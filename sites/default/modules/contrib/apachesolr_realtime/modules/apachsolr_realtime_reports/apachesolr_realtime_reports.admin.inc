<?php
/**
 * @file
 * Admin include file for Solr reports.
 */

/**
 * Implements report showing entities in Solr.
 *
 * @return string
 *   HTML table is returned as string.
 */
function apachesolr_realtime_reports() {
  // Initialise pager.
  $page = pager_find_page();
  $limit = 30;
  $offset = $page * $limit;


  // Define parameters for query.
  $params = array(
    'q.alt' => "*:*",
    'start' => $offset,
    'rows' => $limit,
    'fl' => 'bundle_name,label,entity_id,ss_name',
  );

  // Pass query parameters to the SolrBaseQuery class.
  $solr = apachesolr_get_solr();
  $query = new SolrBaseQuery('apachesolr', $solr, $params, $solrsort = 'ds_created desc', '');
  $query->page = $page;

  // Perform query and return results.
  $results = apachesolr_do_query($query);


  // Define table headers.
  $header = array(
    '0' => 'nid',
    '1' => 'Title',
    '2' => 'Bundle',
    '3' => 'Author',
  );

  $rows = array();
  foreach ($results['1']->response->docs as $return) {
    $rows[] = array(
      $return->entity_id,
      l($return->label, "node/" . $return->entity_id),
      $return->bundle_name,
      check_plain($return->ss_name),
    );
  }

  $result_count = $results['1']->response->numFound;
  pager_default_initialize($result_count, $limit);

  $output = array(
    'node_list' => array(
      '#header'  => $header,
      '#rows'    => $rows,
      '#caption' => t('Displaying records @start to @end of @count', array(
        '@start' => $offset + 1,
        '@end'   => (($offset + $limit) < $result_count) ? ($offset + $limit) : $result_count,
        '@count' => $result_count,
      )),
      '#empty'   => t('No records found in Apache Solr.'),
      '#theme'   => 'table',
    ),
    'pager' => array(
      '#theme' => 'pager',
    ),
  );

  return $output;
}
