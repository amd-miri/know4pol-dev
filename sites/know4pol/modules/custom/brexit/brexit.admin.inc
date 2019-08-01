<?php

/**
 * @file
 * Administration forms for the Brexit module.
 */

/**
 * Form constructor for the main admin form for configuring Brexit.
 */
function brexit_admin() {
  $form = array();

  $form['brexit_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate automatic publication (disable this as killswitch)'),
    '#default_value' => variable_get('brexit_active', FALSE),
  );

  $form['brexit_publication_datetime'] = array(
    '#type' => 'textfield',
    '#title' => t('When to automatically publish content'),
    '#default_value' => variable_get('brexit_publication_datetime', BREXIT_PUBLICATION_DATETIME),
    '#size' => 20,
    '#maxlength' => 20,
    '#description' => t('This is the time that will be used to publish all content with Brexit sheduling (uses cron)'),
    '#states' => array(
      'visible' => array(
        ':input[name="brexit_active"]' => array('checked' => TRUE),
      ),
    ),
  );

  if (module_exists('date_popup')) {
    $form['brexit_publication_datetime']['#type'] = 'date_popup';
    $form['brexit_publication_datetime']['#date_format'] = BREXIT_DATE_FORMAT;
    $form['brexit_publication_datetime']['#date_year_range'] = '0:+10';
    $form['brexit_publication_datetime']['#date_increment'] = 1;
    unset($form['brexit_publication_datetime']['#maxlength']);
  }

  return system_settings_form($form);
}
