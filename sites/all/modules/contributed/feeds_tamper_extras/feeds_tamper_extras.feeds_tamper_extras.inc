<?php

/**
 * @file
 * Install, update and uninstall functions for the number module.
 */

/**
 * Import importer validate and submit (source: feeds_ui_admin.inc)
 * @param $filename filename of export code (should not have leading <?php
 * @return NULL if import unsuccessful, feeds id otherwise
 */
function _feeds_tamper_extras_load_feeds_importer($filename) {
  if (file_exists($filename)) {
    $defstr = file_get_contents($filename);
    $feeds_importer = NULL;

    ob_start();
    eval($defstr);
    ob_end_clean();

    if (!is_object($feeds_importer)) {
      drupal_set_message(t('Unable to interpret Feeds importer code (!filename)', array('!filename' => $filename)), 'error');
      return NULL;
    }

    if (empty($feeds_importer->api_version) || $feeds_importer->api_version < 1) {
      drupal_set_message(t('The !filename importer is not compatible with this version of Feeds.', array('!filename' => $filename)), 'error');
      return NULL;
    }
    elseif (version_compare($feeds_importer->api_version, feeds_api_version(), '>')) {
      drupal_set_message(t('That importer is created for the version %import_version of Feeds, but you only have version %api_version.', array(
        '%import_version' => $feeds_importer->api_version,
        '%api_version' => feeds_api_version()
      )), 'error');
      return NULL;
    }
    foreach (array('fetcher', 'parser', 'processor') as $type) {
      $plugin = feeds_plugin($feeds_importer->config[$type]['plugin_key'], $feeds_importer->id);
      if (get_class($plugin) == 'FeedsMissingPlugin') {
        drupal_set_message(t('The plugin %plugin is unavailable.', array('%plugin' => $feeds_importer->config[$type]['plugin_key'])), 'warning');
        return NULL;
      }
    }

    // Create a copy of the importer to preserve config.
    if (!($save = feeds_importer($feeds_importer->id))) {
      drupal_set_message(t('Feeds importer %importer_id does not load. Error importing from %filename', array(
        '%importer_id' => $feeds_importer->id,
        '%filename' => $filename
      )), 'warning');
      return NULL;
    }
    $save->setConfig($feeds_importer->config);
    foreach (array('fetcher', 'parser', 'processor') as $type) {
      $save->setPlugin($feeds_importer->config[$type]['plugin_key']);
      $save->$type->setConfig($feeds_importer->config[$type]['config']);
    }
    $save->save();

    drupal_set_message(t('Successfully created the %id feeds importer from %filename.', array(
      '%id' => $feeds_importer->id,
      '%filename' => $filename
    )));
    return $feeds_importer->id;
  }
  return NULL;
}

/**
 * Load tamper definitions from exported file
 */
function _feeds_tamper_extras_load_feeds_tamper($filename) {
  $ret = FALSE;
  if (file_exists($filename)) {
    $defstr = file_get_contents($filename);
    $export = NULL;
    ob_start();
    eval($defstr);
    ob_end_clean();
    // $form_state['export'] = $export;
    if (!is_array($export)) {
      drupal_set_message(t('Unable to interpret Feeds tamper importer code in !filename', array('!filename' => $filename)), 'error');
      return $ret;
    }
    if (!empty($export)) {
      foreach ($export as $value) {
        // $feeds_importer = feeds_importer_load($value->importer);
        // if (!empty($feeds_importer)) {
        if (feeds_tamper_load_instance($value->id)) {
          drupal_set_message(t('The feeds tamper !tamper is already in use. Definition from !filename not imported.', array(
            '!tamper' => $value->id,
            '!filename' => $filename
          )), 'warning');
          continue;
        }
        $plugin_id = $value->plugin_id;
        $plugin = feeds_tamper_get_plugin($plugin_id);
        if ($plugin['validate'] && isset($value->settings)) {
          $plugin['validate']($value->settings);
        }
        // from submit
        $obj = feeds_tamper_new_instance();
        $obj->plugin_id = $value->plugin_id;
        if (isset($value->settings)) {
          $obj->settings = $value->settings;
        }
        $obj->importer = $value->importer;
        $obj->source = $value->source;
        $obj->description = $value->description;
        $obj->id = $value->id;
        $obj->weight = $value->weight;
        feeds_tamper_save_instance($obj);
        // $source_name = feeds_tamper_ui_source_name($obj);
        // drupal_set_message(t('Plugin %description was successfully added to %source.', array( '%description' => $obj->description, '%source' => $source_name, )));
        if (!$ret) {
          $ret = TRUE;
        }
      }
    }
  }
  return $ret;
}

