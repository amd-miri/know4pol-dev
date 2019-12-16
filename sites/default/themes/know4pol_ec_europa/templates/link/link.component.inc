<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function know4pol_ec_europa_preprocess_link(array &$variables, $hook) {
  $variables['atomium']['attributes']['element']->append('class', 'ecl-link');

  // Add the class for the external links.
  if (_know4pol_ec_europa_url_is_external($variables['path'])
    && (!$variables['atomium']['attributes']['element']->exists('class', 'ecl-icon'))
    && (!$variables['atomium']['attributes']['element']->exists('class', 'ecl-icon-social'))
  ) {
    $variables['atomium']['attributes']['element']->append('class', 'ecl-link--external');
  }

  if (isset($variables['options']['attributes'])) {
    $variables['atomium']['attributes']['element']->merge($variables['options']['attributes']);
  }
}
