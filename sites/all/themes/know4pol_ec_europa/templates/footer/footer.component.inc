<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_footer(&$variables, $hook) {
  $menu = menu_get_item();
  $variables['#atomium_recursive'] = TRUE;

  $variables_block_mapping = array(
    'footer_middle' => array('menu', 'menu-footer-middle'),
    'footer_right' => array('menu', 'menu-footer-right'),
  );

  foreach ($variables_block_mapping as $name => $data) {
    $variables[$name] = _atomium_block_get_render_array($data[0], $data[1]);
  }

  // Case 1 : Add the feedback form to the whole website,
  // except 3 content types (knowledge_centre, country, topic).
  // First get the group Id of the page if there is only one.
  $gid = "";
  if (isset($menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE]) && count($menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE] == 1)) {
    $gid = $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE][0]['target_id'];
  }
  // Then add the "Give us feedback" link.
  // We can't add the link directly to the footer_right menu,
  // as Atomium/EC_Europa footer links don't work with Tokens.
  if (drupal_lookup_path('source', 'give-us-feedback') != FALSE) {
    $variables['footer_right']['give-us-feedback'] = _know4pol_ec_europa_give_us_fedback_menu_link($gid, $menu);
  }

  // Case 2 : Add dedicated footer menus for the three content types.
  if (isset($menu['page_arguments'][0]->type) &&
      ($menu['page_arguments'][0]->type == 'knowledge_centre' ||
       $menu['page_arguments'][0]->type == 'topic' ||
       $menu['page_arguments'][0]->type == 'country')) {
    switch ($menu['page_arguments'][0]->type) {
      case 'knowledge_centre':
        $variables = _know4pol_ec_europa_make_footer_links_ks_homepage($variables, $menu);
        break;

      case 'topic':
      case 'country':
        $variables = _know4pol_ec_europa_make_footer_links_on_topic_country($variables, $menu);
        break;
    }
  }
}

/**
 * Make the footer for the KS home pages.
 *
 * @param array $variables
 *   The original variables.
 * @param array $menu
 *   The current page menu.
 *
 * @return array
 *   The original variables.
 */
function _know4pol_ec_europa_make_footer_links_ks_homepage(array $variables, array $menu) {
  // A) First change the site name to KS name on left side.
  $variables['footer_left']['title']['#text'] = $menu['page_arguments'][0]->title;
  $variables['footer_left']['title']['#path'] = $menu['page_arguments'][0]->path['alias'];
  // B) Then add the KS middle menu links.
  // Get first the menu links from the KS menu.
  $ks_middle_menulinks = _atomium_block_get_render_array('menu', 'menu-footer-middle-' . $menu['page_arguments'][0]->nid);
  if (!empty($ks_middle_menulinks)) {
    // Replace the theme suggestions from the original menu-footer-middle.
    $ks_middle_menulinks['#theme_wrappers'] = array(
      'menu_tree__menu_footer_middle__menu__menu_footer_middle',
      'block__menu__menu_footer_middle',
    );
    // Remove the block title.
    $ks_middle_menulinks['#block']->subject = "Follow us:";
    // Then replace the middle menu with the KS middle one.
    $variables['footer_middle'] = $ks_middle_menulinks;
  }
  else {
    unset($variables['footer_middle']);
  }
  // C) Finally add the KS right menu links programatically.
  $gid = $menu['page_arguments'][0]->nid;
  $group_path_alias = $menu['page_arguments'][0]->path['alias'];
  // Remove the orginal links.
  foreach ($variables['footer_right'] as $key => $value) {
    if (!(drupal_substr($key, 0, 1) == "#")) {
      unset($variables['footer_right'][$key]);
    }
  }
  // Add the KS "About" link.
  if (drupal_lookup_path('source', $group_path_alias . '/about') != FALSE) {
    $variables['footer_right']['about'] = _know4pol_ec_europa_about_menu_link($group_path_alias);
  }
  // Add the KS "Give us feedback" link.
  if (drupal_lookup_path('source', 'give-us-feedback') != FALSE) {
    $variables['footer_right']['give-us-feedback'] = _know4pol_ec_europa_give_us_fedback_menu_link($gid, $menu);
  }
  // Remove the contextual link if the menu is changed.
  if (isset($variables['footer_right']['about']) || isset($variables['footer_right']['give-us-feedback'])) {
    unset($variables['footer_right']['#contextual_links']);
  }
  return $variables;
}

