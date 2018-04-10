<?php

/**
 * @file
 * Administration form for suggestion module.
 */

/**
 * Menu callback to index suggestions.
 */
function suggestion_admin_edit_form($form, &$state, $ngram) {
  $obj = SuggestionStorage::getSuggestion($ngram);

  $form['#submit'][] = 'suggestion_admin_edit_form_submit';
  $form['#validate'][] = 'suggestion_admin_edit_form_validate';

  $form['ngram'] = array(
    '#type'  => 'value',
    '#value' => $obj->ngram,
  );
  $form['atoms'] = array(
    '#type'  => 'value',
    '#value' => $obj->atoms,
  );
  $form['density'] = array(
    '#type'  => 'value',
    '#value' => $obj->density,
  );
  $form['ngram_txt'] = array(
    '#markup' => t('Suggestion: @ngram', array('@ngram' => $obj->ngram)),
    '#suffix' => '<br />',
    '#weight' => 10,
  );
  $form['atoms_txt'] = array(
    '#markup' => t('Words: @atoms', array('@atoms' => $obj->atoms)),
    '#suffix' => '<br />',
    '#weight' => 20,
  );
  $form['density_txt'] = array(
    '#markup' => t('Score: @density', array('@density' => $obj->density)),
    '#weight' => 30,
  );
  $form['qty'] = array(
    '#title'         => t('Quantity'),
    '#type'          => 'textfield',
    '#default_value' => $obj->qty,
    '#required'      => TRUE,
    '#weight'        => 40,
  );
  $form['src'] = array(
    '#title'         => t('Source'),
    '#type'          => 'select',
    '#options'       => SuggestionStorage::getSrcOptions(),
    '#default_value' => SuggestionHelper::srcBits($obj->src),
    '#multiple'      => TRUE,
    '#required'      => TRUE,
    '#weight'        => 50,
  );
  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Submit'),
    '#weight' => 100,
  );
  return $form;
}

/**
 * Custom submit function for the suggestion setting form.
 */
function suggestion_admin_edit_form_submit($form, &$state) {
  $src = 0;

  foreach ((array) $state['values']['src'] as $bit) {
    $src |= intval($bit);
  }
  $key = array('ngram' => $state['values']['ngram']);
  $fields = array(
    'atoms'   => $state['values']['atoms'],
    'density' => SuggestionHelper::calculateDensity($src, $state['values']['atoms'], $state['values']['qty']),
    'qty'     => $state['values']['qty'],
    'src'     => $src,
  );
  SuggestionStorage::mergeSuggestion($key, $fields);
}

/**
 * Custom submit function for the suggestion setting form.
 */
function suggestion_admin_edit_form_validate($form, &$state) {
  if (!is_numeric(trim($state['values']['qty']))) {
    form_set_error('qty', t('The quantity must have a numeric value'));
  }
  if (!count((array) $state['values']['src'])) {
    form_set_error('src', t('The source must have a value.'));
  }
  elseif (isset($state['values']['src'][0]) && count((array) $state['values']['src']) > 1) {
    form_set_error('src', t('The disabled option cannot be combined with other options.'));
  }
}

/**
 * Menu callback to index suggestions.
 */
function suggestion_admin_index_form($form) {
  $form['feedback'] = array(
    '#markup' => '<div id="suggestion-index-feedback">' . (variable_get('suggestion_synced', TRUE) ? t('No indexing required.') : t('Indexing required.')) . '</div>',
    '#weight' => 10,
  );
  $form['flush'] = array(
    '#title'         => t('Flush all suggestions'),
    '#description'   => t('Flushes all suggestions including priority and surfer suggestions.'),
    '#type'          => 'checkbox',
    '#default_value' => FALSE,
    '#required'      => FALSE,
    '#weight'        => 20,
  );
  $form['submit'] = array(
    '#type'   => 'submit',
    '#value'  => t('Index Suggestions'),
    '#weight' => 30,
    '#ajax'   => array(
      'callback' => 'suggestion_index_block_ajax_callback',
      'effect'   => 'fade',
      'method'   => 'replace',
      'wrapper'  => 'suggestion-index-feedback',
    ),
  );
  return $form;
}

