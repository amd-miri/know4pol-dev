<?php

/**
 * @file
 * Contains the CacheflushUI forms function.
 */
module_load_include('inc', 'cacheflush_ui', 'includes/cacheflush_ui.presets');

/**
 * Cacheflush preset edit form.
 */
function cacheflush_form($form, &$form_state, $entity = NULL) {
  global $base_url;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($entity->title) ? check_plain($entity->title) : NULL,
    '#required' => TRUE,
  );

  $form_state['cacheflush'] = $entity;
  cacheflush_ui_preset_form_options($form, $form_state);

  $form['actions']['#weight'] = 100;
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => isset($entity->id) ? t('Update') : t('Save'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), $base_url . '/' . cacheflush_ui_get_path()),
  );
  $form['#validate'][] = 'cacheflush_ui_preset_form_validate';
  $form['#submit'][] = 'cacheflush_ui_preset_form_submit';
  return $form;
}

/**
 * Cacheflush preset edit form validate.
 */
function cacheflush_ui_preset_form_validate($form, &$form_state) {

  if (isset($form_state['cacheflush'])) {
    $form_state['cacheflush']->title = $form_state['values']['title'];
  }
  else {
    $form_state['cacheflush'] = cacheflush_create(array('title' => $form_state['values']['title']));
  }
  foreach ($form_state['#cacheflush_tabs'] as $tab => $value) {
    $value['validation']($tab, $form, $form_state);
  }
}

/**
 * Cacheflush preset edit form submit.
 */
function cacheflush_ui_preset_form_submit($form, &$form_state) {
  $form_state['redirect'] = cacheflush_ui_get_path();
  $form_state['cacheflush']->data = serialize($form_state['cacheflush']->data);

  // hook_cacheflush_preset_save_alter.
  drupal_alter('cacheflush_preset_save', $form_state['cacheflush'], $form_state['cacheflush']->id);

  cacheflush_save($form_state['cacheflush']);

  // Declare hook_cacheflush_preset_save().
  module_invoke_all('cacheflush_preset_save', $form_state['cacheflush'], $form_state['cacheflush']->id);
}

/**
 * Confirm Form for deleting an existing entity.
 */
function cacheflush_ui_delete_form($form, &$form_state, $entity) {
  $question = t('Are you sure you want to delete this preset?');
  return confirm_form($form, $question, cacheflush_ui_get_path(), t('This action cannot be undone.'));
}

/**
 * Submit for deleting an existing entity.
 */
function cacheflush_ui_delete_form_submit($form, &$form_state) {
  $form_state['redirect'] = cacheflush_ui_get_path();
  cacheflush_delete($form_state['build_info']['args'][0]->id);
  node_types_rebuild();
  menu_rebuild();
}