/**
 * Make the footer for the Topic and Country content types.
 *
 * @param array $variables
 *   The original variables.
 * @param array $menu
 *   The current page menu.
 *
 * @return array
 *   The original variables.
 */
function _know4pol_ec_europa_make_footer_links_on_topic_country(array $variables, array $menu) {
  // A) First change the site name to KS name on left side.
  $variables['footer_left']['title']['#text'] = $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE][0]['label'];
  $variables['footer_left']['title']['#path'] = drupal_lookup_path('alias', $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE][0]['url']);
  // B) Then add the KS middle menu links.
  // Get first the menu links from the KS menu.
  $ks_middle_menulinks = _atomium_block_get_render_array('menu', 'menu-footer-middle-' . $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE][0]['target_id']);
  if (!empty($ks_middle_menulinks)) {
    // Replace the theme suggestions from the original menu-footer-middle.
    $ks_middle_menulinks['#theme_wrappers'] = array(
      'menu_tree__menu_footer_middle__menu__menu_footer_middle',
      'block__menu__menu_footer_middle',
    );
    // Remove the block title.
    $ks_middle_menulinks['#block']->subject = "Follow us:";
    // Then replace the middle menu with the KS middle one.
    $variables['footer_middle'] = $ks_middle_menulinks;
  }
  else {
    unset($variables['footer_middle']);
  }
  // C) Finally add the KS right menu links programatically.
  $gid = $menu['page_arguments'][0]->og_group_ref[LANGUAGE_NONE][0]['target_id'];
  $group_path_alias = drupal_lookup_path('alias', 'node/' . $gid);
  // Remove the orginal links.
  foreach ($variables['footer_right'] as $key => $value) {
    if (!(drupal_substr($key, 0, 1) == "#")) {
      unset($variables['footer_right'][$key]);
    }
  }
  // Add the KS "About" link.
  if (drupal_lookup_path('source', $group_path_alias . '/about') != FALSE) {
    $variables['footer_right']['about'] = _know4pol_ec_europa_about_menu_link($group_path_alias);
  }
  // Add the KS "Give us feedback" link.
  if (drupal_lookup_path('source', 'give-us-feedback') != FALSE) {
    $variables['footer_right']['give-us-feedback'] = _know4pol_ec_europa_give_us_fedback_menu_link($gid, $menu);
  }
  // Remove the contextual link if the menu is changed.
  if (isset($variables['footer_right']['about']) || isset($variables['footer_right']['give-us-feedback'])) {
    unset($variables['footer_right']['#contextual_links']);
  }
  return $variables;
}

/**
 * Get the "Give us feedback" menu link.
 *
 * @param string $gid
 *   The group id if available.
 * @param array $menu
 *   The current page.
 *
 * @return array
 *   The give-us-feedback menu link.
 */
function _know4pol_ec_europa_give_us_fedback_menu_link($gid, array $menu) {
  $menu_link = array(
    '#theme' => 'menu_link__menu_footer_right',
    '#attributes' => array(
      'class' => array(
        'last',
        'leaf',
      ),
    ),
    '#title' => 'Give us feedback',
    '#href' => 'give-us-feedback',
    '#localized_options' => array(
      'query' => array(
        'reported_page' => !empty(drupal_lookup_path('alias', $menu['href'])) ? drupal_lookup_path('alias', $menu['href']) : $menu['href'],
        'destination' => !empty(drupal_lookup_path('alias', $menu['href'])) ? drupal_lookup_path('alias', $menu['href']) : $menu['href'],
      ),
    ),
    '#below' => '',
  );
  if ($gid != "") {
    $menu_link['#localized_options']['query']['related_knowledge_service'] = $gid;
  }
  return $menu_link;
}

/**
 * Get the "Give us feedback" menu link.
 *
 * @param string $group_path_alias
 *   The group path alias.
 *
 * @return array
 *   The about menu link.
 */
function _know4pol_ec_europa_about_menu_link($group_path_alias) {
  $menu_link = array(
    '#theme' => 'menu_link__menu_footer_right',
    '#attributes' => array(
      'class' => array(
        'first',
        'last',
        'leaf',
      ),
    ),
    '#title' => 'About',
    '#href' => '/' . $group_path_alias . '/about',
    '#below' => '',
  );
  return $menu_link;
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
