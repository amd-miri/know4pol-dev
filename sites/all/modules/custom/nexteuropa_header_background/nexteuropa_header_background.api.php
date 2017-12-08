<?php

/**
 * @file
 * Contains all hook defenitions.
 */

/**
 * This hook can be used to define custom view modes.
 *
 * @return array
 *   Array with elements:
 *   'view_mode', the view mode to add the background for.
 *   'content_types', to limit it to the content type, * for all content types.
 */
function hook_nexteuropa_header_background_info() {
  return [
    [
      'view_mode' => 'full',
      'content_type' => '*',
    ],
  ];
}
