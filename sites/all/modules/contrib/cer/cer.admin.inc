<?php

/**
 * @file
 * Administrative functionality, separated for performance purposes.
 */

/**
 * The settings form.
 */
function cer_settings_form($form = array(), &$form_state) {
  $channels = array();

  foreach (_cer_get_fields() as $field) {
    // A field that hasn't been instantiated yet will not have a 'bundles' key, which
    // means it's useless to us, so skip over it.
    if (! isset($field['bundles'])) {
      continue;
    }

    foreach ($field['bundles'] as $entity_type => $bundles) {
      foreach ($bundles as $bundle) {
        $instance = field_info_instance($entity_type, $field['field_name'], $bundle);
        if ($instance) {
          $channels = array_merge($channels, _cer_find_channels($instance));
        }
       }
     }
   }

  if (empty($channels)) {
    drupal_set_message(t('There are no entity reference fields that can correspond.'), 'warning');
  }
  else {
    $mapping = array();
    foreach ($channels as $count => $key) {
      $formatted_key = str_replace(' ', '*', $key);

      $mapping[$count] = $formatted_key;

      $form['values']["enabled_{$count}"] = array(
        '#type' => 'checkbox',
        '#default_value' => cer_preset_enabled($formatted_key),
        '#title' => filter_xss(theme('cer_label', array('key' => $key))),
      );
    }

    // We are using a hidden field to submit the configuration because on
    // some systems the checkbox name length is limited, and using
    // the key would cause the length to be too long. (Issue #558612)
    $form['mapping'] = array(
      '#type' => 'hidden',
      '#value' => serialize($mapping),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }


  return $form;
}

/**
 * Submit function for settings form.
 */
function cer_settings_form_submit($form, $form_state) {
  ctools_include('export');
  $query_values = array();

  $mapping = unserialize($form_state['values']['mapping']);

  foreach ($form_state['values'] as $key => $value) {
    $keys = explode('_', $key);
    if ($keys[0] == 'enabled') {
      $query_values[$mapping[$keys[1]]] = $value;
    }
  }

  // load all existing presets
  $presets = ctools_export_crud_load_all('cer');

  foreach ($query_values as $key => $value) {
    // get preset object (create new one if it doesn't exist already).
    $preset = empty($presets[$key]) ? ctools_export_crud_new('cer') : $presets[$key];

    // set and save value
    if (empty($preset->entity_types_content_fields)) {
      $preset->entity_types_content_fields = $key;
    }
    $preset->enabled = $value;
    ctools_export_crud_save('cer', $preset);

    // remove from list of presets, so we know which ones are still used
    if (isset($presets[$key])) {
      unset($presets[$key]);
    }
  }

  drupal_set_message(t('The configuration has been saved.'));
}

/**
 * Allows batch updating of existing entities.
 */
function cer_update_form($form = array(), &$form_state) {
  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Entity type'),
    '#required' => TRUE,
    '#options' => array(),
    '#description' => t('Select the entity type that you want to update.'),
  );
  foreach (entity_get_info() as $type => $class) {
    $form['type']['#options'][$type] = $class['label'];
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * The update form.
 * Allows updating of current entitys.
 */
function cer_update_form_submit($form, &$form_state) {
  $batch = array(
    'finished' => 'cer_batch_update_existing_finished',
    'title' => t('Processing'),
    'init_message' => t('Preparing to update corresponding entity references for existing entities...'),
    'progress_message' => t('Processing entities...'),
    'error_message' => t('Corresponding entity references - existing entity update has encountered an error.'),
  );

  $entity_type = $form_state['values']['type'];
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type);
  $result = $query->execute();
  if (isset($result[$entity_type])) {
    foreach ($result[$entity_type] as $entity_id => $stub) {
      $batch['operations'][] = array('cer_processing_entity', array('update', $entity_id, $entity_type));
    }
  }
  batch_set($batch);
}

/**
 * The purpose of this function is to answer this question: I am a field instance. Which other
 * fields reference the entity that owns me? And of those instances, which ones can I reference?
 * The answer is returned as an array of CER keys: "entity1 bundle1 field1 entity2 bundle2 field2".
 *
 * @param array $instance
 *  Field instance info, as returned by field_info_instance().
 *
 * @return array
 */
function _cer_find_channels($instance) {
  $channels = array();

  $my_id = $instance['entity_type'] . ' ' . $instance['bundle'] . ' ' . $instance['field_name'];
  $my_info = field_info_field($instance['field_name']);
  $my_targets = _cer_get_target_bundles($my_info);
  $my_target_type = $my_info['settings']['target_type'];

  $referrers = _cer_find_referrers($instance['entity_type'], $instance['bundle']);
  foreach ($referrers as $referrer) {
    if (isset($referrer['bundles'][$my_target_type])) {
      if (empty($my_targets)) {
        $bundles = $referrer['bundles'][$my_target_type];
      }
      else {
        $bundles = array_intersect($referrer['bundles'][$my_target_type], $my_targets);
      }
      
      foreach ($bundles as $bundle) {
        $channels[] = "{$my_id} {$my_target_type} {$bundle} " . $referrer['field_name'];
      }
    }
  }

  return $channels;
}

/**
 * Find all fields that can reference the given entity type and bundle.
 *
 * @param $entity_type
 *  The entity type that can be referenced.
 * @param $bundle
 *  The bundle that can be referenced.
 *
 * @return array
 */ 
function _cer_find_referrers($entity_type, $bundle) {
  $referrers = array();
  foreach (_cer_get_fields() as $field) {
    if ($field['settings']['target_type'] == $entity_type) {
      $target_bundles = _cer_get_target_bundles($field);
      if (empty($target_bundles) || in_array($bundle, $target_bundles)) {
        $referrers[] = $field;
      }
    }
  }

  return $referrers;
}

/**
 * Find all bundles reference-able by a given field. If all bundles are reference-able,
 * an empty array is returned.
 *
 * @param $field
 *  Field info array as returned by field_info_field().
 *
 * @return array
 */
function _cer_get_target_bundles($field) {
  $target_bundles = array();

  // If the reference field is using a view, load the view and see if it's filtering by the entity
  // type's bundle filter. If it is, the filter values are the target bundles. Otherwise,
  // assume that all bundles can be referenced.
  //
  // @todo Support contextual filters?
  //
  // NOTE: Selection handlers (i.e., $field['settings']['handler']) are plugins owned by
  // Entity Reference. There is no method defined to get an array of referenceable
  // bundles, but hopefully, if CER gains enough traction in the community, such a
  // method can be added to the EntityReference_SelectionHandler interface. This
  // function could then be deprecated, which would be a more flexible, future-proof
  // method of finding a field's target bundles.
  //
  if ($field['settings']['handler'] == 'views') {
    $view_name = $field['settings']['handler_settings']['view']['view_name'];

    $view = views_get_view($view_name);
    if ($view) {
      $view->set_display($field['settings']['handler_settings']['view']['display_name']);

      $info = entity_get_info($field['settings']['target_type']);
      if ($info['entity keys']['bundle'] && $handler = $view->display_handler->get_handler('filter', $info['entity keys']['bundle'])) {
        $target_bundles = $handler->value;
      }
    }
    else {
      drupal_set_message(t('Could not get target bundles for %field (failed to load view %view).', array('%view' => $view_name, '%field' => $field['field_name'])), 'error');
    }
  }
  elseif (isset($field['settings']['handler_settings']['target_bundles'])) {
    $target_bundles = $field['settings']['handler_settings']['target_bundles'];
  }
  else {
    $info = entity_get_info($field['settings']['target_type']);
    $target_bundles = array_keys($info['bundles']);
  }

  return $target_bundles;
}

/**
 * Get the Field API definitions for all entity reference fields.
 *
 * @return array
 */
function _cer_get_fields() {
  static $fields;
  if (!isset($fields)) {
    $fields = array_map('field_info_field', db_select('field_config', 'fc')->fields('fc', array('field_name'))->condition('type', 'entityreference')->execute()->fetchCol());
  }  
  return $fields;
}