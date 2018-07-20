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
  
 $nid  = arg(1);
 dpm(current_path());
 dpm($nid);
 
    $node = node_load($nid);
    $group_id = $node->og_group_ref['und'][0]['target_id'];
    $group_node = node_load($group_id);
    $variables['twitter'] = $group_node->field_twitter['und'][0]['value'];
    $variables['blog'] = $group_node->field_blog['und'][0]['value'];
    $variables['about_page'] = $group_node->field_about_page['und'][0]['value'];
    $variables['group_title'] = $group_node->title;
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
