<?php

/**
 * @file
 * Administration forms for the bulk_schedule module.
 */

/**
 * Form constructor for the main admin form for configuring Bulk Schedule.
 */
function bulk_schedule_admin() {
  $form = array();

  $form['bulk_schedule_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate automatic publication (disable this as killswitch)'),
    '#default_value' => variable_get('bulk_schedule_active', FALSE),
  );

  $form['bulk_schedule_publication_datetime'] = array(
    '#type' => 'textfield',
    '#title' => t('When to automatically publish content'),
    '#default_value' => variable_get('bulk_schedule_publication_datetime', BULK_SCHEDULE_PUBLICATION_DATETIME),
    '#size' => 20,
    '#maxlength' => 20,
    '#description' => t('This is the time that will be used to publish all content with Bulk sheduling (uses cron)'),
    '#states' => array(
      'visible' => array(
        ':input[name="bulk_schedule_active"]' => array('checked' => TRUE),
      ),
    ),
  );

  if (module_exists('date_popup')) {
    $form['bulk_schedule_publication_datetime']['#type'] = 'date_popup';
    $form['bulk_schedule_publication_datetime']['#date_format'] = BULK_SCHEDULE_DATE_FORMAT;
    $form['bulk_schedule_publication_datetime']['#date_year_range'] = '0:+10';
    $form['bulk_schedule_publication_datetime']['#date_increment'] = 1;
    unset($form['bulk_schedule_publication_datetime']['#maxlength']);
  }

  return system_settings_form($form);
}
