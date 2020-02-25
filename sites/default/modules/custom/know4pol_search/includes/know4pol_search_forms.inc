<?php

/**
 * @file
 * Form related hooks for know4pol-search module.
 */

/**
 * Implements hook_form().
 */
function know4pol_search_form($form, $form_state) {
  $map = menu_get_item()['original_map'];
  $setting_id = ($map[0] == 'home') ? 0 : $map[1];

  $form['knowledge_centre_nid'] = array(
    '#type' => 'hidden',
    '#value' => $setting_id,
  );
  // Text field.
  $form['keyword'] = array(
    '#type' => 'textfield',
    '#default_value' => '',
    '#prefix' => '<label id="know4pol-form-label" class="ecl-search-form__textfield-wrapper">',
    '#suffix' => '</label>',
    '#attributes' => array('class' => array('ecl-text-input', 'ecl-search-form__textfield')),
  );
  // Submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
    '#attributes' => array(
      'class' => array('ecl-button',
        'ecl-button--form-primary',
        'ecl-button--primary',
        'ecl-search-form__button',
      ),
    ),
  );
  // Search content type options.
  $form['type'] = array(
    '#type' => 'radios',
    '#weight' => '100',
    '#options' => _know4pol_search_get_allowed_content_types($setting_id),
    '#default_value' => _know4pol_search_get_default_content_type(),
    '#attributes' => array('class' => array('ecl-radio-group', 'container-inline')),
  );

  $form['#attributes'] = array(
    'class' => array('ecl-form', 'ecl-search-form--internal'),
    'id' => 'know4pol-search-form',
  );
  return $form;
}

/**
 * Implements hook_form_submit().
 */
function know4pol_search_form_submit(&$form, &$form_state) {
  global $base_url;
  $query = array();
  $i = 0;

  // KS selected ?
  if ($knowledge_centre_nid = $form_state['values']['knowledge_centre_nid']) {
    $query['f[' . ++$i . ']'] = 'sm_og_group_ref:node:' . $knowledge_centre_nid;
  }

  // Get specific SolR page or default page.
  $solr_pages = array_change_key_case(array_flip(_know4pol_search_get_solr_search_pages()));
  $search_for = $form_state['values']['type'];
  if (array_key_exists($search_for, $solr_pages)) {
    $search_url = $solr_pages[$search_for];
  }
  else {
    $search_url = $solr_pages['all'];
    $query['f[' . ++$i . ']'] = 'bundle:' . $search_for;
  }

  // Clean non word characters.
  $keywords = _know4pol_search_clean_keywords($form_state['values']['keyword']);
  $search_url .= '/' . $keywords;

  // Build search url and redirect.
  $form_state['redirect'] = $base_url . '/' . $search_url . '?' . drupal_http_build_query($query);
}

/**
 * Implements hook_form().
 */
function know4pol_mainsearch_form($form, $form_state) {
  // Text field.
  $form['keyword'] = array(
    '#type' => 'textfield',
    '#default_value' => '',
    '#prefix' => '<label id="know4pol-form-label" class="ecl-search-form__textfield-wrapper">',
    '#suffix' => '</label>',
    '#attributes' => array('class' => array('ecl-text-input', 'ecl-search-form__textfield')),
  );
  // Submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
    '#attributes' => array(
      'class' => array('ecl-button',
        'ecl-button--form-primary',
        'ecl-button--primary',
        'ecl-search-form__button',
      ),
    ),
  );
  // Search solr page type options.
  $form['solr_search_page'] = array(
    '#type' => 'radios',
    '#weight' => '100',
    '#options' => _know4pol_search_get_allowed_search_pages(),
    '#default_value' => 'search/site',
    '#attributes' => array('class' => array('ecl-radio-group', 'container-inline')),
  );
  $form['#attributes'] = array(
    'class' => array('ecl-form', 'ecl-search-form--internal'),
    'id' => 'know4pol-search-form',
  );
  return $form;
}

/**
 * Implements hook_form_submit().
 */
function know4pol_mainsearch_form_submit(&$form, &$form_state) {
  global $base_url;
  $keyword = _know4pol_search_clean_keywords($form_state['values']['keyword']);
  $solr_search_page = $form_state['values']['solr_search_page'];
  // Building search url, containing list of numbered solr search parameters.
  $output = $base_url . '/' . $solr_search_page . '/' . $keyword;
  $form_state['redirect'] = $output;
}

/**
 * The free text search form for ApacheSolr pages.
 *
 * @param object $keys
 *   The search words/keys.
 */
function _know4pol_search_freetext_search_form($form, &$form_state, $keys = '') {
  $form = array();
  $form['#id'] = 'freetext-search-form';
  $form['#attributes']['class'][] = 'ecl-search-form';
  $form['#attributes']['class'][] = 'ecl-search-form--internal';
  $form['#attributes']['class'][] = 'ecl-u-mb-l';

  $form['keys'] = array(
    '#type' => 'textfield',
    '#default_value' => $keys,
    '#size' => 20,
    '#maxlength' => 255,
    '#attributes' => array(
      'class' => array('ecl-text-input',
        'ecl-search-form__textfield',
      ),
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#attributes' => array(
      'class' => array('ecl-button',
        'ecl-button--form-primary',
        'ecl-search-form__button',
      ),
    ),
  );

  return $form;
}

/**
 * The submit function for the free text search form for ApacheSolr pages.
 */
function _know4pol_search_freetext_search_form_submit(&$form, &$form_state) {
  // Should get the URL from the defined search pages.
  $arg = menu_get_item()['map'];
  if ($arg[0] == 'search' && $arg[1] == 'site') {
    $redirect = 'search/site';
  }
  else {
    $redirect = $arg[0];
  }
  $redirect_value = rawurlencode($form_state['values']['keys']);
  if (drupal_strlen($form_state['values']['keys'])) {
    $redirect .= '/' . $redirect_value;
  }

  $get = drupal_get_query_parameters();
  if (!empty($get)) {
    unset($get['q']);
    // Reset to first page.
    unset($get['page']);
  }
  $form_state['redirect'] = array($redirect, array('query' => $get));
}

/**
 * Get allowed search pages on homepage.
 *
 * @return array
 *   Returns search pages.
 */
function _know4pol_search_get_allowed_search_pages() {
  $know4pol_search_settings_array = variable_get('know4pol_search_settings');
  $allowed_options = $know4pol_search_settings_array[0];
  // Get human names.
  $types = _know4pol_search_get_solr_search_pages();
  foreach ($allowed_options as $allowed_option) {
    $allowed_options[$allowed_option] = $types[$allowed_option];
  }
  $allowed_options['search/site'] = 'All';
  // Move default option as first option.
  $allowed_options_sorted = array('search/site' => $allowed_options['search/site']) + $allowed_options;
  return $allowed_options_sorted;
}

/**
 * Clean non word characters for keywords.
 *
 * @return string
 *   The cleaned text.
 */
function _know4pol_search_clean_keywords($input) {
  return preg_replace('/[^\w\s\-\']/', '', $input);
}

/**
 * Get search query from url and use as default_value in form.
 *
 * @return string
 *   Returns content type or keyword.
 */
function _know4pol_search_get_default_content_type() {
  $parameters = drupal_get_query_parameters();
  if (empty($parameters)) {
    return 'all';
  }
  foreach ($parameters['f'] as $bundle_parameter) {
    if (strpos($bundle_parameter, 'bundle:') !== FALSE) {
      $bundle_machine_name = str_replace('bundle:', '', $bundle_parameter);
      return $bundle_machine_name;
    }
  }
}
