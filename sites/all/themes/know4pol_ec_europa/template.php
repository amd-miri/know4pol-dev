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
}
