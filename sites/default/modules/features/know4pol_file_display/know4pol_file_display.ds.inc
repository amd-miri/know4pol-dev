<?php

/**
 * @file
 * know4pol_file_display.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function know4pol_file_display_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'featured';
  $ds_view_mode->label = 'Featured';
  $ds_view_mode->entities = array(
    'node' => 'node',
    'file' => 'file',
  );
  $export['featured'] = $ds_view_mode;

  return $export;
}
