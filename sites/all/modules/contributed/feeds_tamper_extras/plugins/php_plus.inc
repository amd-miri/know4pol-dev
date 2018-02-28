<?php

/* This plugin is inspired by the feeds_tamper_php plugin.
 * It differs in three main ways:
 * 1. uses multi-loop to build an array result on input multi-fields
 * 2. provides $var and $default arrays with other feeds results or values
 * 3. allows a NULL return value to leave field alone
 */

$plugin = array(
  'form' => 'feeds_tamper_php_plus_form',
  'callback' => 'feeds_tamper_php_plus_callback',
  'name' => 'PHP Plus',
  'multi' => 'loop',
  'category' => 'Other',
);

/* Convert a string into a PHP-compatible variable name
*/
function _feeds_tamper_php_plus_name_convert($string) {
  return strtr($string, array(
    ' ' => '',
    ':' => '',
    '-' => '__'
  ));
}

/**
 * Form callback for PHP Plus feeds tamper callback
 * @param $importer
 * @param $element_key
 * @param $settings
 * @return array
 * @throws \Exception
 */
function feeds_tamper_php_plus_form($importer, $element_key, $settings) {
  $form = array();
  $replace = array();

  $replace[] = '$field';
  $replace[] = '$result, $item_key, $element_key, $settings, $source';
  foreach (feeds_tamper_get_unique_source_list($importer) as $source) {
    $replace[] = '$var[\'' . _feeds_tamper_php_plus_name_convert($source) . '\']';
  }
  foreach (array_keys($importer->processor->config['values']) as $key) {
    $replace[] = '$default[\'' . _feeds_tamper_php_plus_name_convert($key) . '\']';
  }

  $form['text'] = array(
    '#type' => 'textarea',
    '#title' => t('PHP code to evaluate'),
    '#rows' => 25,
    '#default_value' => isset($settings['text']) ? $settings['text'] : '',
  );
  $form['nullret'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set field when NULL return value'),
    '#description' => t('If checked, then a NULL return will set field to NULL. If not checked, a NULL return leaves field untouched.'),
    '#checked' => FALSE,
    '#default_value' => isset($settings['nullret']) ? $settings['nullret'] : '',
  );
  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available variables'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
    '#value' => theme('item_list', array('items' => $replace)),
  );
  return $form;
}

/**
 *  Implements php_plus feeds_tamper callback
 * @param $result
 * @param $item_key
 * @param $element_key
 * @param $field
 * @param $settings
 * @param $source
 */
function feeds_tamper_php_plus_callback($result, $item_key, $element_key, &$field, $settings, $source) {
  $var = array();
  $default = array();

  foreach ($result->current_item as $key => $value) {
    $var[_feeds_tamper_php_plus_name_convert($key)] = $value;// (is_array($value) ? reset($value) : $value);
  }
  foreach ($source->importer->processor->config['values'] as $key => $value) {
    $default[_feeds_tamper_php_plus_name_convert($key)] = ($value);
  }
  ob_start();
  $ret = eval($settings['text']);
  ob_get_clean();

  if ($ret !== NULL || $settings['nullret']['#value']) {
    $field = $ret;
  }
}
