<?php

/**
 * @file
 * Solr/Facet related hooks for know4pol-search module.
 */

/**
 * Implements hook_apachesolr_facet_items_alter().
 */
function know4pol_search_facet_items_alter(&$build, &$settings) {
  // Content type facet.
  switch ($settings->facet) {
    case "bundle":
      if (isset($build['newsroom_item'])) {
        $build = _know4pol_search_splice_facet($build, 'im_field_newsroom_item_type', TRUE);
        // Remove original filter anyway.
        unset($build['newsroom_item']);
      }
      if (isset($build['topic'])) {
        $build = _know4pol_search_splice_facet($build, 'bm_field_type');
        // Remove original filter.
        unset($build['topic']);
      }
      break;

    case "sm_field_ks_related_topics":
      // Replace the available list by the created one.
      $build = _know4pol_search_facet_filter_field_ks_related_topics($build);
      break;
  }
}

/**
 * Implements know4pol_search_facetapi_enabled_facets_alter().
 */
function know4pol_search_facetapi_enabled_facets_alter(array &$enabled_facets, $searcher, $realm_name) {
  if ($searcher == 'apachesolr@solr') {
    if (isset($enabled_facets['bm_field_type']) && isset($enabled_facets['bundle'])) {
      $enabled_facets['bm_field_type']['label'] = $enabled_facets['bundle']['label'];
    }
    if (isset($enabled_facets['sm_og_vocabulary'])) {
      $enabled_facets['sm_og_vocabulary']['label'] = t('Specific taxonomy');
    }
  }
}

/**
 * Implements hook_facetapi_sort_info().
 */
function know4pol_search_facetapi_sort_info() {
  $sorts = array();
  $sorts['ogvocab'] = array(
    'label' => t('OG vocab taxonomy'),
    'callback' => '_know4pol_search_facetapi_sort_ogvocab',
    'description' => t('Sort by taxonomy created into OG vocab'),
    'weight' => -5,
  );

  return $sorts;
}

/**
 * Facetapi sort, by vid of term.
 *
 * @see uasort()
 */
function _know4pol_search_facetapi_sort_ogvocab(array &$a, array &$b) {
  global $_know4pol_search_vid;

  $ta = _know4pol_search_facetapi_load_term($a);
  $tb = _know4pol_search_facetapi_load_term($b);
  $va = (int) $_know4pol_search_vid[$ta->vid]->weight;
  $vb = (int) $_know4pol_search_vid[$tb->vid]->weight;

  // Compare weight of vocabularies or vid if same weight.
  return ($va == $vb) ? ($ta->vid == $tb->vid ? 0 : ($ta->vid > $tb->vid) ? 1 : -1) : (($va > $vb) ? 1 : -1);
}

/**
 * Implements hook_facetapi_filters().
 */
function know4pol_search_facetapi_filters() {
  return array(
    'exclude_og_vocab' => array(
      'handler' => array(
        'label' => t('Exclude specific og vocabularies'),
        'class' => 'Know4polSearchFacetapiExcludeOGVocab',
      ),
    ),
  );
}

/**
 * Implements hook_facetapi_widgets().
 */
function know4pol_search_facetapi_widgets() {
  return array(
    'know4pol_search_ogvocab_list' => array(
      'handler' => array(
        'label' => t('OG vocab taxonomy'),
        'class' => 'Know4polSearchFacetapiWidgetOGVocab',
        'query types' => array('term'),
      ),
    ),
  );
}

/**
 * Implements hook_apachesolr_query_prepare().
 */
function know4pol_search_apachesolr_query_prepare($query) {
  $menu_item = menu_get_item();
  // Determine which apache solR page is viewed.
  switch ($menu_item['map'][0]) {
    case 'events':
    case 'news':
      $query->setAvailableSort('ds_field_newsroom_item_date', array('title' => t('NR Date'), 'default' => 'desc'));
      $query->setSolrsort('ds_field_newsroom_item_date', 'desc');
      break;

    default:
      $query->setAvailableSort('ds_field_last_update', array('title' => t('Last update'), 'default' => 'desc'));
      $query->setSolrsort('ds_field_last_update', 'desc');
      break;

  }
}

/**
 * Implements hook_apachesolr_query_alter().
 */
function know4pol_search_apachesolr_query_alter($query) {
  $query->addParam('fl', 'ds_field_newsroom_item_date');
  $query->addParam('fl', 'ds_field_last_update');
}

/**
 * Implements hook_apachesolr_index_document_build_node().
 */
