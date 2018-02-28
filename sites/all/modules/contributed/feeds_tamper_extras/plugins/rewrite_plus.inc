<?php

/**
 * @file
 * Rewrite a field using tokens.
 * This plugin is inspired by the rewrite plugunb provided by feeds_tamper
 * It differs in the following ways:
 * 1. Looping over multiple inputs and generating an array result
 * 2. Allows NULL return value when result is boolean not
 */

$plugin = array(
  'form' => 'feeds_tamper_rewrite_plus_form',
  'callback' => 'feeds_tamper_rewrite_plus_callback',
  'name' => 'Rewrite Plus',
  'multi' => 'loop',
  'category' => 'Other',
);

/**
 * Configuration form callback for Rewrite Plus feeds tamper plugin
 * @param $importer
 * @param $element_key
 * @param $settings
 * @return array
 * @throws \Exception
 */
function feeds_tamper_rewrite_plus_form($importer, $element_key, $settings) {
  $form = array();
  $replace = array();

  foreach (feeds_tamper_get_unique_source_list($importer) as $source) {
    $replace[] = '[' . $source . ']';
  };
  foreach (array_keys($importer->processor->config['values']) as $key) {
    $replace[] = '[' . $key . ']';
  }

  $form['text'] = array(
    '#type' => 'textarea',
    '#title' => t('Replacement pattern'),
    '#default_value' => isset($settings['text']) ? $settings['text'] : '',
  );
  $form['nullret'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set NULL when empty return value'),
    '#description' => t('If checked, then a zero-length string will set field to NULL.'),
    '#checked' => FALSE,
    '#default_value' => isset($settings['nullret']) ? $settings['nullret'] : '',
  );
  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available replacement patterns'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    '#value' => theme('item_list', array('items' => $replace)),
  );
  return $form;
}

/**
 * Action callback for Rewrite Plus feeds tamper plugin
 * @param $result
 * @param $item_key
 * @param $element_key
 * @param $field
 * @param $settings
 * @param $source
 */
function feeds_tamper_rewrite_plus_callback($result, $item_key, $element_key, &$field, $settings, $source) {
  $trans = array();
  foreach ($result->current_item as $key => $value) {
    $trans['[' . $key . ']'] = is_array($value) ? reset($value) : $value;
  }
  foreach ($source->importer->processor->config['values'] as $key => $value) {
    $trans['[' . $key . ']'] = $value;
  }
  if (!($ret = strtr($settings['text'], $trans)) && $settings['nullret']['#value']) {
    $ret = NULL;
  }
  $field = $ret;
}
