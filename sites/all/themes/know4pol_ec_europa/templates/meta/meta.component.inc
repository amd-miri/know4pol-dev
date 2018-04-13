<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_meta(&$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-meta--header');
}
