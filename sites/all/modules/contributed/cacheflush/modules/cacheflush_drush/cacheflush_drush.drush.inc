<?php

/**
 * @file
 * Cacheflush Drush implementation.
 */

/**
 * Implements hook_drush_help().
 */
function cacheflush_drush_drush_help($command) {
  switch ($command) {
    case 'drush:cacheflush':
      return dt('Clear cache with help of cacheflush module.');
  }
}

/**
 * Implements hook_drush_command().
 */
function cacheflush_drush_drush_command() {
  $items = array();
  $items['cacheflush'] = array(
    'description' => dt('Clear cache predefined in cacheflush preset.'),
    'arguments' => array(
      'id' => dt('Preset id to run'),
    ),
    'examples' => array(
      'Example' => 'drush cacheflush 5',
    ),
    'aliases' => array('cf'),
  );
  return $items;
}

/**
 * Callback function for drush cacheflush.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (cacheflush_drush) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 *
 * @param string|int $id
 *   An optional argument.
 */
function drush_cacheflush_drush_cacheflush($id = NULL) {
  module_load_include('inc', 'cacheflush', 'cacheflush.api');
  if (isset($id)) {
    if (is_numeric($id)) {
      drush_print(_cacheflush_clear_preset($id));
    }
    else {
      drush_print(t('Please provide the ID of the preset (numeric value) ex: "drush cf 1".'));
    }
  }
  else {
    drush_log(t('Preset list. Use "drush cf ID" to clear cache.'), 'ok');
    drush_print('');
    foreach (cacheflush_load_multiple(FALSE, array('status' => 1)) as $id => $entity) {
      drush_print('[' . $id . ']   :   ' . $entity->title);
    }
  }
}
