<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_service_links(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables, TRUE);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_service_tools(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables, TRUE);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__nexteuropa_site_social_media(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables, TRUE);
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-footer__social-links');
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_social_media(&$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables, TRUE);
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-footer__social-links');
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__nexteuropa_site_custom_links(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_site_links(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_inst_links(array &$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer($variables);
}

/**
 * Common preproces for menu_trees in footer region.
 *
 * @param array $variables
 *   Variables from the original hook.
 * @param bool $inline
 *   Inline links switch, default no.
 */
function _know4pol_ec_europa_preprocess_menu_tree__footer(array &$variables, $inline = FALSE) {
  $variables['atomium']['attributes']['wrapper']->append(
    'class',
    array_merge(
      array(
        'ecl-footer__list',
        'ecl-list',
        'ecl-list--unstyled',
      ),
      $inline ? array(
        'ecl-list--inline',
        'ecl-footer__list--inline',
      ) : array()
    )
  );
}
