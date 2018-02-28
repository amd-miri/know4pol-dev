<?php

/**
 * @file
 * Rewrite a field using tokens.
 */

$plugin = array(
  'form' => 'feeds_tamper_property_by_property_form',
  'callback' => 'feeds_tamper_property_by_property_callback',
  'name' => 'Property by property',
  'multi' => 'loop',
  'category' => 'Other',
);

/**
 * Form callback for Property by Property feeds tamper configuration
 * @param $importer
 * @param $element_key
 * @param $settings
 * @return array
 */
function feeds_tamper_property_by_property_form($importer, $element_key, $settings) {
  $form = array();
  $form['haystacktable'] = array(
    '#type' => 'textfield',
    '#title' => t('Haystack table'),
    '#description' => t('This is the table to search.'),
    '#default_value' => isset($settings['haystacktable']) ? $settings['haystacktable'] : 'bc',
    '#size' => 64,
    '#required' => TRUE,
  );
  $form['needleproperty'] = array(
    '#type' => 'textfield',
    '#title' => t('Needle property'),
    '#description' => t('This is the property to search for.'),
    '#default_value' => isset($settings['needleproperty']) ? $settings['needleproperty'] : 'extid',
    '#size' => 64,
    '#required' => TRUE,
  );
  $form['resultproperty'] = array(
    '#type' => 'textfield',
    '#title' => t('Property to be returned as result.'),
    '#description' => t('This is the property to return.'),
    '#default_value' => isset($settings['resultproperty']) ? $settings['resultproperty'] : 'bcid',
    '#size' => 64,
    '#required' => TRUE,
  );
  return $form;
}

/**
 * feeds_tamper plugin to look up a record in a database and return a column.
 * In Drupal-land, a column of a record is called a "property". Therefore, this
 * plugin looks up a record by a "property" and then returns a particular other
 * "property" of the found record.
 * @param $result
 * @param $item_key
 * @param $element_key
 * @param $field
 * @param $settings
 */
function feeds_tamper_property_by_property_callback($result, $item_key, $element_key, &$field, $settings) {
  if ($field) {
    $haystacktable = $settings['haystacktable'] ? $settings['haystacktable'] : 'bc';
    $needleproperty = $settings['needleproperty'] ? $settings['needleproperty'] : 'extid';
    $resultproperty = $settings['resultproperty'] ? $settings['resultproperty'] : 'bcid';
    $searchfor = $field;
    $result = db_select($haystacktable, 'b')
      ->condition('b.' . $needleproperty,
        $searchfor)
      ->fields('b', array($resultproperty))
      ->execute();
    if ($result->rowCount()) {
      $field = $result->fetchField();
    }
  }
}