/**
 * Scan a directory and load importers
 */
function _feeds_tamper_extras_load_from_rootdir($modulename, $rootdir) {
  $ret = FALSE;
  $tracking = variable_get('feeds_tamper_extras_tracking', array());
  $files = file_scan_directory($rootdir, '/(\w+)\.importer.export$/');
  foreach ($files as $file) {
    feeds_cache_clear(FALSE);
    if ($id = _feeds_tamper_extras_load_feeds_importer($file->uri)) {
      $ret = TRUE;
      $tracking[$id] = $modulename;
    }
  }
  if ($ret) {
    variable_set('feeds_tamper_extras_tracking', $tracking);
  }
  $files = file_scan_directory($rootdir, '/(\w+)\.tamper.export$/');
  foreach ($files as $file) {
    feeds_cache_clear(FALSE);
    if ($id = _feeds_tamper_extras_load_feeds_tamper($file->uri)) {
      $ret = TRUE; // tampers need to refer to importers and will get removed with importer. If they don't refer to an importer, there will be a leak
    }
  }
  return $ret;
}

/**
 * Load all importer.export and tamper.export files in the importers directory
 */
function _feeds_tamper_extras_load_feeds_importers($module_list = NULL) {
  if (!$module_list) {
    if (!($module_list = module_implements('feeds_tamper_extras_importdir'))) {
      return FALSE;
    }
  }
  $ret = FALSE;
  feeds_importer_load_all(TRUE);
  foreach ($module_list as $module) {
    $importlist = module_invoke($module, 'feeds_tamper_extras_importdir');
    if (!is_array($importlist)) {
      $importlist = array($importlist);
    }
    foreach ($importlist as $importdir) {
      if (_feeds_tamper_extras_load_from_rootdir($module, $importdir)) {
        $ret = TRUE;
      }
    }
  }
  if ($ret) {
    feeds_cache_clear(FALSE);
  }
  return $ret;
}

/**
 * Implements hook_feeds_tamper_extras_autocreate()
 */
function feeds_tamper_extras_feeds_tamper_extras_autocreate($module_list = NULL) {
  if (_feeds_tamper_extras_load_feeds_importers($module_list)) {
    feeds_cache_clear(TRUE);
  }
}

/*
 * Remove feeds tampers for importer
 * Based on feeds_tamper_rectify_instances()
 */
function _feeds_tamper_extras_remove_tamper_instances($importerid, $sourcelist) {
  ctools_include('export');
  $instances = ctools_export_load_object('feeds_tamper', 'conditions', array('importer' => $importerid));

  foreach ($instances as $instance) {
    if (!in_array($instance->source, $sourcelist)) {
      continue;
    }

    if ($instance->export_type == EXPORT_IN_DATABASE) {
      feeds_tamper_delete_instance($instance);
    }
    else {
      $instance->disabled = TRUE;
      feeds_tamper_save_instance($instance);
    }
  }
}

/**
 * remove importers defined within bc
 */
function _feeds_tamper_extras_delete_feeds_importers($modules = NULL) {
  $ret = 0;
  $feeds_tamper_extras_tracking = variable_get('feeds_tamper_extras_tracking', array());
  foreach ($feeds_tamper_extras_tracking as $importer_id => $module) {
    if (!$modules || in_array($module, $modules)) {
      if ($importer = feeds_importer($importer_id)) {
        $sources = feeds_tamper_get_unique_source_list($importer, FALSE);
        $importer->delete();

        drupal_set_message(t('Deleted the %id feeds importer defined by %module.', array(
          '%id' => $importer->id,
          '%module' => $module
        )));
        unset($feeds_tamper_extras_tracking[$importer_id]);
        _feeds_tamper_extras_remove_tamper_instances($importer_id, $sources);
        $ret = 1;
      }
    }
  }
  if ($ret) {
    variable_set('feeds_tamper_extras_tracking', $feeds_tamper_extras_tracking);
  }
  return ($ret);
}

/**
 * Implements hook_feeds_tamper_extras autodelete()
 */
function feeds_tamper_extras_feeds_tamper_extras_autodelete($modules = NULL) {
  if (_feeds_tamper_extras_delete_feeds_importers($modules)) {
    //clear the cache to display in Feeds as available plugin.
    feeds_cache_clear(TRUE);
    cache_clear_all('plugins:feeds:plugins', 'cache');
    menu_rebuild();
  }
}
