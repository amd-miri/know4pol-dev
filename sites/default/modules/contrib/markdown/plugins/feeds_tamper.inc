<?php

/**
 * @file
 * A Feeds Tamper plugin that converts from markdown format.
 */

$plugin = array(
  'form' => 'markdown_feeds_tamper_form',
  'callback' => 'markdown_feeds_tamper_callback',
  'name' => 'Markdown',
  'multi' => 'loop',
  'category' => 'Text',
);

/**
 * Form for plugin.
 */
function markdown_feeds_tamper_form($importer, $element_key, $settings) {
  $form = array();

  $form['help'] = array(
    '#markup' => t('Interpret Markdown format and convert to HTML'),
  );
  return $form;
}

/**
 * Callback for plugin.
 */
function markdown_feeds_tamper_callback($feeds_parser_result, $item_key, $element_key, &$field, $settings, $feeds_source) {
  $field = _filter_markdown($field, null);
}

?>