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
  $menu_item = menu_get_item();

  // Node is viewed.
  if ($menu_item['path'] == 'node/%') {
    $node = $menu_item['page_arguments'][0];
    switch ($node->type) {
      case 'knowledge_centre':
        $variables['full_banner'] = TRUE;
        if (!empty($node->field_short_description[LANGUAGE_NONE][0]['value'])) {
          $variables['introduction'] = $node->field_short_description[LANGUAGE_NONE][0]['value'];
        }
        $variables['title'] = $node->field_ks_fullname[LANGUAGE_NONE][0]['value'];
        break;

      case 'navigation_page':
        $variables['full_banner'] = TRUE;
        if (!empty($node->field_nav_description[LANGUAGE_NONE][0]['value'])) {
          $variables['introduction'] = $node->field_nav_description[LANGUAGE_NONE][0]['value'];
        }
        break;

      // Common for those types.
      case 'newsroom_item':
      case 'dataset':
      case 'publication':
        $variables['full_banner'] = TRUE;
        $variables['meta'] = array(
          '#theme' => 'meta',
          '#type' => $node->type,
          '#timestamp' => format_date($node->created, 'custom', 'Y-m-d\TH:i:sP'),
          '#date' => format_date($node->created, 'meta'),
        );

        break;
    }
    // Specific for those types.
    switch ($node->type) {
      case 'newsroom_item':
        if (!empty($node->field_newsroom_teaser[$node->language][0]['value'])) {
          $variables['introduction'] = filter_xss($node->field_newsroom_teaser[$node->language][0]['value']);
        }
        if (isset($node->field_newsroom_item_type[LANGUAGE_NONE][0]['tid'])) {
          $variables['meta']['#type'] = taxonomy_term_load($node->field_newsroom_item_type[LANGUAGE_NONE][0]['tid'])->name;
          if ($variables['meta']['#type'] == "Event") {
            // Events subtybe has different dates and a location.
            $variables['meta']['#date'] = _know4pol_ec_europa_format_dates_start_end($node->field_newsroom_item_date[LANGUAGE_NONE][0]);
            if (isset($node->field_newsroom_item_venue[LANGUAGE_NONE][0]['safe_value'])) {
              // If a venue is set (should be town + country).
              $variables['meta']['#location'] = $node->field_newsroom_item_venue[LANGUAGE_NONE][0]['safe_value'];
            }

          }
        }
        break;

      case 'publication':
        if (isset($node->field_pub_type[LANGUAGE_NONE][0]['tid'])) {
          $variables['meta']['#type'] = taxonomy_term_load($node->field_pub_type[LANGUAGE_NONE][0]['tid'])->name;
        }
        if (!empty($node->field_pub_dc_descrip_abstract[LANGUAGE_NONE][0]['value'])) {
          $variables['introduction'] = $node->field_pub_dc_descrip_abstract[LANGUAGE_NONE][0]['value'];
        }
    }
  }
  elseif (drupal_is_front_page()) {
    $variables['full_banner'] = TRUE;
    $variables['introduction'] = variable_get('site_slogan', '');
  }
  // Or it's a SolR page.
  elseif ($adapter = _know4pol_ec_europa_get_solr_instance()) {
    // Full header.
    $variables['full_banner'] = TRUE;
    // And custom title.
    $id_suffix = $variables['identity'];
    // If in a KS search, append name of KS to title.
    $searcher = $adapter->getSearcher();
    if ($facet = facetapi_facet_load('sm_og_group_ref', $searcher)) {
      if ($value = $adapter->getActiveItems($facet)) {
        $value = $adapter->getMappedValue('sm_og_group_ref', key($value));
        $id_suffix = $value['#markup'];
      }
    }
    $variables['title'] = t('Search') . ' ' . $id_suffix;
    $variables['introduction'] = t('Refine your search result using the form, left.');
  }
}

/**
 * Format date with begin and end value for better display.
 *
 * @param array $date
 *   The date field to format.
 *
 * @return string
 *   The formatted date with meta formater.
 */
function _know4pol_ec_europa_format_dates_start_end(array $date) {
  // No end date or not different.
  if (!isset($date['value2']) || $date['value'] == $date['value2']) {
    return format_date($date['value'], 'meta');
  }

  // Extract date parts.
  preg_match('/^([0-9]{2})\/([0-9]{2})\/([0-9]{4})$/', date('d/m/Y', $date['value']), $d1);
  preg_match('/^([0-9]{2})\/([0-9]{2})\/([0-9]{4})$/', date('d/m/Y', $date['value2']), $d2);

  // Check possible cases of same year and month
  // (we know it's not the same day since first return).
  if ($d1[3] == $d2[3]) {
    if ($d1[2] == $d2[2]) {
      return $d1[1] . ' &ndash; ' . format_date($date['value2'], 'meta');
    }
    return format_date($date['value'], 'custom', 'd F') . ' &ndash; ' . format_date($date['value2'], 'meta');
  }
  return format_date($date['value'], 'meta') . ' &ndash; ' . format_date($date['value2'], 'meta');
}
