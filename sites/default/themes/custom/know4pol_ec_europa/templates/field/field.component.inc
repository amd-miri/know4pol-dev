<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_field().
 */
function know4pol_ec_europa_preprocess_field(array &$variables, $hook) {
  $el = $variables['element'];
  $node = $el['#object'];
  $menu_item = menu_get_item();

  // Check if view_mode is not solr and if Display Suite is handling the field.
  if ($el['#view_mode'] != 'apachesolr_page' && isset($node->type) && module_exists('ds')) {
    $layout = ds_get_layout('node', $node->type, $el['#view_mode']);
    if (isset($layout['settings']['fields'][$el['#field_name']])) {
      $variables['theme_hook_suggestions'][] = 'field__ds_region__' . $layout['settings']['fields'][$el['#field_name']];
      $variables['theme_hook_suggestions'][] = 'field__' . $el['#field_name'] . '__ds_region' .
        $layout['settings']['fields'][$el['#field_name']];
    }
  }
  // Handle apache solR preproces in a different function.
  elseif ($el['#view_mode'] == 'apachesolr_page') {
    // Add template suggestions for field in the apache solr viewmode.
    $variables['theme_hook_suggestions'][] = 'field__' . $el['#view_mode'];
    $variables['theme_hook_suggestions'][] = 'field__' .
      $el['#field_name'] . '__' . $el['#view_mode'];
    // Heading of search result.
    // Beter way would to theme fields in the DS region but seems not possible.
    switch ($el['#field_name']) {
      case 'node_type_name':
      case 'field_pub_dc_date_created':
      case 'changed_date':
      case 'field_newsroom_item_type':
      case 'field_newsroom_item_date':
      case 'changed_date':
      case 'created':
        $variables['theme_hook_suggestions'][] = 'field__' . $el['#view_mode'] .
          '__meta_headers';
        break;
    }

    // Determine which apache solR page is viewed.
    switch ($menu_item['map'][0]) {
      case 'events':
        $variables['hide_metas'] = TRUE;
        // Newsroom date, field newsroom_item_type exists, and it's an event.
        if ($el['#field_name'] == "field_newsroom_item_date" &&
          $el['#object']->field_newsroom_item_type[LANGUAGE_NONE][0]['taxonomy_term']->name == "Event") {
          // Determine which apache solR page is viewed.
          $variables['theme_hook_suggestions'][] = 'field__' . $el['#view_mode'] .
              '__event_date';
          $variables['ecl_date'] = _know4pol_ec_europa_get_date_for_ecl($el['#items'][0]);
        }
    }
  }

  // Custom hook for specific fields.
  switch ($el['#field_name']) {
    case 'ks_name_topic_specific_taxonomies':
      $variables['label'] = t('Knowledge service | Topics | Specific keywords');
      break;

    case 'field_vis_data_url':
      _know4pol_ec_europa_preprocess_field__field_vis_data_url__visualisation($variables);
      break;

    case 'field_vis_qlik_elements':
      _know4pol_ec_europa_preprocess_field__field_vis_qlik_elements__visualisation($variables);
      break;

    case 'title':
      // Check if nid of menu_item is not identical of the redered
      // title to determine embedding and avoid double H1 in embed nodes.
      if ($el['#view_mode'] == 'full' && $node &&
        $el['#object']->nid != $menu_item['map'][1]->nid) {
        // Disable DS formatting and use template instead.
        $variables['theme_hook_suggestions'][] = 'field__title_embed';
        $variables['element']['#items'][0][value] = $el['#object']->title;
      }

      // Navigation block alternate title on blocks.
      if ($el['#view_mode'] == 'navigation') {
        if (isset($node->field_nav_navigation_title[LANGUAGE_NONE][0]['value'])) {
          $alt_title = trim($node->field_nav_navigation_title[LANGUAGE_NONE][0]['value']);
          // Do not display the original title if the alt is filled in.
          if (drupal_strlen($alt_title)) {
            unset($variables['items']);
          }
        }
      }
  }
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
 * Preprocess field data visualisation urls.
 *
 * @param array $variables
 *   Variables from the original hook.
 */
function _know4pol_ec_europa_preprocess_field__field_vis_qlik_elements__visualisation(array &$variables) {
  // Build data paramters if relevant type.
  if ($variables['element']['#object']->field_vis_type[LANGUAGE_NONE][0]['value'] == "Qlik") {

    drupal_add_css('//qap-datam.jrc.ec.europa.eu/qap/content/Default/qlik-styles.css', 'external');
    drupal_add_js('//qap-datam.jrc.ec.europa.eu/qap/resources/assets/external/requirejs/require.js', 'external');

    $variables['atomium']['attributes']['wrapper']->append('class', 'qlik-wrapper');

    // Get the layout from the text field ready for rendering.
    $variables['html_layout'] = render(field_view_value(
        'node',
        $variables['element']['#object'],
        'field_vis_qlik_page_layout',
        $variables['element']['#object']->field_vis_qlik_page_layout[LANGUAGE_NONE][0]
      ));

    // Prepare values of the field collection in this field.
    foreach ($variables['items'] as &$item) {
      $fcid = array_keys($item['entity']['field_collection_item'])[0];
      $fcit = &$item['entity']['field_collection_item'][$fcid];

      $item['html_id'] = $fcit['field_vis_qlik_html_id']['#items'][0]['value'];
      $item['id'] = $fcit['field_vis_qlik_id']['#items'][0]['value'];

      if (isset($fcit['field_vis_qlik_options']['#items'][0]['value'])) {
        switch ($fcit['field_vis_qlik_options']['#items'][0]['value']) {
          case "no_interaction":
            $item['option'] = '{noInteraction: true}';
            break;

          case "no_selection":
            $item['option'] = '{noSelections: true}';
            break;
        }
      }
    }
  }
}
