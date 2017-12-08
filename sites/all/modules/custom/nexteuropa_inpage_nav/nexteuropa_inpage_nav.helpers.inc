<?php

/**
 * @file
 * Contains all helper functions used in nexteuropa inpage nav.
 */

/**
 * Function to render the inpage navigation.
 *
 * @param array $anchors
 *   The list of anchors to use.
 *
 * @return string
 *   Rendered inpage navigation markup.
 */
function _nexteuropa_inpage_nav_render($anchors) {
  if (is_array($anchors)) {
    // Initialize the block.
    $items = [];

    // Default link parameters, external TRUE is because it just makes the
    // anchors append.
    $default_link_attributes = [
      'attributes' => [
        'class' => [
          'inpage_nav__list-item',
        ],
      ],
      'external' => TRUE,
    ];

    // Loop our anchors. But we should replace possible bad parts from the id.
    foreach ($anchors as $heading) {
      $items[] = l(
        $heading['label'],
        '',
        array_merge($default_link_attributes, ['fragment' => $heading['id']])
      );
    }

    // Render config for the links.
    $variables = [
      'items' => $items,
      'attributes' => [
        'class' => [
          'nav',
          'inpage-nav__list',
        ],
      ],
    ];

    // Render config for the full block.
    $render_config = [
      '#theme' => 'inpage_nav_block',
      '#links' => theme('item_list', $variables),
      '#title' => t('Page Contents'),
      '#attached' => [
        'js' => [
          [
            'type' => 'file',
            'data' => drupal_get_path('module', 'nexteuropa_inpage_nav') . '/js/inpage_nav.js',
          ],
          [
            'type' => 'setting',
            'data' => [
              'inpage_navigation' => [
                'node_title' => '',
              ],
            ],
          ],
        ],
      ],
    ];

    return drupal_render($render_config);
  }
}

/**
 * Pre render function for inpage navigation.
 *
 * This will call required function to build the inpage navigation.
 *
 * @param array $element
 *   Render array for the entity.
 *
 * @return array
 *   Modified render array for the entity.
 */
function _nexteuropa_inpage_nav_build_inpage_nav($element) {
  // Get the anchors.
  $anchors = _nexteuropa_inpage_nav_get_anchors($element);

  // If we are able to build the markup. Then we should return it in the correct
  // place.
  if (!empty($anchors)) {
    $element['in_page_navigation'][0]['#markup'] = _nexteuropa_inpage_nav_render($anchors);
    return $element;
  }

  // If we cannot render it, we unset it.
  unset($element['in_page_navigation']);
  return $element;
}

/**
 * Helper function to get anchor from a field group.
 *
 * @param array $field_group
 *   The array containging field group information.
 *
 * @return mixed
 *   Array of anchors or false if none.
 */
function _nexteuropa_inpage_nav_get_field_group_anchor($field_group) {
  // A few things must match to be sure about the label.
  if (
    isset($field_group->format_settings['instance_settings']['show_label']) &&
    $field_group->format_settings['instance_settings']['show_label'] &&
    $field_group->format_settings['instance_settings']['label_element'] == NEXTEUROPA_INPAGE_NAV_DEPTH &&
    strpos($field_group->format_settings['instance_settings']['attributes'], 'id=') !== FALSE
  ) {
    // Set our label array. We have to t() the label here, as it is designed
    // like this by Field group module.
    // @codingStandardsIgnoreLine
    $label = isset($field_group->format_settings['label']) ? t($field_group->format_settings['label']) : $field_group->label;
    return [
      'id' => str_replace([
        'id=',
        '"',
      ], '', $field_group->format_settings['instance_settings']['attributes']),
      'label' => $label,
    ];
  }
  return FALSE;
}

/**
 * Helper function to get anchor from a field.
 *
 * @param array $field
 *   The array containing field information.
 * @param array $ds_field
 *   The array containing  ds_field information.
 *
 * @return mixed
 *   Array of anchors or false if none.
 */
