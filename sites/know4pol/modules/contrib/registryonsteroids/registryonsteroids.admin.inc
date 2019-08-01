<?php

/**
 * @file
 * registryonsteroids.admin.inc
 */

/**
 * Custom hook_menu callback.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The configuration form.
 */
function _registryonsteroids_admin_settings(array $form, array $form_state) {
  $form['registryonsteroids_theme_debug'] = [
    '#type' => 'checkbox',
    '#title' => t('Enable theme debug ?'),
    '#default_value' => variable_get('registryonsteroids_theme_debug', FALSE),
    '#description' => t('Theme debug mode can be used to see possible template suggestions and the locations of template files right in your HTML markup (as HTML comments). For more information, see <a href="@url">documentation</a>.', ['@url' => 'https://www.drupal.org/docs/7/theming/overriding-themable-output/working-with-template-suggestions']),
  ];
  $form['registryonsteroids_rebuild_registry'] = [
    '#type' => 'checkbox',
    '#title' => t('Rebuild the theme registry at each page load ?'),
    '#default_value' => variable_get('registryonsteroids_rebuild_registry', FALSE),
    '#description' => t('Auto-rebuild the theme registry during development. It is <em>extremely</em> important to <a href="!link">turn off this feature</a> on production websites.', ['@link' => url('admin/appearance/settings/' . $GLOBALS['theme'])]),
  ];

  return system_settings_form($form);
}
