<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_page().
 */
function know4pol_ec_europa_preprocess_page(&$variables, $hook) {
  // If this is a search page, add wrapper to results.
  if (isset($variables['page']['content']['system_main']['search_results'])) {
    $variables['page']['content']['system_main']['search_results']['search_results']['#prefix'] = '<ul class="ecl-list ecl-list--unstyled ecl-u-mv-m">';
    $variables['page']['content']['system_main']['search_results']['search_results']['#suffix'] = '</ul>';
  }
}
