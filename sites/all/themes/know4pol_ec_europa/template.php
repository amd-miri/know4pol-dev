<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements hook_menu_link().
 */
function know4pol_ec_europa_menu_link(array $variables) {
  // Add a class to menu links that link to unpublished nodes.
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $sub_menu = str_replace('<ul class="', '<ul class="dropdown-menu ', $sub_menu);
  }
  if (preg_match('@^node/(\d+)$@', $element['#href'], $matches)) {
    $node = node_load((int) $matches[1]);
    if ($node && $node->status == NODE_NOT_PUBLISHED) {
      // There appear to be some inconsistency.
      // Sometimes the classes come through
      // As an array and sometimes as a string.
      if (empty($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = array();
      }
      elseif (is_string($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = explode(' ', $element['#localized_options']['attributes']['class']);
      }
      $element['#localized_options']['attributes']['class'][] = 'menu-node-unpublished';
    }
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  $output = html_entity_decode($output);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_block__content(&$variables, $hook) {
  // Add template suggestion for search pages.
  if ($variables['elements']['#block']->bid == 'block-5') {
    $variables['theme_hook_suggestions'][] = 'block__search_top';
    _know4pol_ec_europa_preprocess_block__block__search_results($variables, $hook);
  }
  // Remove unnecessary ".ecl-editor" class.
  $variables['atomium']['attributes']['content']['class'] = array();
}

/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_block__sidebar_first(&$variables, $hook) {
  // Add template suggestion for search pages.
  if ($variables['elements']['#block']->bid == 'block-4') {
    $variables['theme_hook_suggestions'][] = 'block__search_options';
    _know4pol_ec_europa_preprocess_block__solr_related($variables, $hook);
  }
}

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node(&$variables, $hook) {
  // For all content types.
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', 'external');
  // Per node type.
  switch ($variables['type']) {
    case 'file':
      _know4pol_ec_europa_preprocess_node_file($variables);
      break;
  }
}

/**
 * Implements template_preprocess_page().
 */
function know4pol_ec_europa_preprocess_page(&$variables, $hook) {
  // If this is a search page, add wrapper to results.
  if (isset($variables['page']['content']['system_main']['search_results'])) {
    $variables['page']['content']['system_main']['search_results']['search_results']['#prefix'] = '<ul class="ecl-list ecl-list--unstyled ecl-u-mv-m">';
    $variables['page']['content']['system_main']['search_results']['search_results']['#suffix'] = '</ul>';
  }
}

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
    switch ($variables['element']['#field_name']) {
      case 'node_type_name':
      case 'field_pub_dc_date_created':
      case 'changed_date':
        $variables['theme_hook_suggestions'][] = 'field__' . $variables['element']['#view_mode'] .
          '__meta_headers';
        break;
    }
  }

  // Custom hook for specific fields.
  if ($variables['element']['#field_name'] == 'field_vis_data_url') {
    _know4pol_ec_europa_preprocess_field__field_vis_data_url__visualisation($variables);
  }
}

/**
 * Preprocess node_file.
 *
 * Analyse legacy link content
 * and possible more info to display into the ECL block.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_node_file(array &$variables) {
  $node = $variables['elements']['#node'];

  // Is file a link or a file ?
  $node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
    $node->field_is_legacy_link,
    $node->field_legacy_link,
    $node->field_file_file
  );
  // Filetype icon.
  $_icon_css = $node->field_file_type[LANGUAGE_NONE][0]['taxonomy_term']->field_file_type_classname[LANGUAGE_NONE];
  // Default icon if no type.
  $node->file_type_css = "." . count($_icon_css) ? $_icon_css[0]['value'] : 'ecl-icon--file';

  // Languages versions.
  $translations = translation_node_get_translations($node->nid);
  foreach ($translations as $t) {
    // Other languages olny.
    if ($t->nid != $node->nid) {
      $t_node = node_load($t->nid);
      $t_node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
        $t_node->field_is_legacy_link,
        $t_node->field_legacy_link,
        $t_node->field_file_file
      );
      $node->translations->data[] = $t_node;
    }
  }
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
        $el['thost'] = urlencode($matches[1] . '/');
        $el['troot'] = htmlentities($matches[2]);
        $el['tname'] = htmlentities($matches[3]);
      }
      break;

    case "Highcharts":
      // No preprocess.
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
 * Implements template_preprocess_form_element().
 */
function know4pol_ec_europa_preprocess_form_element(&$variables) {
  // Add theme suggestions so facets can be distinguished.
  if (isset($variables['element']['#name'])) {
    $variables['theme_hook_suggestions'][] = 'form_item__' . $variables['element']['#name'];
    $variables['theme_hook_suggestions'][] = 'form_item__' . $variables['element']['#id'] .
      '__' . $variables['element']['#name'];
  }
}

/**
 * Get current SolR adapter API.
 *
 * @return object
 *   FacetapiAdapter object, null if not possible.
 */
function _know4pol_ec_europa_get_solr_instance() {
  // Checks there is a SolR instance and a search.
  $searcher = array_values(facetapi_get_active_searchers())[0];
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
 * Preprocess current search options.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_block__solr_related(array &$variables, $hook) {
  // Current search ?
  if (!$adapter = _know4pol_ec_europa_get_solr_instance()) {
    return;
  }
  // Set variables from SolR.
  $variables['solr'] = array();
  $variables['solr']['result_count'] = $adapter->getResultCount();
}

/**
 * Preprocess current search SolR block.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_block__block__search_results(array &$variables, $hook) {
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
  $facets = array();

  // Build collection.
  foreach ($facets_used as $key => $item) {
    $fname = $item['facets'][0];
    if (!isset($facets[$fname])) {
      $index = array('values' => array());
      // Get facet name.
      $index['facet'] = facetapi_facet_load($fname, $searcher);
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
