<?php

/**
 * @file
 * Contains the CacheflushUI forms function.
 */

/**
 * Callback: cacheflush_ui_preset_form().
 */
function cacheflush_ui_preset_form_options(&$form, &$form_state) {

  // Form element, vertical tab parent.
  $form['cacheflush_vertical_tabs'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 50,
    '#attached' => array(
      'js' => array(
        'vertical-tabs' => drupal_get_path('module', 'cacheflush_ui') . '/js/cacheflush_ui_vertical_tabs.js',
      ),
    ),
  );

  // Add vertical tabs.
  $form_state['#cacheflush_tabs'] = module_invoke_all('cacheflush_ui_tabs');
  $original_tabs = cacheflush_ui_cacheflush_ui_tabs();
  foreach ($form_state['#cacheflush_tabs'] as $key => $value) {
    $form[$key] = array(
      '#type' => 'fieldset',
      '#title' => check_plain($value['name']),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#group' => 'cacheflush_vertical_tabs',
      '#tree' => TRUE,
      '#weight' => isset($value['weight']) ? $value['weight'] : NULL,
      '#attributes' => isset($original_tabs[$key]) ? array('class' => array('original_tabs')) : array(),
    );
  }

  $form_state['cacheflush']->data = unserialize(isset($form_state['cacheflush']->data) ? $form_state['cacheflush']->data : NULL);
  // Adding table elemnts to tabs.
  $form_state['#preset_options'] = _cacheflush_get_option_list();
  foreach ($form_state['#preset_options'] as $key => $value) {
    // Special tab element added only if there module are instaled.
    if ($value['category'] == 'vertical_tabs_often' && !module_exists($key)) {
      continue;
    }
    $form[$value['category']][$key] = array(
      '#type' => 'checkbox',
      '#title' => check_plain($key),
      '#default_value' => isset($form_state['cacheflush']->data[$key]) ? 1 : 0,
      '#description' => check_plain($value['description']),
    );
  }
  _cacheflush_ui_tabs_description($form);
}

/**
 * Callback form preset form validate.
 */
function cacheflush_ui_tab_validation($tab, &$form, &$form_state) {
  if (isset($form_state['values'][$tab])) {
    foreach ($form_state['values'][$tab] as $preset => $value) {
      if ($value) {
        $form_state['cacheflush']->data[$preset]['functions'] = $form_state['#preset_options'][$preset]['functions'];
      }
    }
  }
}

/**
 * Update form tabs with Notes.
 */
function _cacheflush_ui_tabs_description(&$form) {

  $form['cacheflush_form_mani_note'] = array(
    '#type' => 'item',
    '#title' => t('Cache sources'),
    '#weight' => 40,
    '#description' => t('Select below the different cache sources you wish to clear when your preset is executed. Don`t be afraid to select them, all these are flushed when you normally clear all the caches. Select only those you need for better performance.'),
  );

  $form['vertical_tabs_core']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note'),
    '#description' => t('Select any of the cache database tables below, to be truncated when this preset is executed.'),
    '#weight' => -10,
  );

  $form['vertical_tabs_functions']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note'),
    '#description' => t('Select any of the below functions to be run when this preset is executed.'),
    '#weight' => -10,
  );

  $form['vertical_tabs_custom']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note'),
    '#description' => t('Select any of the tables defined by contributed modules to be flushed when this preset is executed.'),
    '#weight' => -10,
  );

  $form['vertical_tabs_often']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note'),
    '#description' => t('Some contrib modules have unique ways to store their cache, or to flush them.<br />These require custom configuration, so if you can`t find some of your contrib modules here, please submit us an issue on <a href="@url">http://drupal.org/project/cacheflush/issues/</a><br />
Select any from the list below to clear when this preset is executed.', array('@url' => url('http://drupal.org/project/issues/cacheflush/'))),
    '#weight' => -10,
  );
}
