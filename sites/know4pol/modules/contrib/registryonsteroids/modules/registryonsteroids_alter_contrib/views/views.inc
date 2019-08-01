<?php

/**
 * @file
 * Views.inc.
 */

/**
 * Implements hook_views_pre_render().
 *
 * @param \view $view
 *   The view object.
 */
function registryonsteroids_alter_contrib_views_pre_render(\view $view) {
  $display = $view->display[$view->current_display];

  $suggestions_parts = [
    $view->name,
    $display->display_plugin,
  ];

  if ($display->id !== $display->display_plugin) {
    $suggestions_parts[] = $display->id;
  }

  if (isset($view->style_plugin->definition['theme'])) {
    _registryonsteroids_alter_extend_value_with_suggestions(
      $view->style_plugin->definition['theme'],
      $suggestions_parts
    );

    array_unshift(
      $suggestions_parts,
      $view->style_plugin->definition['theme']
    );
  }

  if (isset($view->display_handler->definition['theme'])) {
    _registryonsteroids_alter_extend_value_with_suggestions(
      $view->display_handler->definition['theme'],
      $suggestions_parts
    );
  }
}