/**
 * Menu callback to index suggestions.
 */
function suggestion_admin_search_form($form, &$state, $ngram = '') {
  $ngram = trim($ngram);
  $opts = array('query' => drupal_get_destination());
  $rows = array();
  $rpp = variable_get('suggestion_rpp', 100);
  $header = array(
    t('N-Gram'),
    t('Source'),
    t('Atoms'),
    t('Quantity'),
    t('Density'),
    t('Edit'),
  );
  if ($ngram) {
    $pattern = '%' . db_like($ngram) . '%';
    $page = pager_default_initialize(SuggestionStorage::getCount($pattern), $rpp);
    $suggestions = SuggestionStorage::search($pattern, ($page * $rpp), $rpp);
  }
  else {
    $page = pager_default_initialize(SuggestionStorage::getCount(), $rpp);
    $suggestions = SuggestionStorage::getAllSuggestions(($page * $rpp), $rpp);
  }
  foreach ($suggestions as $obj) {
    $rows[$obj->ngram] = array(
      $obj->ngram,
      $obj->src,
      $obj->atoms,
      $obj->qty,
      $obj->density,
      l(t('Edit'), "admin/config/suggestion/edit/$obj->ngram", $opts),
    );
  }
  $form['ngram'] = array(
    '#type'              => 'textfield',
    '#autocomplete_path' => 'suggestion/autocomplete',
    '#default_value'     => $ngram,
    '#weight'            => 10,
  );
  $form['search'] = array(
    '#type'     => 'submit',
    '#name'     => 'search',
    '#value'    => t('Search'),
    '#submit'   => array('suggestion_admin_search_form_submit'),
    '#validate' => array(),
    '#weight'   => 20,
  );
  $form['list'] = array(
    '#type'    => 'tableselect',
    '#header'  => $header,
    '#options' => $rows,
    '#empty'   => t('Nothing found.'),
    '#weight'  => 60,
  );
  if (count($rows)) {
    $form['src'] = array(
      '#title'    => t('Source'),
      '#type'     => 'select',
      '#options'  => SuggestionStorage::getSrcOptions(),
      '#multiple' => TRUE,
      '#weight'   => 30,
    );
    $form['update'] = array(
      '#type'     => 'submit',
      '#name'     => 'update',
      '#value'    => t('Update'),
      '#submit'   => array(
        'suggestion_admin_search_form_update_submit',
        'suggestion_admin_search_form_submit',
      ),
      '#validate' => array('suggestion_admin_search_form_validate'),
      '#weight'   => 40,
    );
    $form['pager'] = array(
      '#theme'  => 'pager',
      '#weight' => 70,
    );
  }
  return $form;
}

/**
 * Ngram search submission function.
 */
function suggestion_admin_search_form_submit($form, &$state) {
  drupal_goto("admin/config/suggestion/search/{$state['values']['ngram']}");
}

/**
 * Ngram update submission function.
 */
function suggestion_admin_search_form_update_submit($form, &$state) {
  $src = SuggestionHelper::optionBits((array) $state['values']['src']);

  foreach ((array) $state['values']['list'] as $ngram => $val) {
    if (!$val) {
      continue;
    }
    SuggestionHelper::updateSrc($ngram, $src);

    drupal_set_message(t('Updated: &ldquo;@ngram&rdquo;', array('@ngram' => $ngram)));
  }
}

/**
 * Validation function for the suggestion search form.
 */
function suggestion_admin_search_form_validate($form, &$state) {
  $suxs = FALSE;

  if (!count((array) $state['values']['src'])) {
    form_set_error('src', t('The source must have a value.'));
  }
  elseif (isset($state['values']['src'][0]) && count((array) $state['values']['src']) > 1) {
    form_set_error('src', t('The disabled option cannot be combined with other options.'));
  }
  foreach ((array) $state['values']['list'] as $val) {
    if ($val) {
      $suxs = TRUE;
      break;
    }
  }
  if (!$suxs) {
    form_set_error('list', t('You must select an ngram to perform the update to.'));
  }
}

