<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link(array &$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->remove('class', 'leaf');
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__menu_nexteuropa_inst_links__footer(array &$variables, $hook) {
  _know4pol_ec_europa_menu_link_footer_alter($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__nexteuropa_site_social_media__footer(array &$variables, $hook) {
  _know4pol_ec_europa_menu_link_footer_alter($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__nexteuropa_site_custom_links__footer(array &$variables, $hook) {
  _know4pol_ec_europa_menu_link_footer_alter($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__menu_nexteuropa_site_links__footer(array &$variables, $hook) {
  _know4pol_ec_europa_menu_link_footer_alter($variables);
}

/**
 * Alter specific menu link for the footer.
 *
 * @param array $variables
 *   The array of variables.
 */
function _know4pol_ec_europa_menu_link_footer_alter(array &$variables) {
  $variables['menu_link']['menu_link']['#options']['attributes']['class'][] = 'ecl-link--inverted';
}
