<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function know4pol_ec_europa_atomium_theme_tags() {
  return array(
    'tags' => array(
      'variables' => array(
        'label' => '',
        'items' => array(),
      ),
      'template' => 'tags',
    ),
  );
}

/**
 * Implements hook_atomium_definition_hook().
 */
function know4pol_ec_europa_atomium_definition_tags() {
  return array(
    'label' => 'Tags',
    'description' => 'Tags template.',
    'disable' => TRUE,
  );
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_tags(&$variables, $hook) {
  // Store initial items.
  $variables['tags'] = $variables['items'];
  $variables['atomium']['attributes']['wrapper']->append('class', 'eclz-tag');
  $variables['atomium']['attributes']['title']->append('class', 'eclz-tag__label');

  foreach ($variables['items'] as $key => $item) {
    $variables['items'][$key] = array(
      '#theme' => _atomium_extend_theme_hook('link', $variables['theme_hook_original']),
    // $item['value'],.
      '#text' => 'noooooo';
      '#path' => $item['href'],
    );
  };
}