/**
 * Menu callback to configure suggestion settings.
 */
function suggestion_admin_settings_form($form) {
  _suggestion_admin_stopword_init();

  $form['#submit'][] = 'suggestion_admin_settings_form_submit';

  $form['suggestion_form_id'] = array(
    '#title'         => t('Form ID'),
    '#type'          => 'textfield',
    '#default_value' => variable_get('suggestion_form_id', ''),
    '#required'      => TRUE,
    '#weight'        => 10,
  );
  $form['suggestion_field_name'] = array(
    '#title'         => t('Field Name'),
    '#type'          => 'textfield',
    '#default_value' => variable_get('suggestion_field_name', ''),
    '#required'      => TRUE,
    '#weight'        => 20,
  );
  $form['suggestion_min'] = array(
    '#title'         => t('Minimum Characters'),
    '#type'          => 'select',
    '#options'       => array_combine(range(3, 10), range(3, 10)),
    '#default_value' => variable_get('suggestion_min', 4),
    '#required'      => TRUE,
    '#weight'        => 30,
  );
  $form['suggestion_max'] = array(
    '#title'         => t('Maximum Characters in a Suggestion'),
    '#type'          => 'select',
    '#options'       => array_combine(range(20, 60), range(20, 60)),
    '#default_value' => variable_get('suggestion_max', 45),
    '#required'      => TRUE,
    '#weight'        => 40,
  );
  $form['suggestion_atoms'] = array(
    '#title'         => t('Maximum Words in a Suggestion'),
    '#type'          => 'select',
    '#options'       => array_combine(range(1, 10), range(1, 10)),
    '#default_value' => variable_get('suggestion_atoms', 6),
    '#required'      => TRUE,
    '#weight'        => 50,
  );
  $form['suggestion_limit'] = array(
    '#title'         => t('Maximum Suggestions Returned'),
    '#type'          => 'select',
    '#options'       => array_combine(range(10, 100), range(10, 100)),
    '#default_value' => variable_get('suggestion_limit', 20),
    '#required'      => TRUE,
    '#weight'        => 60,
  );
  $form['suggestion_types'] = array(
    '#title'         => t('Content Types'),
    '#type'          => 'checkboxes',
    '#options'       => SuggestionStorage::getContentTypes(),
    '#default_value' => variable_get('suggestion_types', array()),
    '#required'      => TRUE,
    '#weight'        => 70,
  );
  $form['suggestion_keywords'] = array(
    '#title'         => t('Priority Suggestions'),
    '#description'   => t('Suggestions entered here take priority.'),
    '#type'          => 'textarea',
    '#default_value' => implode("\n", SuggestionStorage::getKeywords()),
    '#rows'          => 10,
    '#required'      => FALSE,
    '#weight'        => 80,
  );
  $form['suggestion_stopwords'] = array(
    '#title'         => t('Stopwords'),
    '#description'   => t('Stopwords are not indexed.'),
    '#type'          => 'textarea',
    '#default_value' => implode("\n", array_keys(SuggestionHelper::getStops())),
    '#rows'          => 10,
    '#required'      => FALSE,
    '#weight'        => 90,
  );
  $form['stopwords'] = array(
    '#title'       => t('Stopword File Location'),
    '#description' => t('Set the location of the stopword file, (advanced users only).'),
    '#type'        => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#weight'      => 100,
  );
  $form['stopwords']['suggestion_stopword_uri'] = array(
    '#title'         => t('Stopword file'),
    '#type'          => 'textfield',
    '#description'   => t('You must use PHP stream wrappers.'),
    '#default_value' => variable_get('suggestion_stopword_uri', file_default_scheme() . '://suggestion/suggestion_stopword.txt'),
    '#required'      => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Custom submit function for the suggestion setting form.
 */
function suggestion_admin_settings_form_submit($form, &$state) {
  if ($state['values']['suggestion_atoms'] != variable_get('suggestion_atoms', 0)) {
    variable_set('suggestion_synced', FALSE);
  }
  elseif ($state['values']['suggestion_limit'] != variable_get('suggestion_limit', 0)) {
    variable_set('suggestion_synced', FALSE);
  }
  elseif ($state['values']['suggestion_max'] != variable_get('suggestion_max', 0)) {
    variable_set('suggestion_synced', FALSE);
  }
  elseif ($state['values']['suggestion_min'] != variable_get('suggestion_min', 0)) {
    variable_set('suggestion_synced', FALSE);
  }
  elseif ($state['values']['suggestion_types'] != variable_get('suggestion_types', NULL)) {
    variable_set('suggestion_synced', FALSE);
  }
  _suggestion_admin_submit_keywords($state);

  _suggestion_admin_submit_stopwords($state);
}

/**
 * Build an array of defalut options from bitmaps.
 *
 * @param int $src
 *   The title to index.
 * @param array $options
 *   An array of the available options.
 *
 * @return array
 *   An array of default option.
 */
function _suggestion_admin_src_bits($src = 0, array $options = array()) {
  $bits = array();

  if (intval($src) <= 0) {
    return array(0);
  }
  foreach (array_keys($options) as $bit) {
    if ($bit & $src) {
      $bits[] = $bit;
    }
  }
  return $bits;
}

/**
 * Implements hook_enable().
 */
function _suggestion_admin_stopword_init() {
  $tgt = variable_get('suggestion_stopword_uri', file_default_scheme() . '://suggestion/suggestion_stopword.txt');

  if (file_exists($tgt)) {
    return;
  }
  $dir = preg_replace('/\/[^\/]+$/', '', $tgt);

  if (!file_exists($dir)) {
    drupal_mkdir($dir);
  }
  module_load_include('inc', 'suggestion', 'suggestion.stopword');
  $stopwords = implode("\n", _suggestion_stopword_list());
  variable_set('suggestion_stopword_hash', drupal_hash_base64($stopwords));
  file_unmanaged_save_data($stopwords, $tgt, FILE_EXISTS_REPLACE);
}

/**
 * Process keywords.
 */
function _suggestion_admin_submit_keywords(&$form_data) {
  foreach (preg_split('/\s*[\n\r]+\s*/s', $form_data['values']['suggestion_keywords']) as $txt) {
    SuggestionHelper::insert($txt, SuggestionStorage::PRIORITY_BIT);
  }
  unset($form_data['input']['suggestion_keywords']);
  unset($form_data['values']['suggestion_keywords']);
}

/**
 * Process stopwords.
 */
function _suggestion_admin_submit_stopwords(&$form_data) {
  $stopwords = array();

  foreach (preg_split('/\s*[\n\r]+\s*/s', $form_data['values']['suggestion_stopwords']) as $txt) {
    $stopwords += array_flip(preg_split('/\s+/', SuggestionHelper::tokenize($txt, variable_get('suggestion_min', 4))));
  }
  $stopwords = array_fill_keys(array_keys($stopwords), 1);

  ksort($stopwords);

  $file_path = drupal_realpath(variable_get('suggestion_stopword_uri', file_default_scheme() . '://suggestion/suggestion_stopword.txt'));

  $stopwords = implode("\n", array_keys($stopwords));

  $hash = drupal_hash_base64($stopwords);

  if ($hash != variable_get('suggestion_stopword_hash', '')) {
    variable_set('suggestion_stopword_hash', $hash);
    variable_set('suggestion_synced', FALSE);
  }
  file_unmanaged_save_data($stopwords, $file_path, FILE_EXISTS_REPLACE);

  unset($form_data['input']['suggestion_stopwords']);
  unset($form_data['values']['suggestion_stopwords']);
}
