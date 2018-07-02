<?php

/**
 * @file
 * theme-settings.php
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function know4pol_ec_europa_form_system_theme_settings_alter(&$form, &$form_state) {
  // Build the form.
  if (empty($form['know4pol_ec_europa'])) {
    $form['know4pol_ec_europa'] = [
      '#type' => 'fieldset',
      '#title' => t('Google site verification'),
    ];
  }

  $form['know4pol_ec_europa']['google_site_id_meta'] = [
    '#type' => 'checkbox',
    '#title' => t('Add the meta tag to front page.'),
    '#description' => t('Google needs a META tag to be added to the front page to verify ownership'),
    '#default_value' => theme_get_setting('google_site_id_meta', 'know4pol_ec_europa'),
  ];

  $form['know4pol_ec_europa']['google_site_id_key'] = [
    '#type' => 'textfield',
    '#title' => t('Key provided by google.'),
    '#description' => t('You get this from the webmaster tools.'),
    '#default_value' => theme_get_setting('google_site_id_key', 'know4pol_ec_europa'),
    '#states' => [
      'visible' => [
        ':input[name="google_site_id_meta"]' => [
          'checked' => TRUE,
        ],
      ],
    ],
  ];
}
