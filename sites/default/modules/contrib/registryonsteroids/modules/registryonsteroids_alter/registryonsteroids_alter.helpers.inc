<?php

/**
 * @file
 * registryonsteroids_alter.helpers.inc
 */

/**
 * Extend the #theme_wrappers property of an element.
 *
 * @param array $element
 *   The element.
 * @param string[] $suggestions_parts
 *   The suggestions parts.
 */
function _registryonsteroids_alter_extend_theme_wrappers_property_with_suggestions(array &$element, array $suggestions_parts) {
  if (!isset($element['#theme_wrappers']) || !is_array($element['#theme_wrappers'])) {
    return;
  }

  foreach ($element['#theme_wrappers'] as &$hook_or_hooks) {
    _registryonsteroids_alter_extend_value_with_suggestions(
      $hook_or_hooks,
      $suggestions_parts);
  }
}

/**
 * Extend the #theme property of an element.
 *
 * @param array $element
 *   The element.
 * @param string[] $suggestions_parts
 *   The suggestions parts.
 */
function _registryonsteroids_alter_extend_theme_property_with_suggestions(array &$element, array $suggestions_parts) {
  if (!isset($element['#theme'])) {
    return;
  }

  _registryonsteroids_alter_extend_value_with_suggestions(
    $element['#theme'],
    $suggestions_parts);
}

/**
 * Extends strings with an array of suggestions.
 *
 * @param string|string[] $hook_or_hooks
 *   The hook or hooks to extend.
 * @param string[] $suggestion_parts
 *   The suggestions to extend the base string with.
 *
 * @example
 *   $base = 'block';
 *   $suggestions_parts = ['system', 'main-menu'];
 *
 *   The result will be: 'block__system__main_menu'
 *
 *   Quick note about the drupal_strtolower() call:
 *   We must ensure lowercase values because get_defined_functions()
 *   in drupal_group_functions_by_prefix() returns functions in lower case.
 *
 * @see http://php.net/manual/en/function.get-defined-functions.php
 */
function _registryonsteroids_alter_extend_value_with_suggestions(&$hook_or_hooks, array $suggestion_parts) {
  $suffix = '';

  foreach ($suggestion_parts as $suggestion_part) {
    $suggestion_part = strtolower(
      trim(
        preg_replace('@\W@', '_', $suggestion_part),
        '_'
      )
    );

    if ('' === $suggestion_part) {
      continue;
    }

    $suffix .= '__' . $suggestion_part;
  }

  if (is_string($hook_or_hooks)) {
    $hook_or_hooks .= $suffix;
  }
  elseif (is_array($hook_or_hooks)) {
    // @todo Do we really want to append the suffix to every hook in the array?
    $hook_or_hooks = array_map(
      function ($hook) use ($suffix) {
        return $hook . $suffix;
      },
      $hook_or_hooks
    );
  }
}

/**
 * Custom helper function.
 *
 * This helper updates the render array of a block so
 * block preprocess callbacks are correctly processed.
 *
 * @param array $block_array
 *   The original block render array.
 * @param string|null $region
 *   The region where the block is placed.
 */
function _registryonsteroids_alter_update_block_render_array(array &$block_array, $region = NULL) {
  $suggestions_parts = [
    $region,
    $block_array['#block']->module,
    $block_array['#block']->delta,
  ];

  if (isset($block_array['#theme'])) {
    $suggestions_parts = array_merge($suggestions_parts, (array) $block_array['#theme']);
  }

  _registryonsteroids_alter_extend_theme_wrappers_property_with_suggestions(
    $block_array,
    $suggestions_parts);
}

/**
 * Try to find information about the current page being viewed.
 *
 * This function will detect if an entity is displayed.
 * If an entity is displayed it will return an array containing:
 *  - The entity type
 *  - The entity info array
 *  - The entity itself.
 *
 * @return array|false
 *   The array if an entity is found, FALSE otherwise.
 */
function registryonsteroids_alter_menu_get_entity() {
  $return = FALSE;
  $item = menu_get_item();
  $item['load_functions'] = (array) $item['load_functions'];
  $load_functions = array_values($item['load_functions']);

  if (NULL === $load_functions) {
    return $return;
  }

  if ([] === $load_functions) {
    return $return;
  }

  $arg_position = array_search(
    $load_functions[0],
    $item['load_functions'],
    TRUE
  );

  foreach (entity_get_info() as $entity_name => $entity_info) {
    if ($entity_info['load hook'] !== $load_functions[0]) {
      continue;
    }

    if (($obj = menu_get_object($entity_name, $arg_position)) && is_object($obj)) {
      $return = [
        'entity' => $obj,
        'entity type' => $entity_name,
        'entity info' => $entity_info,
      ];
    }
  }

  return $return;
}

/**
 * Recursive element_children() function.
 *
 * As the default element_children() from Drupal is fine for single dimension
 * arrays, this function deal with multiple dimensions arrays.
 * It applies a callback to each Drupal element found in it.
 * The variable $context['parents'] of type string[] will hold the parents
 * hierarchy of the element.
 *
 * @param array $root_element
 *   The root element.
 * @param callable $callback
 *   A custom callback to apply to each element.
 * @param string|null $root_element_key
 *   The root element key.
 * @param array $context
 *   The context.
 */
