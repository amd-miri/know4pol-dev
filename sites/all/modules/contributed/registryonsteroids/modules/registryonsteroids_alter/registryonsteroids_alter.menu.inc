<?php

/**
 * @file
 * registryonsteroids_alter.menu.inc
 */

/**
 * Copy of the function menu_tree().
 *
 * This allows to pass a context variables to sub-functions calls.
 *
 * @param string $menu_name
 *   The menu name.
 * @param array $context
 *   The context.
 *
 * @see https://api.drupal.org/api/drupal/includes%21menu.inc/function/menu_tree/7.x
 *
 * @return mixed
 */
function registryonsteroids_menu_tree($menu_name, array $context = []) {
  $menu_output = &drupal_static(__FUNCTION__, []);

  $context['menu_name'] = $menu_name;

  if (!isset($menu_output[$menu_name])) {
    $menu_output[$menu_name] = registryonsteroids_menu_tree_output(
      menu_tree_page_data($menu_name),
      $context
    );
  }

  return $menu_output[$menu_name];
}

/**
 * Copy of the function menu_tree_output().
 *
 * This allows to pass a context variables to sub-functions calls.
 *
 * @param array $tree
 *   The menu tree.
 * @param array $context
 *   The context.
 *
 * @see https://api.drupal.org/api/drupal/includes%21menu.inc/function/menu_tree_output/7.x
 *
 * @return array
 */
function registryonsteroids_menu_tree_output(array $tree, array $context = []) {
  // Call to the original function.
  $build = menu_tree_output($tree);

  $context += ['suggestions parts' => []];

  // Alteration of the menu build array.
  registryonsteroids_alter_recursive_menu_tree(
    $build,
    function (&$element, $key, $recursive_context) {
      _registryonsteroids_alter_add_default_pre_render_callback($element);
      _registryonsteroids_alter_add_default_pre_render_variables($element);

      $element['#registryonsteroids']['suggestions']['theme_wrappers'] = array_merge(
        $element['#registryonsteroids']['suggestions']['theme'],
        $element['#registryonsteroids']['suggestions']['theme_wrappers'],
        [
          $recursive_context['block']->module,
          $recursive_context['block']->delta,
          $recursive_context['block']->region,
          'level' . $recursive_context['level'],
        ],
        $recursive_context['suggestions parts']
      );

      $element['#registryonsteroids']['suggestions']['theme'] = array_merge(
        $element['#registryonsteroids']['suggestions']['theme'],
        [
          'level' . $recursive_context['level'],
        ],
        $recursive_context['suggestions parts']
      );
    },
    NULL,
    $context
  );

  return $build;
}
