<?php
/**
 * @file
 * nexteuropa_site_header.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_site_header_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
