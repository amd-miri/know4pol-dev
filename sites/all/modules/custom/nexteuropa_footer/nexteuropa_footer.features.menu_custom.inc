<?php
/**
 * @file
 * nexteuropa_footer.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function nexteuropa_footer_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-nexteuropa-inst-links.
  $menus['menu-nexteuropa-inst-links'] = array(
    'menu_name' => 'menu-nexteuropa-inst-links',
    'title' => 'European Union',
    'description' => 'Links to be put in the footer',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-nexteuropa-inst-links.
  $menus['menu-nexteuropa-site-links'] = array(
    'menu_name' => 'menu-nexteuropa-site-links',
    'title' => 'European Commission',
    'description' => 'Links to be put in the footer',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-nexteuropa-service-links.
  $menus['menu-nexteuropa-service-links'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'title' => 'Nexteuropa service links',
    'description' => 'Links to be put in the footer',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Exported menu: menu-nexteuropa-social-media.
  $menus['menu-nexteuropa-social-media'] = array(
    'menu_name' => 'menu-nexteuropa-social-media',
    'title' => 'Follow the European Commission',
    'description' => 'List of social networks links for the European Commission',
    'language' => 'und',
    'i18n_mode' => 5,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('European Union');
  t('Follow the European Commission');
  t('Links to be put in the footer');
  t('List of social networks links for the European Commission');
  t('Nexteuropa service links');

  return $menus;
}
