<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements hook_menu_link().
 */
function know4pol_ec_europa_menu_link(array $variables) {
  // Add a class to menu links that link to unpublished nodes.
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $sub_menu = str_replace('<ul class="', '<ul class="dropdown-menu ', $sub_menu);
  }
  if (preg_match('@^node/(\d+)$@', $element['#href'], $matches)) {
    $node = node_load((int) $matches[1]);
    if ($node && $node->status == NODE_NOT_PUBLISHED) {
      // There appear to be some inconsistency
      // sometimes the classes come through
      // as an array and sometimes as a string.
      if (empty($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = array();
      }
      elseif (is_string($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = explode(' ', $element['#localized_options']['attributes']['class']);
      }
      $element['#localized_options']['attributes']['class'][] = 'menu-node-unpublished';
    }
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  $output = html_entity_decode($output);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node(&$variables, $hook) {
  // For all content types.
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', 'external');
  // Node is a file.
  if ($variables['type'] == 'file') {
    _know4pol_ec_europa_preprocess_node_file($variables);
  }
}

/**
 * Preprocess node_file.
 *
 * Analyse legacy link content
 * and possible more info to display into the ECL block.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_node_file(&$variables) {
  $node = $variables['elements']['#node'];
  // Is file a link or a file ?
  $node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file($node);
  // Filetype icon.
  $_icon_css = $node->field_file_type[LANGUAGE_NONE][0]['taxonomy_term']->field_file_type_classname[LANGUAGE_NONE];
  // Default icon if no type.
  $node->file_type_css = "." . count($_icon_css) ? $_icon_css[0][value] : 'ecl-icon--file';

  // Languages versions.
  $translations = translation_node_get_translations($node->nid);
  foreach ($translations as $t) {
    // Other languages olny.
    if ($t->nid != $node->nid) {
      $t_node = node_load($t->nid);
      $t_node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file($t_node);
      $node->translations->data[] = $t_node;
    }
  }
}

/**
 * Preprocess fields field_file.
 *
 * Analyse legacy link content
 * and possible more info to display into the ECL block.
 *
 * @param node $node
 *   The node.
 *
 * @return array
 *   Parameters of the file (link and infos).
 */
function _know4pol_ec_europa_preprocess_node_file__field_file($node) {
  // Build link for ECL download
  // If file is external.
  if (count($node->field_is_legacy_link) && $node->field_is_legacy_link[LANGUAGE_NONE][0]['value']) {
    $link = $node->field_legacy_link[LANGUAGE_NONE][0][url];
  }
  // If internal and we have a file.
  elseif (count($node->field_file_file)) {
    $file = $node->field_file_file[LANGUAGE_NONE][0];
    $link = file_create_url($file['uri']);
    $size = _know4pol_ec_europa_file_size_human($file['filesize']);
  }
  $info = array();
  if ($size) {
    $info[] = $size;
  }

  $info = implode(' - ', $info);
  $info = (strlen($info)) ? '(' . $info . ')' : NULL;

  return array('link' => $link, 'info' => $info);
}

/**
 * Preprocess field data visualisation urls.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_field__field_vis_data_url__visualisation(&$variables) {

  $el = &$variables['items'][0]['#element'];
  $el['v_type'] = $variables['element']['#object']->field_vis_type[LANGUAGE_NONE][0]['value'];

  // Build data paramters for the visualisation types.
  switch ($el['v_type']) {
    case "Tableau":
      $matches = array();
      if (preg_match('/(.*?ec\.europa\.eu)(\/t\/.*?)\/.*?\/([^\?]+)/', $el['url'], $matches)) {
        $el['thost'] = urlencode($matches[1] . '/');
        $el['troot'] = htmlentities($matches[2]);
        $el['tname'] = htmlentities($matches[3]);
      }
      break;

    case "Highcharts":
      // No preprocess.
      break;
  }
}

/**
 * Provides a readable filesize text.
 *
 * From a number by reccurently dividing by a base.
 *
 * @param int $size
 *   The filesize in bytes.
 * @param int $i
 *   Default 0, can be used for overriding
 *   the start of the division if $size is already divided.
 * @param int $base
 *   Default 1024, the divider for next unit.
 *
 * @return string
 *   A string representing $size with the biggest unit possible.
 */
function _know4pol_ec_europa_file_size_human($size, $i = 0, $base = 1024) {
  // Iterate per base until it can't be divided anymore.
  for (; $size > $base; $i++) {
    $size /= $base;
  }
  // Return rounded number and unit.
  return round($size, $i > 0 ? 2 : 0) . ' ' .
    ["bytes", "KB", "MB", "GB", "TB", "PB", "><"][$i];
}
