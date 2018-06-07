<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements template_preprocess_field().
 */
function know4pol_ec_europa_preprocess_field(&$variables) {
  // Handle apache solR preproces in a different function.
  if ($variables['element']['#view_mode'] == 'apachesolr_page') {
    // Add template suggestions for field in the apache solr viewmode.
    $variables['theme_hook_suggestions'][] = 'field__' . $variables['element']['#view_mode'];
    $variables['theme_hook_suggestions'][] = 'field__' .
      $variables['element']['#field_name'] . '__' .
      $variables['element']['#view_mode'];
    // Heading of search result.
    // Beter way would to theme fields in the DS region but seems not possible.
    switch ($variables['element']['#field_name']) {
      case 'node_type_name':
      case 'field_pub_dc_date_created':
      case 'changed_date':
      case 'field_newsroom_item_type':
      case 'field_newsroom_item_date':
      case 'changed_date':
      case 'created':
        $variables['theme_hook_suggestions'][] = 'field__' . $variables['element']['#view_mode'] .
          '__meta_headers';
        break;
    }

    // Specific to solR page.
    $menu_item = menu_get_item();
    // Determine which apache solR page is viewed.
    switch ($menu_item['map'][0]) {
      case 'events':
        $variables['hide_metas'] = TRUE;
        // Newsroom date, field newsroom_item_type exists, and it's an event.
        if ($variables['element']['#field_name'] == "field_newsroom_item_date" &&
          $variables['element']['#object']->field_newsroom_item_type[LANGUAGE_NONE][0]['taxonomy_term']->name == "Event") {
          // Determine which apache solR page is viewed.
          $variables['theme_hook_suggestions'][] = 'field__' . $variables['element']['#view_mode'] .
              '__event_date';
          $variables['ecl_date'] = _know4pol_ec_europa_get_date_for_ecl($variables['element']['#items'][0]);
          // =.
        }
    }
  }

  // Custom hook for specific fields.
  if ($variables['element']['#field_name'] == 'field_vis_data_url') {
    _know4pol_ec_europa_preprocess_field__field_vis_data_url__visualisation($variables);
  }
}

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
 * Preprocess field data visualisation urls.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_field__field_vis_data_url__visualisation(array &$variables) {
  $el = &$variables['items'][0]['#element'];
  $el['v_type'] = $variables['element']['#object']->field_vis_type[LANGUAGE_NONE][0]['value'];
  // Build data paramters for the visualisation types.
  switch ($el['v_type']) {
    case "Tableau":
      $matches = array();
      if (preg_match('/(.*?ec\.europa\.eu)(\/t\/.*?)\/.*?\/([^\?]+)/', $el['url'], $matches)) {
        // Default object parameters.
        $parameters = array(
          'host_url' => urlencode($matches[1] . '/'),
          'site_root' => htmlentities($matches[2]),
          'name' => htmlentities($matches[3]),
          'embed_code_version' => '3',
          'tabs' => 'no',
          'toolbar' => 'yes',
          'showAppBanner' => 'false',
        );

        $filters = array();
        // May override default param from url.
        foreach (drupal_parse_url($el['url'])['query'] as $key => $value) {
          // Filter or parameter ? Tableau uses ':' for param.
          if ($key[0] == ':') {
            $parameters[drupal_substr($key, 1)] = $value;
          }
          else {
            $filters[] = urlencode($key) . '=' . urlencode($value);
          }
        }
        if (count($filters)) {
          $parameters['filter'] = implode("&", $filters);
        }
        $el['param'] = $parameters;
      }
      break;

    case "Highcharts":
    case "Image":
      // No preprocess yet.
      // Image could copy first image into previsualisation if empty.
      break;
  }
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
