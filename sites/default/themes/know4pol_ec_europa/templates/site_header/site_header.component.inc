<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_site_header(array &$variables, $hook) {
  // KNOW4POL-501.
  unset($variables['site_switcher']);
}
