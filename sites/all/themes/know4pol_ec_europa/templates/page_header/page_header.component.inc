<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_hook().
 */
function know4pol_ec_europa_atomium_theme_page_header() {
  return array(
    'page_header' => array(
      'variables' => array(
        'identity' => NULL,
        'title' => NULL,
        'introduction' => NULL,
        'meta' => NULL,
        'breadcrumb' => NULL,
        'full_banner' => FALSE,
      ),
      'template' => 'page-header',
    ),
  );
}

/**
 * Implements template_preprocess_page_header().
 */
function know4pol_ec_europa_preprocess_page_header(&$variables, $hook) {
  // Node is viewed.
  $menu_item = menu_get_item();
  if ($menu_item['path'] == 'node/%') {
    $node = $menu_item['page_arguments'][0];
    switch ($node->type) {
      case 'knowledge_centre':
        $variables['full_banner'] = TRUE;
        if (!empty($node->field_short_description[LANGUAGE_NONE][0]['value'])) {
          $variables['introduction'] = $node->field_short_description[LANGUAGE_NONE][0]['value'];
        }
        $variables['title'] = check_plain($node->field_ks_full_name[LANGUAGE_NONE][0]['value']);
    }
  }
  elseif (drupal_is_front_page()) {
    $variables['full_banner'] = TRUE;
  }
  // Or it's a SolR page.
  elseif ($adapter = _know4pol_ec_europa_get_solr_instance()) {
    // Full header.
    $variables['full_banner'] = TRUE;
    // And custom title.
    $id_suffix = $variables['identity'];
    // If in a KS search, append name of KS to title.
    if ($adapter = _know4pol_ec_europa_get_solr_instance()) {
      $searcher = $adapter->getSearcher();
      if ($facet = facetapi_facet_load('sm_og_group_ref', $searcher)) {
        if ($value = $adapter->getActiveItems($facet)) {
          $value = $adapter->getMappedValue('sm_og_group_ref', key($value));
          $id_suffix = $value['#markup'];
        }
      }
    }
    $variables['title'] = t('Search') . ' ' . $id_suffix;
    $variables['introduction'] = t('Refine your search result using the form, left.');
  }
}
