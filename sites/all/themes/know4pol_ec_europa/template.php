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
 * Preprocess fields field_file.
 *
 * Analyse legacy link content
 * and possible more info to display into the ECL block.
 *
 * @param array $field_is_legacy_link
 *   The field field_is_legacy_link of the content.
 * @param array $field_legacy_link
 *   The field field_legacy_link of the content.
 * @param array $field_file_file
 *   The field field_file_file of the content.
 *
 * @return array
 *   Parameters of the file (link and infos).
 */
function _know4pol_ec_europa_preprocess_node_file__field_file(array $field_is_legacy_link, array $field_legacy_link, array $field_file_file) {
  // Build link for ECL download.
  // If file is external.
  if (count($field_is_legacy_link) && $field_is_legacy_link[LANGUAGE_NONE][0]['value']) {
    $link = $field_legacy_link[LANGUAGE_NONE][0]['url'];
  }
  // If internal and we have a file.
  elseif (count($field_file_file)) {
    $file = $field_file_file[LANGUAGE_NONE][0];
    $link = file_create_url($file['uri']);
    $size = _know4pol_ec_europa_file_size_human($file['filesize']);
  }
  $info = array();
  if (isset($size)) {
    $info[] = $size;
  }

  $info = implode(' - ', $info);
  $info = (drupal_strlen($info)) ? '(' . $info . ')' : NULL;

  return array('link' => $link, 'info' => $info);
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
  return round($size, $i > 0 ? 2 : 0) . ' ' .
    ["bytes", "KB", "MB", "GB", "TB", "PB", "><"][$i];
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
  $searcher = array_values($searcher)[0];
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
 * Preprocess hook for file entities.
 */
function know4pol_ec_europa_preprocess_file_entity(&$variables) {
  $image = image_load($variables['uri']);
  $content = array(
    'file' => array(
      '#theme' => 'image_style',
      '#style_name' => 'original',
      '#path' => $image->source,
      '#width' => $image->info['width'],
      '#height' => $image->info['height'],
      '#alt' => $variables['field_file_image_alt_text']['en'][0]['value'],
      '#title' => $variables['field_file_image_title_text']['en'][0]['value'],
    ),
  );
  $variables['image'] = $content;
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
