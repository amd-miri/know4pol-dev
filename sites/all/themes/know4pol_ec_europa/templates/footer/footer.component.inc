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

  // Add dedicated footer menus for each knowledge service.
  $menu = menu_get_item();
  // First change the site name to KS name on left side.
  if (isset($menu['page_arguments']['0']->type)) {
    switch ($menu['page_arguments']['0']->type) {
      case 'knowledge_centre':
        $variables['footer_left']['title']['#text'] = $menu['page_arguments']['0']->title;
        $variables['footer_left']['title']['#path'] = $menu['page_arguments']['0']->path['alias'];
        break;

      case 'topic':
      case 'country':
        $variables['footer_left']['title']['#text'] = $menu['page_arguments']['0']->og_group_ref[LANGUAGE_NONE]['0']['label'];
        $variables['footer_left']['title']['#path'] = drupal_lookup_path('alias', $menu['page_arguments']['0']->og_group_ref[LANGUAGE_NONE]['0']['url']);
        break;
    }
  }
  // Then add the KS middle menu links.
  if (isset($menu['page_arguments']['0']->type) &&
      ($menu['page_arguments']['0']->type == 'knowledge_centre' ||
       $menu['page_arguments']['0']->type == 'topic' ||
       $menu['page_arguments']['0']->type == 'country')) {
    // Get first the menu links from the KS menu.
    if ($menu['page_arguments']['0']->type == 'knowledge_centre') {
      $ks_middle_menulinks = _atomium_block_get_render_array('menu', 'menu-footer-middle-' . $menu['page_arguments'][0]->nid);
    }
    else {
      $ks_middle_menulinks = _atomium_block_get_render_array('menu', 'menu-footer-middle-' . $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]['0']['target_id']);
    }
    if (!empty($ks_middle_menulinks)) {
      // Replace the theme suggestions from the original menu-footer-middle.
      $ks_middle_menulinks['#theme_wrappers'] = $variables['footer_middle']['#theme_wrappers'];
      // Remove the block title.
      $ks_middle_menulinks['#block']->subject = "Follow us:";
      // Then replace the middle menu with the KS middle one.
      $variables['footer_middle'] = $ks_middle_menulinks;
    }
    else {
      unset($variables['footer_middle']);
    }
    // Finally add the KS right menu links programatically.
    // Remove the orginal links.
    foreach ($variables['footer_right'] as $key => $value) {
      if (!(drupal_substr($key, 0, 1) == "#")) {
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
