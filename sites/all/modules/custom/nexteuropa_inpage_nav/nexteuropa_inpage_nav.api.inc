<?php

/**
 * @file
 * This file contains examples of hooks nexteuropa_inpage_nav can implement.
 */

/**
 * Alter hook for the inpage navigation.
 *
 * @param array $element
 *   Render array for the entity.
 * @param array $ds_field_settings
 *   The ds field settings it is currently acting on.
 *
 * @return array
 *   The array returned should contain all the required information to put and
 *   render the inpage nav item in the correct place.
 *   {code}
 *     'weight': is the actual weight from the element, this should ideally come
 *       from the $element['field_name'].
 *     'heading': this array element exists out of 2 elements.
 *       'id': This is the id to the anchor.
 *       'label': The text to display in the inpage nav.
 *     'children': If the element has children, we can add those here, using
 *       the same structure as other elements. Only used for field groups.
 *   {code}
 */
function hook_nexteuropa_inpage_nav_add($element, $ds_field_settings) {
  // Example.
  return [
    $element['field_name']['#field_name'] => [
      'weight' => $element['field_name']['#weight'],
      'heading' => [
        'id' => 'bar',
        'label' => 'foo',
      ],
      'children' => '',
    ],
  ];
}
