<?php

/**
 * @file
 * know4pol_file_display.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function know4pol_file_display_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}
