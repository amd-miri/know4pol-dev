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

  // Specific for policy layer landing pages.
  if ($el['#view_mode'] == 'featured' && $el['#bundle'] == 'topic') {
    switch ($el['#field_name']) {
      case 'field_av_image':
        $variables['theme_hook_suggestions'][] = 'field__title_h2_pagenav';
        $variables['label'] = t('Brief me');
        $variables['html_id'] = 'brief';
        break;
    }
  }
  if ($el['#view_mode'] == 'featured' && $el['#bundle'] == 'knowledge_centre') {
    switch ($el['#field_name']) {
      case 'body':
        $variables['theme_hook_suggestions'][] = 'field__title_h2_pagenav';
        $variables['label'] = t('Brief me');
        $variables['html_id'] = 'brief';
        break;

      case 'field_av_image':
        $variables['theme_hook_suggestions'][] = 'field__title_h2_pagenav';
        $variables['label'] = t('What we do');
        $variables['html_id'] = 'what';
        break;

      case 'field_av_summary':
        $ks_path = $variables['element']['#object']->path['alias'];
        $aboutpage = $ks_path . '/about';
        // Add the KS "About" link to content.
        if (drupal_lookup_path('source', $aboutpage) != FALSE) {
          $variables['items'][0]['#markup'] .= '<p>' . l(t('About this knowledge service'), $aboutpage) . '</p>';
        }

    }
  }
  if ($el['#field_name'] == 'field_av_image') {
    $variables['atomium']['attributes']['wrapper']->remove('class', 'field-type-image');
  }

  // Custom hook for specific fields.
  switch ($el['#field_name']) {
    case 'ks_name_topic_specific_taxonomies':
      $variables['label'] = t('Knowledge service | Metadata');
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
      break;
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
  $object = $variables['element']['#object'];
  $el['v_type'] = $object->field_vis_type[LANGUAGE_NONE][0]['value'];
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
      $variables['provider'] = (isset($object->field_vis_highcharts_gantt) && $object->field_vis_highcharts_gantt[LANGUAGE_NONE][0]['value'] == TRUE) ? 'highchartsgantt' : 'highcharts';
      if (isset($object->field_vis_render_to) && drupal_strlen($object->field_vis_render_to[LANGUAGE_NONE][0]['value'])) {
        $variables['render_to'] = $object->field_vis_render_to[LANGUAGE_NONE][0]['value'];
      }
      break;

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

    drupal_add_css('//qlik-sense.jrc.ec.europa.eu/qap/content/Default/qlik-styles.css', 'external');
    drupal_add_js('//qlik-sense.jrc.ec.europa.eu/qap/resources/assets/external/requirejs/require.js', 'external');
    drupal_add_js(drupal_get_path('theme', 'know4pol_ec_europa') . '/assets/scripts/qap-k4p-config.js', array('type' => 'file', 'scope' => 'footer'));

    $variables['atomium']['attributes']['wrapper']->append('class', 'qlik-wrapper');

    // Get the layout from the text field ready for rendering.
    $variables['html_layout'] = render(field_view_value(
        'node',
        $variables['element']['#object'],
        'field_vis_qlik_page_layout',
        $variables['element']['#object']->field_vis_qlik_page_layout[LANGUAGE_NONE][0]
      ));

    $js_items = array();
    // Prepare values of the field collection in this field.
    foreach ($variables['items'] as $item) {
      $fcid = array_keys($item['entity']['field_collection_item'])[0];
      $fcit = $item['entity']['field_collection_item'][$fcid];
      $js_item = array(
        'html_id' => $fcit['field_vis_qlik_html_id']['#items'][0]['value'],
        'id' => $fcit['field_vis_qlik_id']['#items'][0]['value'],
      );

      if (isset($fcit['field_vis_qlik_options']['#items'][0]['value'])) {
        switch ($fcit['field_vis_qlik_options']['#items'][0]['value']) {
          case "no_interaction":
            $js_item['option'] = (object) ['noInteraction' => TRUE];
            break;

          case "no_selection":
            $js_item['option'] = (object) ['noSelections' => TRUE];
            break;
        }
      }

      $js_items[] = $js_item;
    }

    drupal_add_js(array('know4pol' => array('items' => $js_items)), array('type' => 'setting'));
    drupal_add_js(array('know4pol' => array('qapid' => $variables['element']['#object']->field_vis_qlik_app_id[LANGUAGE_NONE][0]['value'])), array('type' => 'setting'));
  }
}