function _nexteuropa_inpage_nav_get_field_anchors($field, $ds_field = NULL) {
  $anchors = [];
  // In case of a text summary we parse the code as well.
  if (isset($field['#field_type']) && in_array($field['#field_type'], ['text_with_summary', 'text_long'])) {
    // Loop over all the items as it might be multi value.
    foreach (element_children($field) as $item) {
      $anchors += isset($field[$item]['#markup']) ? _nexteuropa_inpage_nav_get_anchors_from_markup($field[$item]['#markup']) : NULL;
    }
  }
  // We should also check for the Label.
  if (isset($field['#label_display']) && $field['#label_display'] <> 'hidden') {
    // This is our master check, as we always require an ID to be able to
    // display anchor links. Also the element should be H2.
    if (
      isset($ds_field['formatter_settings']['ft']['lb-at']) &&
      strpos($ds_field['formatter_settings']['ft']['lb-at'], 'id=') !== FALSE &&
      isset($ds_field['formatter_settings']['ft']['lb-el']) &&
      $ds_field['formatter_settings']['ft']['lb-el'] == NEXTEUROPA_INPAGE_NAV_DEPTH
    ) {
      // Then depending on further config, we set our label.
      if (!empty($ds_field['formatter_settings']['ft']['lb'])) {
        $label = $ds_field['formatter_settings']['ft']['lb'];
      }
      else {
        $label = $field['#title'];
      }
      // We can already set the full anchor now..
      $anchors[] = [
        'id' => str_replace([
          'id=',
          '"',
        ], '', $ds_field['formatter_settings']['ft']['lb-at']),
        'label' => $label,
      ];
    }
  }

  // If we have anchors, we send them back.
  if (!empty($anchors)) {
    return [
      'weight' => intval($field['#weight']),
      'anchors' => $anchors,
    ];
  }
  return FALSE;
}

/**
 * This function goes over the element recursively and adds them to child array.
 *
 * @param array $childs
 *   Passed by reference, the childs.
 * @param bool $has_child
 *   Passed by reference, parameter indicating childs.
 * @param array $children
 *   The children to check for.
 * @param array $element
 *   The main element.
 * @param bool $parent
 *   The parent if any.
 */
function _nexteuropa_inpage_nav_recursive_anchors(&$childs, &$has_child, $children, $element, $parent = NULL) {
  // Check the children.
  foreach ($children as $field) {
    // If we were able to get a label from the helper we append them to the
    // childs array.
    if (isset($element[$field])) {
      $has_child = TRUE;
      if ($field_anchor = _nexteuropa_inpage_nav_get_field_anchors($element[$field])) {
        $childs[$field] = $field_anchor;
      }
    }

    // If we have a subgroup.
    if (isset($childs[$parent]) && $label = _nexteuropa_inpage_nav_get_field_group_anchor($element['#groups'][$field])) {
      // The weight should be the sub field minus one as it should come
      // above children.
      $childs[$field] = [
        'weight' => $childs[$parent]['weight'] - 1,
        'anchors' => [$label],
      ];
    }

    unset($element[$field]);

    if (drupal_substr($field, 0, 6) == 'group_') {
      _nexteuropa_inpage_nav_recursive_anchors($childs, $has_child, $element['#groups'][$field]->children, $element, $field);
    }
  }
}

/**
 * Helper function to parse a render array into an anchor list.
 *
 * @param array $element
 *   Render array for the entity.
 *
 * @return array
 *   The anchors that can be used for rendering.
 */