function registryonsteroids_alter_recursive_element_children(array &$root_element, callable $callback, $root_element_key = NULL, array &$context = []) {
  $context += ['parents' => []];
  $context['parents'][$root_element_key] = &$root_element;

  $callback($root_element, $root_element_key, $context);

  foreach (element_children($root_element) as $sub_element_key) {
    if (!is_array($root_element[$sub_element_key])) {
      continue;
    }
    registryonsteroids_alter_recursive_element_children(
      $root_element[$sub_element_key],
      $callback,
      $sub_element_key,
      $context
    );
  }

  array_pop($context['parents']);
}

/**
 * Recursive function that goes through all children of a Drupal's menu build.
 *
 * @param array $root_element
 *   The root element.
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

  $callback($root_element, $root_element_key, $context);

  foreach (element_children($root_element) as $sub_element_key) {
    if (!is_array($root_element[$sub_element_key])) {
      continue;
    }

    registryonsteroids_alter_recursive_menu_tree($root_element[$sub_element_key], $callback, $sub_element_key, $context);

    if (!isset($root_element[$sub_element_key]['#below'])) {
      continue;
    }

    $context['level']++;
    registryonsteroids_alter_recursive_menu_tree($root_element[$sub_element_key]['#below'], $callback, $sub_element_key, $context);
    $context['level']--;
  }
}

/**
 * Populate an element with a specific pre-render callback.
 *
 * @param array $element
 *   The Drupal element.
 */
function _registryonsteroids_alter_add_default_pre_render_callback(array &$element) {
  $element += ['#pre_render' => []];
  // Using a non numeric key to avoid duplicates.
  $element['#pre_render']['_registryonsteroids_alter_element_pre_render'] = '_registryonsteroids_alter_element_pre_render';
}

/**
 * Populate an element with default pre render variables.
 *
 * @param array $element
 *   The Drupal element.
 */
function _registryonsteroids_alter_add_default_pre_render_variables(array &$element) {
  $element += ['#registryonsteroids' => []];
  $element['#registryonsteroids'] += ['suggestions' => []];
  $element['#registryonsteroids']['suggestions'] += ['theme' => []];
  $element['#registryonsteroids']['suggestions'] += ['theme_wrappers' => []];
}

/**
 * Pre-render callback.
 *
 * @param array $element
 *   The Drupal element.
 *
 * @return array
 *   The Drupal element.
 */
function _registryonsteroids_alter_element_pre_render(array $element) {
  $suggestions_page = _registryonsteroids_get_current_page_suggestions();

  _registryonsteroids_alter_add_default_pre_render_variables($element);

  $suggestions_theme_wrappers = array_merge(
    $element['#registryonsteroids']['suggestions']['theme_wrappers'],
    $suggestions_page
  );

  drupal_alter(
    'registryonsteroids_theme_wrappers_suggestions',
    $suggestions_theme_wrappers,
    $element
  );

  _registryonsteroids_alter_extend_theme_wrappers_property_with_suggestions(
    $element,
    $suggestions_theme_wrappers
  );

  $suggestions_theme = array_merge(
    isset($element['#tag']) ? (array) $element['#tag'] : [],
    $element['#registryonsteroids']['suggestions']['theme'],
    $suggestions_page
  );

  drupal_alter(
    'registryonsteroids_theme_suggestions',
    $suggestions_theme,
    $element
  );

  _registryonsteroids_alter_extend_theme_property_with_suggestions(
    $element,
    $suggestions_theme
  );

  return $element;
}

/**
 * Custom pre render callback for hook_form_alter().
 *
 * @param array $form
 *   The form.
 *
 * @return array
 *   The form.
 */
function _registryonsteroids_alter_form_alter_pre_render(array $form) {
  $context = [
    'form' => $form,
    'suggestions parts' => [
      $form['#id'],
    ],
  ];

  _registryonsteroids_alter_add_default_pre_render_variables($form);

  registryonsteroids_alter_recursive_element_children(
    $form,
    function (&$element, $element_key, &$recursive_context) use ($context) {
      _registryonsteroids_alter_add_default_pre_render_variables($element);

      $element['#registryonsteroids']['suggestions']['theme'] = array_merge(
        array_filter(array_keys($recursive_context['parents'])),
        $context['suggestions parts'],
        $element['#registryonsteroids']['suggestions']['theme']
      );

      $type = [];
      if (isset($element['#type'])) {
        $type[] = $element['#type'];

        if (isset($element['#theme'])) {
          if ($element['#theme'] !== $element['#type']) {
            $type = array_merge(
              $type,
              (array) $element['#theme']
            );
          }
        }
      }

      $element['#registryonsteroids']['suggestions']['theme_wrappers'] = array_merge(
        $type,
        array_filter(array_keys($recursive_context['parents'])),
        $context['suggestions parts'],
        $element['#registryonsteroids']['suggestions']['theme_wrappers']
      );
    },
    NULL,
    $context
  );

  return $form;
}

/**
 * Get suggestions of the current page.
 *
 * Currently only handles when an entity is viewed, it could be extended to
 * other types of pages like Panels, Views, etc etc...
 *
 * @return string[]
 */
function _registryonsteroids_get_current_page_suggestions() {
  $page_suggestions_parts = [];

  // Add suggestions if an entity is found on the current page.
  if ($entity = registryonsteroids_alter_menu_get_entity()) {
    $page_suggestions_parts[] = $entity['entity type'];

    if (isset($entity['entity']->{$entity['entity info']['entity keys']['bundle']})) {
      $page_suggestions_parts[] = $entity['entity']->{$entity['entity info']['entity keys']['bundle']};
    }
  }

  return array_merge(
    $page_suggestions_parts,
    explode('/', $_GET['q'])
  );
}
