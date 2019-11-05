<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_page().
 */
function know4pol_ec_europa_preprocess_page(&$variables, $hook) {
  if (drupal_is_front_page()) {
    // Google site verification from theme settings.
    if (theme_get_setting('google_site_id_meta', 'know4pol_ec_europa')) {
      drupal_add_html_head(array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => 'google-site-verification',
          'content' => filter_xss(theme_get_setting('google_site_id_key', 'know4pol_ec_europa')),
        ),
      ), 'google-site-verification');
    }
  }
  // If this is a search page, add wrapper to results.
  elseif (isset($variables['page']['content']['system_main']['search_results'])) {
    $variables['page']['content']['system_main']['search_results']['search_results']['#prefix'] = '<ul class="ecl-list ecl-list--unstyled ecl-u-mv-m">';
    $variables['page']['content']['system_main']['search_results']['search_results']['#suffix'] = '</ul>';
  }

  // KNOW4POL-502: usage of CCK mandatody on all ec.europa pages.
  drupal_add_js('https://ec.europa.eu/wel/cookie-consent/consent.js', 'external');
}