function know4pol_search_apachesolr_index_document_build_node(ApacheSolrDocument $document, $entity, $entity_type) {
  switch ($entity->type) {
    case 'newsroom_item':
      // Add signle field newsroom date in SolR index.
      $document->addField('ds_field_newsroom_item_date', apachesolr_date_iso($entity->field_newsroom_item_date[LANGUAGE_NONE][0]['value']));
      break;

    case 'publication':
      // KNOW4POL-452, make sure it's never set at midnight.
      $yeardate = strtotime($document->getField('dm_field_pub_dc_date_issued')['value'][0]);
      // @see facetapi_isodate()
      $document->setField('dm_field_pub_dc_date_issued', gmdate('Y-m-d\T01:00:00\Z', $yeardate));
      break;
  }

  // All content types.
  $document->addField('ds_field_last_update', apachesolr_date_iso(strtotime($entity->field_last_update[LANGUAGE_NONE][0]['value'])));
}

/**
 * Get list of the solar pages and urls.
 *
 * @return array
 *   Returns url and label.
 */
function _know4pol_search_get_solr_search_pages() {
  $search_pages = apachesolr_search_load_all_search_pages();
  foreach ($search_pages as $search_page) {
    $output[$search_page['search_path']] = $search_page['label'];
  }
  $output['search/site'] = 'All';
  return $output;
}

/**
 * Parse term_id from facetapi indexed term and load term.
 *
 * @param array &$facetapi_term
 *   The indexed_term value from facetapi.
 *
 * @return object
 *   The stored or loaded term by taxonomy_term_load().
 */
function _know4pol_search_facetapi_load_term(array &$facetapi_term) {
  global $_know4pol_search_vid;

  if (!isset($facetapi_term['term'])) {
    // Parse tid from indexed value.
    if (preg_match('/\:([0-9]+)$/', $facetapi_term['#indexed_value'], $r) != 1) {
      return NULL;
    }
    // Load term and store for next usage (performance)
    $facetapi_term['term'] = taxonomy_term_load($r[1]);

    // Need to store vocabulary data as well for sorting by weight.
    if (!isset($_know4pol_search_vid)) {
      $_know4pol_search_vid = array();
    }
    if (!isset($_know4pol_search_vid[$facetapi_term['term']->vid])) {
      $_know4pol_search_vid[$facetapi_term['term']->vid] = taxonomy_vocabulary_load($facetapi_term['term']->vid);
    }

  }
  return $facetapi_term['term'];
}

/**
 * Filter the field_ks_related_topics facet to only show the related KS topics.
 *
 * @param array $build
 *   The build array of the facet.
 *
 * @return array
 *   The topics of the chosen KS.
 */
function _know4pol_search_facet_filter_field_ks_related_topics(array $build) {
  $params = drupal_get_query_parameters();
  foreach ($params['f'] as $param) {
    $field = explode(':', $param);
    if ($field[0] == 'sm_og_group_ref') {
      $gid = $field[2];
    }
  }
  if ($gid) {
    $query = db_select('node', 'n')
      ->fields('n', array('nid'));
    $query->join('og_membership', 'ogm', 'ogm.etid = n.nid');
    $query->condition('ogm.gid', $gid, '=');
    $query->condition('n.type', 'topic', '=');
    $ks_topics = $query->execute()->fetchAll();
    $new_topic_list = array();
    foreach ($ks_topics as $topic) {
      $topic_item = 'node:' . $topic->nid;
      if (in_array($topic_item, array_keys($build))) {
        $new_topic_list[$topic_item] = $build[$topic_item];
      }
    }
    return $new_topic_list;
  }
}

/**
 * Splice facet items with another facet acting as subtypes.
 *
 * @param array $build
 *   The build array of the facet.
 * @param string $facet_name
 *   The facet machine name to get elements from.
 * @param bool $remove_self
 *   Whether to remove the param from the query, default no.
 *
 * @return array
 *   The new list of items.
 */
function _know4pol_search_splice_facet(array $build, $facet_name, $remove_self = FALSE) {
  $solr_pages = apachesolr_search_load_all_search_pages();

  if ($adapter = _know4pol_ec_europa_get_solr_instance()) {
    $searcher = $adapter->getSearcher();
    $nr_type = $adapter->getFacet(facetapi_facet_load($facet_name, $searcher));
    foreach ($nr_type->getBuild() as $key => $item) {
      // Get url for dedicated solR search page.
      foreach ($solr_pages as $solr_page) {
        if ($solr_page['label'] == $item['#markup'] || $solr_page['label'] == $item['#markup'] . 's') {
          $item['#path'] = $solr_page['search_path'];
          break;
        }
      }
      // Remove self ? Useful if target page and already filtered.
      // Loop could be avoided if sure that self is always last.
      if ($remove_self) {
        foreach ($item['#query']['f'] as $index => $value) {
          if ($value == $facet_name . ':' . $item['#indexed_value']) {
            unset($item['#query']['f'][$index]);
            break;
          }
        }
      }
      $build[$key] = $item;
    }
  }
  return $build;
}
