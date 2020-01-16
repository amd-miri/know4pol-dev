<?php

/**
 * @file
 * Administration forms for the Brexit module.
 */

/**
 * Form constructor for the main admin form for configuring In-page navigation.
 */
function multisite_inpage_nav_admin() {
  $form = array();

  $form['post_process'] = array(
    '#type' => 'fieldset',
    '#title' => t('post-process HTML analysis'),
    '#description' => t('triggers markup analysis after content is rendered useful for contexts and views)'),
  );
  $form['post_process']['multisite_inpage_nav_content_types'] = array(
    '#type' => 'select',
    '#title' => t('On specific content types'),
    '#default_value' => variable_get('multisite_inpage_nav_content_types', NULL),
    '#options' => node_type_get_names(),
    '#multiple' => TRUE,
    '#chosen' => TRUE,
    '#description' => t("When rendered as a page."),
  );
  if (module_exists('ds')) {
    $view_modes = ds_entity_view_modes('node');
    $form['post_process']['multisite_inpage_nav_viewmode'] = array(
      '#type' => 'select',
      '#title' => t('For specific viewmode'),
      '#default_value' => variable_get('multisite_inpage_nav_viewmode', NULL),
      '#options' => array_combine(array_keys($view_modes), array_column($view_modes, 'label')),
      '#multiple' => TRUE,
      '#chosen' => TRUE,
    );
  }
  $form['post_process']['multisite_inpage_nav_path'] = array(
    '#type' => 'textarea',
    '#title' => t('By path'),
    '#default_value' => variable_get('multisite_inpage_nav_path', ''),
    '#description' => t('For specified path, supports node/nid. use one per line.'),
  );

  return system_settings_form($form);
}
