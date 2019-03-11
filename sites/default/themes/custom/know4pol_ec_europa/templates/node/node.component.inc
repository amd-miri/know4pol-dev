<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node(&$variables, $hook) {
  // For all content types.
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', 'external');
  switch ($variables['type']) {
    case 'file':
      _know4pol_ec_europa_preprocess_node__file($variables);
      break;

    case 'external_page':
      _know4pol_ec_europa_preprocess_node__external_page($variables);
      break;

    case 'visualisation':
      if ($variables['view_mode'] == 'node_embed' && !isset($variables['field_vis_link_embed'][LANGUAGE_NONE][0])) {
        /* KNOW4POL-400 no link if flag checked */
        unset($variables['content']['node_link']);
        $variables['content']['title'][0]['#markup'] = strip_tags($variables['content']['title']['#items'][0]['value'], '<h3>');
      }
      break;
  }
}

/**
 * Implements template_preprocess_node().
 *
 * @param array $variables
 *   The original variables from the preprocess_node hook.
 */
function _know4pol_ec_europa_preprocess_node__file(array &$variables) {
  $node = $variables['elements']['#node'];
  // Is file a link or a file ?
  $node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
    $node->field_is_legacy_link,
    $node->field_legacy_link,
    $node->field_file_file
  );
  // Filetype icon.
  $_icon_css = $node->field_file_type[LANGUAGE_NONE][0]['taxonomy_term']->field_file_type_classname[LANGUAGE_NONE];
  // Default icon if no type.
  $node->file_type_css = "." . count($_icon_css) ? $_icon_css[0]['value'] : 'ecl-icon--file';
  // Languages versions.
  $translations = translation_node_get_translations($node->nid);
  foreach ($translations as $t) {
    // Other languages olny.
    if ($t->nid != $node->nid) {
      $t_node = node_load($t->nid);
      $t_node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
        $t_node->field_is_legacy_link,
        $t_node->field_legacy_link,
        $t_node->field_file_file
      );
      $node->translations->data[] = $t_node;
    }
  }
}

/**
 * Implements template_preprocess_node().
 *
 * @param array $variables
 *   The original variables from the preprocess_node hook.
 */
function _know4pol_ec_europa_preprocess_node__external_page(array &$variables) {
  // Default values if empty.
  if (!isset($variables['field_frame_height'][0]['value'])) {
    $variables['field_frame_height'] = [['value' => 350]];
  }
  // Default values if empty.
  if (!isset($variables['field_frame_width'][0]['value'])) {
    $variables['field_frame_width'] = [['value' => '100%']];
  }
}
