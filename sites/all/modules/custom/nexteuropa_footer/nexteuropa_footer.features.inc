<?php
/**
 * @file
 * nexteuropa_footer.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_footer_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