function _nexteuropa_inpage_nav_get_anchors($element) {
  // We load our ds field settings once.
  $ds_field_settings = ds_get_field_settings($element['#entity_type'], $element['#bundle'], $element['#view_mode']);
  $ordered_array = [];
  // Rebuild the full array to be in the correct order.
  foreach ($element['#groups'] as $group => $content) {

    // Skip those with a parent.
    if (!empty($element['#groups'][$group]->parent_name)) {
      continue;
    }

    // Reinitialize.
    $childs = [];
    $has_child = FALSE;

    _nexteuropa_inpage_nav_recursive_anchors($childs, $has_child, $content->children, $element);

    // Get our field group label.
    $label = _nexteuropa_inpage_nav_get_field_group_anchor($content);
    // If one passes, we know we are having an anchor.
    if ($has_child && ($label || !empty($childs))) {
      // Make sure that we already sort the childs.
      if (count($childs) > 1) {
        usort($childs, '_nexteuropa_inpage_nav_sort_by_weight');
      }
      // Add the group to our array, including label and child.
      $ordered_array[$group] = [
        'group' => $group,
        'weight' => intval($content->weight),
        'children' => $childs,
        'heading' => $label,
      ];
    }
  }
  // Allow other modules to alter the data.
  foreach (module_implements('nexteuropa_inpage_nav_add') as $module) {
    $ordered_array += module_invoke($module, 'nexteuropa_inpage_nav_add', $element, $ds_field_settings);
  }
  // Initialize.
  $field_inpage_nav = FALSE;
  // Loop over the rest of the fields, to make sure nothing is left out.
  // @todo: We have to check if we can merge this and the code above.
  foreach ($element as $field => $field_info) {
    if (is_array($field_info) && isset($field_info['#field_name'])) {
      $has_child = FALSE;
      // Get our specific ds field settings and pass them.
      $ds_field = isset($ds_field_settings[$field]) ? $ds_field_settings[$field] : NULL;
      // If we were able to get a label from the helper we append them to the
      // childs array.
      if ($field_anchor = _nexteuropa_inpage_nav_get_field_anchors($element[$field], $ds_field)) {
        // Search if the field is already in the field list.
        foreach ($ordered_array as $item) {
          if (isset($item['children']) && is_array($item['children'])) {
            foreach ($item['children'] as $in_fields => $in_fields_value) {
              if ($field == $in_fields) {
                $field_inpage_nav = TRUE;
              }
            }
          }
        }
        // Only add the field if its not there before.
        if (!$field_inpage_nav) {
          $has_child = TRUE;
          $childs[$field] = $field_anchor;
        }
      }

      // Remove it from our array so that we do not test for it again later.
      unset($element[$field]);

      if ($has_child) {
        // Make sure that we already sort the childs.
        if (isset($childs) && count($childs) > 0) {
          usort($childs, '_nexteuropa_inpage_nav_sort_by_weight');
          // Add the group to our array, including label and child.
          $ordered_array[$field] = [
            'weight' => intval($field_info['#weight']),
            'children' => $childs,
            'heading' => '',
          ];
        }
      }
    }
  }
  // Sort the array by weight.
  usort($ordered_array, '_nexteuropa_inpage_nav_sort_by_weight');

  // Initialize our anchors.
  $anchors = [];
  // Parse the fresh array to a simple version.
  foreach ($ordered_array as $item) {
    if (is_array($item['heading']) && isset($item['heading']['label'])) {
      $anchor = [
        'id' => $item['heading']['id'],
        'label' => $item['heading']['label'],
      ];
      array_push($anchors, $anchor);
    }
    if (is_array($item['children'])) {
      foreach ($item['children'] as $child) {
        foreach ($child['anchors'] as $anchor) {
          array_push($anchors, $anchor);
        }
      }
    }
  }
  return $anchors;
}

/**
 * Usort function to sort by weight.
 */
function _nexteuropa_inpage_nav_sort_by_weight($a, $b) {
  return $a['weight'] - $b['weight'];
}

/**
 * Helper function to get anchors from a piece of markup.
 *
 * @param string $markup
 *   The markup to be checked.
 *
 * @return array
 *   Array of anchors.
 */
function _nexteuropa_inpage_nav_get_anchors_from_markup($markup) {
  // Initialize our array.
  $inpage_nav_list = [];
  // Looking for:
  // H2 elements that have an id attribute or
  // DIV elements with id attributes thats first child is an H2.
  $pattern = "/<" . NEXTEUROPA_INPAGE_NAV_DEPTH . ".*?id=\"(.[^\"]*)\".*?>(.[^\<]*)<\/" . NEXTEUROPA_INPAGE_NAV_DEPTH . ">|<div.[^<]?id=\"(.[^\"]*)\".*?><" . NEXTEUROPA_INPAGE_NAV_DEPTH . ">(.*?)<\/" . NEXTEUROPA_INPAGE_NAV_DEPTH . ">/i";

  preg_match_all($pattern, $markup, $matches);

  foreach ($matches[1] as $i => $id) {
    $inpage_nav_list[] = [
      'id' => $matches[1][$i] . $matches[3][$i],
      'label' => strip_tags($matches[2][$i] . $matches[4][$i]),
    ];
  }

  return $inpage_nav_list;
}
