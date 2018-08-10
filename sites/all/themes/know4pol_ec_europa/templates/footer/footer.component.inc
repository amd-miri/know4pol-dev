<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_footer(&$variables, $hook) {
  $variables['#atomium_recursive'] = TRUE;

  $variables_block_mapping = array(
    'footer_middle' => array('menu', 'menu-footer-middle'),
    'footer_right' => array('menu', 'menu-footer-right'),
  );

  foreach ($variables_block_mapping as $name => $data) {
    $variables[$name] = _atomium_block_get_render_array($data[0], $data[1]);
  }

  // Add dedicated footer menus for each knwoledeg service.
  $menu = menu_get_item();
  if (isset($menu['page_arguments']['0']->type) &&
      ($menu['page_arguments']['0']->type == 'knowledge_centre' ||
       $menu['page_arguments']['0']->type == 'topic' ||
       $menu['page_arguments']['0']->type == 'country')) {
    // Add the KS middle menu links.
    // Get first the menu links from the KS menu.
    $ks_middle_menulinks = _atomium_block_get_render_array('menu', 'menu-footer-middle-' . $menu['page_arguments'][0]->nid);
    // Replace the theme suggestions from the original menu-footer-middle.
    $ks_middle_menulinks['#theme_wrappers'] = $variables['footer_middle']['#theme_wrappers'];
    // Remove the block title.
    $ks_middle_menulinks['#block']->subject = "Follow us:";
    // Then replace the middle menu with the KS middle one.
    $variables['footer_middle'] = $ks_middle_menulinks;

    // Add the KS right menu links programatically.
    // Remove the orginal links.
    foreach ($variables['footer_right'] as $key => $value) {
      if (!(substr($key, 0, 1) == "#")) {
        unset($variables['footer_right'][$key]);
      }
    }
    // Add the KS "About" link.
    if (drupal_lookup_path('source', $menu['page_arguments'][0]->path['alias'] . '/about') != FALSE) {
      $variables['footer_right']['about'] = array(
        '#theme' => 'menu_link__menu_footer_right',
        '#attributes' => array(
          'class' => array(
            'first',
            'last',
            'leaf',
          ),
        ),
        '#title' => 'About',
        '#href' => '/' . $menu['page_arguments'][0]->path['alias'] . '/about',
        '#below' => '',
      );
    }
    // Add the KS "Give us feedback" link.
    if (drupal_lookup_path('source', 'give-us-feedback') != FALSE) {
      $variables['footer_right']['give-us-feedback'] = array(
        '#theme' => 'menu_link__menu_footer_right',
        '#attributes' => array(
          'class' => array(
            'first',
            'last',
            'leaf',
          ),
        ),
        '#title' => 'Give us feedback',
        '#href' => drupal_lookup_path('source', 'give-us-feedback') . '?knowledge_service=' . $menu['page_arguments'][0]->nid,
        '#below' => '',
      );
    }
  }
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__menu_footer_middle(&$variables, $hook) {
  $variables = _ec_europa_menu_link_footer_alter($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__menu_footer_right(&$variables, $hook) {
  $variables = _ec_europa_menu_link_footer_alter($variables);
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_footer_right(&$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-footer__menu');
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_tree__menu_footer_middle(&$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-footer__menu');
}
