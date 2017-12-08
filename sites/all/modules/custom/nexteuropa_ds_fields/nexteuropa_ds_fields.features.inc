<?php
/**
 * @file
 * nexteuropa_ds_fields.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_ds_fields_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}
