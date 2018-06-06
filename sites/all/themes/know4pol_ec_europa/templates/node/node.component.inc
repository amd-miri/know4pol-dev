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
}

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node__file(array &$variables) {
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
