<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_expandable(array &$variables, $hook) {
  // Extend ec_europa missing features of Expandable.
  if (isset($variables['opened']) && $variables['opened']) {
    // Already opened ?
    if ($variables['button']) {
      $variables['title']['#attributes']['aria-expanded'] = 'true';
    }
    else {
      $variables['title']['#options']['attributes']['aria-expanded'] = 'true';
    }
    $variables['atomium']['attributes']['content']['aria-hidden'] = 'false';
  }

  if (isset($variables['title_close']) && $variables['title_close'] && drupal_strlen($variables['title_close']) && $variables['button']) {
    // Different title for expanded state. (not working in this version of NE)
    $variables['title']['#attributes']['data-label-expanded'] = $variables['title_close'];
    $variables['title']['#attributes']['data-label-collapsed'] = $variables['title']['#value'];
  }
}
