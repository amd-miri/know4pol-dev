<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Format date with begin and end value for ECL dateblocks.
 *
 * @param array $date
 *   The date field to format.
 *
 * @return string
 *   The formatted date with meta formater.
 */
function _know4pol_ec_europa_get_date_for_ecl(array $date) {
  // No end date or not different.
  $result = array();
  // Convert now to today at 00:00 so we can compare with the dates.
  $now = strtotime('today midnight');

  if ($date['value'] == $now || (
    isset($date['value2']) && ($date['value2'] > $now  && $date['value2'] <= $now))) {
    $result['type'] = 'ongoing';
  }
  elseif ($date['value'] < $now &&
    (!isset($date['value2']) || isset($date['value2']) && $date['value2'] < $now)) {
    $result['type'] = 'past';
  }

  // Start with first date.
  $result['weekday'] = date('D', $date['value']);
  $result['day'] = date('j', $date['value']);
  $result['month'] = date('M', $date['value']);
  $result['year'] = date('Y', $date['value']);
  if ($result['year'] > date('Y', $now)) {
    $result['next_year'] = TRUE;
  }

  if (isset($date['value2']) && $date['value2'] > $date['value']) {
    $result['weekday'] .= '&ndash;' . date('D', $date['value2']);
    $result['day'] .= '&ndash;' . date('j', $date['value2']);

    if (date('Y', $date['value2']) != $result['year']) {
      $result['year'] .= '&ndash;' . date('Y', $date['value2']);
      $result['month'] .= '&ndash;' . date('M', $date['value2']);
    }
    elseif (date('M', $date['value2']) != $result['month']) {
      $result['month'] .= '&ndash;' . date('M', $date['value2']);
    }
  }
  return $result;
}

/**
 * Provides a readable filesize text.
 *
 * From a number by reccurently dividing by a base.
 *
 * @param int $size
 *   The filesize in bytes.
 * @param int $i
 *   Default 0, can be used for overriding
 *   the start of the division if $size is already divided.
 * @param int $base
 *   Default 1024, the divider for next unit.
 *
 * @return string
 *   A string representing $size with the biggest unit possible.
 */
function _know4pol_ec_europa_file_size_human($size, $i = 0, $base = 1024) {
  // Iterate per base until it can't be divided anymore.
  for (; $size > $base; $i++) {
    $size /= $base;
  }
  // Return rounded number and unit.
  $size_types = array("bytes", "KB", "MB", "GB", "TB", "PB", "><");
  return round($size, $i > 0 ? 2 : 0) . ' ' .
    $size_types[$i];
}

/**
 * Get current SolR adapter API.
 *
 * @return object
 *   FacetapiAdapter object, null if not possible.
 */
function _know4pol_ec_europa_get_solr_instance() {
  // Checks there is a SolR instance and a search.
  $searcher = facetapi_get_active_searchers();
  if (!isset($searcher) || !count($searcher)) {
    return NULL;
  }
  $searcher = array_values($searcher);
  $searcher = $searcher[0];
  if (!facetapi_is_active_searcher($searcher)) {
    return NULL;
  }
  if (!$adapter = facetapi_adapter_load($searcher)) {
    return NULL;
  }
  if (!$adapter->searchExecuted($searcher)) {
    return NULL;
  }
  return $adapter;
}

/**
 * Build QueryString from array list of named facets.
 *
 * @param array $active_facets
 *   List of parameters to join for the URL.
 *
 * @return string
 *   The generated QueryString.
 */
function _know4pol_ec_europa_build_query_facets(array $active_facets) {
  foreach ($active_facets as $key => $value) {
    $active_facets[$key] = 'f[' . $key . ']=' . $active_facets[$key];
  }
  return implode('&', $active_facets);
}

/**
 * Implements template_url_outbound_alter().
 *
 * Remove appended redirection after creating the content from URI.
 */
function know4pol_ec_europa_url_outbound_alter(&$path, &$options, $original_path) {
  if (preg_match('/node.add.\+?(\S+)?/m', $path)) {
    unset($options['query']['destination']);
  }
}

/**
 * Returns TRUE if a path is external to Drupal and 'ec.europa.eu' domain.
 *
 * @param string $path
 *   The internal path or external URL being linked to, such as "node/34" or
 *   "http://example.com/foo".
 *
 * @return bool
 *   Boolean TRUE or FALSE, where TRUE indicates an external path.
 */
function _know4pol_ec_europa_url_is_external($path) {
  // Durpal knows this is internal ?
  if (!url_is_external($path)) {
    return FALSE;
  }
  // The host is this site or in europa.eu?
  $regex_internal = '/^(https?:\/{2})?((\w+\.)*europa.eu|' . str_replace('.', '\.', $_SERVER['HTTP_HOST']) . ')([\/\s:]|$).*?$/';
  return !preg_match($regex_internal, $path);
}
