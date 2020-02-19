<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_block().
 */
function know4pol_ec_europa_preprocess_block(&$variables, $hook) {
  // Add template suggestion for search pages.
  if ($variables['elements']['#block']->bid == 'multisite_og_button-og-contextual-links') {
    $variables['content'] = preg_replace("/class\=\"ecl\-link\"/", "class=\"ecl-link ecl-link--standalone ecl-link-block__link\"", $variables['content']);
  }

  // Block specific.
  switch ($variables['block']->delta) {
    case 'ks_browse_by-browse_by_country':
      $variables['block']->inpage_anchor = t('Browse by country');
      $variables['block']->html_id = 'country';
      $variables['title']['#markup'] = t('Browse @ksname by country', array('@ksname' => menu_get_item()['page_arguments'][0]->title));
      break;

    case 'ks_browse_by-browse_by_topic':
      $variables['block']->inpage_anchor = t('Browse by topic');
      $variables['block']->html_id = 'topic';
      $variables['title']['#markup'] = t('Browse @ksname by topic', array('@ksname' => menu_get_item()['page_arguments'][0]->title));
      break;

    case 'ks_browse_by-browse_by_tool':
      $variables['block']->inpage_anchor = t('Browse tools');
      $variables['block']->html_id = 'tools';
      $variables['title']['#markup'] = t('Browse @ksname tools', array('@ksname' => menu_get_item()['page_arguments'][0]->title));
      break;
  }
}

/**
 * Implements hook_preprocess_block__content().
 */
function know4pol_ec_europa_preprocess_block__block__5__content(&$variables, $hook) {
  // Current search ?
  if (!$adapter = _know4pol_ec_europa_get_solr_instance()) {
    return;
  }

  $searcher = $adapter->getSearcher();
  $result_count = $adapter->getResultCount();
  $per_page = $adapter->getPageLimit();
  $page = $adapter->getPageNumber();
  $last_on_page = $page * $per_page;

  // Set variables from SolR.
  $variables['solr'] = array();
  $variables['solr']['max_page'] = $adapter->getPageTotal();
  $variables['solr']['result_count'] = $result_count;
  $variables['solr']['result_start'] = (($page - 1) * $per_page) + 1;
  $variables['solr']['result_end'] = $last_on_page > $result_count ? $result_count : $last_on_page;

  // Get all active facets.
  $facets_used = $adapter->getAllActiveItems();
  $facets_enabled = facetapi_get_enabled_facets($searcher);
  $facets = array();

  // Build collection.
  foreach ($facets_used as $key => $item) {
    $fname = $item['facets'][0];
    if (!isset($facets[$fname])) {
      $index = array('values' => array());
      // Get facet name.
      $index['facet'] = $facets_enabled[$fname];
      $facets[$fname] = $index;
    }
    $facets[$fname]['values'][] = array(
      'value' => $item['value'],
      'name' => $adapter->getMappedValue($fname, $item['value']),
      'removed_url' => _know4pol_ec_europa_build_query_facets(array_keys(array_diff_key($facets_used, array_flip((array) $key)))),
    );
  }

  if (count($facets)) {
    $variables['solr']['facets'] = $facets;
  }
  // Remove unnecessary ".ecl-editor" class.
  $variables['atomium']['attributes']['content']['class'] = array();
}

/**
 * Implements hook_preprocess_block__sidebar_first().
 */
function know4pol_ec_europa_preprocess_block__block__4__sidebar_first(&$variables, $hook) {
  // Current search ?
  if (!$adapter = _know4pol_ec_europa_get_solr_instance()) {
    return;
  }
  // Set variables from SolR.
  $variables['solr'] = array();
  $variables['solr']['result_count'] = $adapter->getResultCount();
}
