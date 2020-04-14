<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_lang_select_site(array &$variables, $hook) {
  // Languages list has been build in theme ec_europa in $languages.
  // Alter and disable all but "EN", see KNOW4POL-652.
  foreach ($variables['languages'] as $index => $item) {
    foreach ($item as $key => $value) {
      if (isset($value['#language']) && $value['#language']->language != 'en') {
        unset($variables['languages'][$index][$key]);
      }
    }
  }
}
