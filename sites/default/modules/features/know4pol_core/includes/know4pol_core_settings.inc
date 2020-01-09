<?php

/**
 * @file
 * Administration forms for know4pol-core feature.
 */

/**
 * Implements hook_form().
 */
function know4pol_core_ks_settings_form($form, &$form_state, $nid) {
  $form['latest'] = array(
    '#type' => 'fieldset',
    '#title' => t('Latest ressources settings'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['latest']['types_hidden'] = array(
    '#type' => 'select',
    '#title' => t('Hidden content types'),
    '#options' => _know4pol_core_get_last_ressources_types([], FALSE),
    '#description' => t('What content types are <u>not</u> allowed to appear in the latest ressource block'),
    '#multiple' => TRUE,
    '#default_value' => _know4pol_core_get_setting($nid, 'types_hidden', NULL),
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 2,
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function know4pol_core_ks_settings_form_submit($form, &$form_state) {
  _know4pol_core_save_setting(arg(2), 'types_hidden', $form_state['values']['types_hidden']);
  drupal_set_message(t('KS settings have been saved'), 'status');
}

/**
 * Get content types filter from view.
 *
 * @param array $remove
 *   An array of machine name content types to remove from the list.
 * @param bool $machine
 *   Whether return machine (true) or human name, default true.
 *
 * @return array
 *   List of content types machine names.
 */
function _know4pol_core_get_last_ressources_types(array $remove = array(), $machine = TRUE) {
  // Open view for accepted types;.
  $view = views_get_view('ks_latest_content');
  if (!$view || !$view->access('latest_resources')) {
    return NULL;
  }

  $result = array();
  $node_types = $machine ? NULL : node_type_get_types();

  foreach ($view->display['latest_resources']->display_options['filters']['type']['value'] as $ct) {
    if (!array_key_exists($ct, $remove)) {
      $result[$ct] = $machine ? $ct : $node_types[$ct]->name;
    }
  }
  krumo($view->display['latest_resources']->display_options['filters']['type']['value']);
  krumo($result);

  return $result;
}

/**
 * Loads a setting value for a given group.
 *
 * @param int $gid
 *   The group id the setting is for.
 * @param string $key
 *   The name of the setting.
 * @param mixed $default
 *   The default value if setting does not exist.
 *
 * @return mixed
 *   The loaded value for the setting or default.
 *
 * @todo Consider using DB table rather that variable get/set.
 */
function _know4pol_core_get_setting($gid, $key, $default) {
  return variable_get('know4pol_core_ks_settings_' . $gid . '_' . $key, $default);
}

/**
 * Saves a setting value for a given group.
 *
 * @param int $gid
 *   The group id the setting is for.
 * @param string $key
 *   The name of the setting.
 * @param mixed $value
 *   The value to store.
 *
 * @todo Consider using DB table rather that variable get/set.
 */
function _know4pol_core_save_setting($gid, $key, $value) {
  variable_set('know4pol_core_ks_settings_' . $gid . '_' . $key, $value);
}
