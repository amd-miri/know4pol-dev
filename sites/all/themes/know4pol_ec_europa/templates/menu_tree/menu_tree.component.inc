<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_menu_tree().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_site_links__menu__menu_nexteuropa_site_links__footer__page(&$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer__page($variables);
}

/**
 * Implements template_preprocess_menu_tree().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_social_media__menu__menu_nexteuropa_social_media__footer__page(&$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer__page($variables);
  $variables['atomium']['attributes']['wrapper']->append(
    'class',
    array(
      'ecl-list--inline',
      'ecl-footer__list--inline',
      'ecl-footer__social-links',
    )
  );
}

/**
 * Implements template_preprocess_menu_tree().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_nexteuropa_inst_links__menu__menu_nexteuropa_inst_links__footer__page(&$variables, $hook) {
  _know4pol_ec_europa_preprocess_menu_tree__footer__page($variables);
}

/**
 * Common preproces for menu_trees.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_menu_tree__footer__page(array &$variables) {

  $variables['atomium']['attributes']['wrapper']->append(
    'class',
    array(
      'ecl-footer__list',
      'ecl-list',
      'ecl-list--unstyled',
    )
  );
}
