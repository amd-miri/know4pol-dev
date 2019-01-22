<?php

/**
 * @file
 * registryonsteroids_alter.menu.inc
 */

/**
 * Recursive function that goes through all children of a Drupal's menu build.
 *
 * @param array $root_element
 *   The root element.
 *   Typical structure:
 *   $[$mlid]['#theme'] === 'menu_link__navigation'
 *   $['#theme_wrappers'][] = 'menu_tree__navigation'
 * @param callable $callback
 *   A custom callback to apply to each element.
 * @param string|null $root_element_key
 *   The root element key.
 * @param array $context
 *   The context.
 */
function registryonsteroids_alter_recursive_menu_tree(array &$root_element, callable $callback, $root_element_key = NULL, array &$context = []
) {
  $context += ['level' => 0];

  // Alter the menu tree element.
  $callback($root_element, $root_element_key, $context);

  foreach (element_children($root_element) as $sub_element_key) {
    if (!is_array($root_element[$sub_element_key])) {
      continue;
    }

    // Alter the menu link element.
    $callback($root_element[$sub_element_key], $sub_element_key, $context);

    if (empty($root_element[$sub_element_key]['#below'])) {
      continue;
    }

    // Alter the sub-tree.
    $context['level']++;
    registryonsteroids_alter_recursive_menu_tree($root_element[$sub_element_key]['#below'], $callback, $sub_element_key, $context);
    $context['level']--;
  }
}
