<?php

/**
 * @file rules integration for the file module
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_event_info() on behalf of the file module.
 */
function rules_file_event_info() {
  $items = array(
    'file_insert' => array(
      'label' => t('After saving new file'),
      'group' => t('File'),
      'variables' => rules_events_file_variables(t('created file')),
      'access callback' => 'rules_file_integration_access',
    ),
    'file_update' => array(
      'label' => t('After updating existing file'),
      'group' => t('File'),
      'variables' => rules_events_file_variables(t('updated file'), TRUE),
      'access callback' => 'rules_file_integration_access',
    ),
    'file_presave' => array(
      'label' => t('Before saving file'),
      'group' => t('File'),
      'variables' => rules_events_file_variables(t('saved file'), TRUE),
      'access callback' => 'rules_file_integration_access',
    ),

    /**
     * @todo, add support for more file module hooks.
     * Eligible hooks include:
     * hook_file_copy
     * hook_file_delete
     * hook_file_download
     * hook_file_download_access
     * hook_file_download_access_alter
     * hook_file_load
     * hook_file_mimetype_mapping_alter
     * hook_file_move
     * hook_file_url_alter
     * hook_file_validate
     *
     * Some of these might not work as Rules events.
     */
  );

  return $items;
}

/**
 * Returns some parameter suitable for using it with a file
 */
function rules_events_file_variables($file_label, $update = FALSE) {
  $args = array(
    'file' => array('type' => 'file', 'label' => $file_label),
  );

  if ($update) {
    $args += array(
      'file_unchanged' => array(
        'type' => 'file',
        'label' => t('unchanged file'),
        'handler' => 'rules_events_entity_unchanged',
      ),
    );
  }
  return $args;
}

/**
 * File integration access callback.
 *
 * @todo, this is modeled on rules_node_integration_access(). Not sure what it does.
 * It does not seem to get called.
 */
function rules_file_integration_access($type, $name) {
  if ($type == 'event' || $type == 'condition') {
    return entity_access('view', 'file');
  }
}
