<?php

/**
 * @file
 * Contains the CacheflushUIController class.
 */

/**
 * Custom controller for the administrator UI.
 */
class CacheflushUIController extends EntityDefaultUIController {

  /**
   * Overrides EntityDefaultUIController::hook_menu().
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    $items[$this->path]['title'] = 'CacheFlush';
    $items[$this->path]['access callback'] = 'user_access';
    $items[$this->path]['access arguments'] = array('cacheflush administer');

    $items[$this->path . '/add']['file'] = 'includes/cacheflush_ui.forms.inc';
    $items[$this->path . '/add']['file path'] = drupal_get_path('module', 'cacheflush_ui');

    return $items;
  }

  /**
   * Overrides EntityDefaultUIController::overviewForm().
   */
  public function overviewForm($form, &$form_state) {

    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
      return cacheflush_ui_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['presets']));
    }
    $admin_access = user_access('cacheflush administer');
    drupal_set_title(t('Presets'));
    $form['filters'] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#title' => t('Filter'),
      '#theme' => 'exposed_filters__cacheflush',
      '#access' => $admin_access,
    );

    $form['filters']['container'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('clearfix')),
    );
    $form['filters']['container']['ops'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('filters')),
    );

    $form['filters']['container']['ops']['status'] = array(
      '#type' => 'select',
      '#title' => t('Status'),
      '#options' => array(
        'all' => t('any'),
        1 => t('enabled'),
        0 => t('disabled'),
      ),
      '#default_value' => isset($_GET['status']) ? $_GET['status'] : NULL,
    );
    $form['filters']['container']['ops']['menu'] = array(
      '#type' => 'select',
      '#title' => t('Menu entry'),
      '#options' => array(
        'all' => t('any'),
        1 => t('Yes'),
        0 => t('No'),
      ),
      '#default_value' => isset($_GET['menu']) ? $_GET['menu'] : NULL,
    );

    $form['filters']['container']['actions'] = array(
      '#type' => 'actions',
      '#attributes' => array('class' => array('container-inline')),
    );
    $form['filters']['container']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Filter'),
      '#name' => 'filters',
    );
    $form['filters']['container']['actions']['reset']['#markup'] = l(t('Reset'), $_GET['q']);

    // Build the 'Otions' form.
    $form['options'] = array(
      '#type' => 'fieldset',
      '#title' => t('Options'),
      '#attributes' => array('class' => array('container-inline')),
      '#access' => $admin_access,
    );

    $options = array();
    foreach (module_invoke_all('cacheflush_ui_operations') as $operation => $array) {
      $options[$operation] = $array['label'];
    }
    $form['options']['operation'] = array(
      '#type' => 'select',
      '#title' => t('Operation'),
      '#title_display' => 'invisible',
      '#options' => $options,
      '#default_value' => 'enable',
    );
    $form['options']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#name' => 'op-submit',
    );

    $conditions = array();
    if (isset($_GET['status'])) {
      $conditions['status'] = array('value' => $_GET['status'], 'op' => '=');
    }
    if (isset($_GET['menu'])) {
      $conditions['menu'] = array('value' => $_GET['menu'], 'op' => '=');
    }

    $form['presets'] = $this->overviewTable($conditions);
    $form['pager'] = array('#theme' => 'pager');
    return $form;
  }

  /**
   * Overrides EntityDefaultUIController::overviewFormSubmit().
   */
  public function overviewFormValidate($form, &$form_state) {

    // Error if there are no items to select.
    if ((
        isset($form_state['clicked_button']['#value']) &&
        $form_state['clicked_button']['#name'] == 'op-submit'
        ) &&
        (!is_array($form_state['values']['presets']) ||
        !count(array_filter($form_state['values']['presets'])
        ))
    ) {
      form_set_error('', t('No items selected.'));
    }
  }

  /**
   * Overrides EntityDefaultUIController::overviewFormSubmit().
   */
  public function overviewFormSubmit($form, &$form_state) {
    $args = array();
    if (isset($form_state['values']['status']) && $form_state['values']['status'] != 'all') {
      $args['status'] = $form_state['values']['status'];
    }
    if (isset($form_state['values']['menu']) && $form_state['values']['menu'] != 'all') {
      $args['menu'] = $form_state['values']['menu'];
    }
    $form_state['redirect'] = array(
      'path' => $_GET['q'],
      'options' => array(
        'query' => $args,
      ),
    );
    if (isset($form_state['clicked_button']['#value']) &&
        $form_state['clicked_button']['#name'] == 'op-submit') {
      $this->overviewFormOperationSubmit($form, $form_state);
    }
  }

  /**
   * Process CacheflushUIController::overviewForm form submissions.
   *
   * Executes the chosen 'Update Option' on the selected presets.
   */
  public function overviewFormOperationSubmit($form, &$form_state) {

    $operations = module_invoke_all('cacheflush_ui_operations');
    $operation = $operations[$form_state['values']['operation']];
    // Filter out unchecked presets.
    $presets = array_filter($form_state['values']['presets']);
    if ($function = $operation['callback']) {
      // Add in callback arguments if present.
      if (isset($operation['callback arguments'])) {
        $args = array_merge(array($presets), $operation['callback arguments']);
      }
      else {
        $args = array($presets);
      }
      call_user_func_array($function, $args);
      cache_clear_all();
    }
    else {
      // We need to rebuild the form to go to a second step. For example, to
      // show the confirmation form for the deletion of presets.
      $form_state['rebuild'] = TRUE;
    }
    node_types_rebuild();
    menu_rebuild();
  }

  /**
   * Overrides EntityDefaultUIController::overviewTable().
   */
  public function overviewTable($conditions = array()) {
    $header = array(
      array('data' => t('ID'), 'field' => 'id', 'sort' => 'DESC'),
      array('data' => t('Title'), 'field' => 'c.title'),
      array('data' => t('Author'), 'field' => 'c.uid'),
      array('data' => t('Status'), 'field' => 'c.status'),
      array('data' => t('Menu entry'), 'field' => 'c.menu'),
      array('data' => t('Created'), 'field' => 'c.created'),
      array('data' => t('Operations')),
    );
    $view_any = user_access('cacheflush view any');
    $query = db_select('cacheflush', 'c')
        ->extend('TableSort')->orderByHeader($header)
        ->fields('c', array('id'));

    if ($this->overviewPagerLimit) {
      $query->extend('PagerDefault')->limit($this->overviewPagerLimit);
    }

    if (isset($conditions)) {
      foreach ($conditions as $field => $value) {
        $query->condition('c.' . $field, $value['value'], $value['op']);
      }
    }
    if (!$view_any) {
      $query->condition('c.uid', $GLOBALS['user']->uid, '=');
    }
    $ids = $query->execute()->fetchCol();

    $rows = array();
    $presets = cacheflush_load_multiple($ids);

    foreach ($presets as $preset) {
      $row = $operations = array();
      $user = user_load($preset->uid);
      $row[] = $preset->id;
      $row[] = $preset->title;
      $row[] = theme('username', array('account' => $user));
      $row[] = ($preset->status == 1) ? t('enabled') : t('disabled');
      $row[] = ($preset->menu == 1) ? t('Yes') : t('No');
      $row[] = format_date($preset->created, 'short');
      
      if (cacheflush_ui_access('update', $preset)) {
        $operations['update'] = array(
          'title' => t('Edit'),
          'href' => 'cacheflush/' . $preset->id . '/edit',
          'query' => drupal_get_destination(),
        );
      }
      if (cacheflush_ui_access('delete', $preset)) {
        $operations['delete'] = array(
          'title' => t('Delete'),
          'href' => 'cacheflush/' . $preset->id . '/delete',
          'query' => drupal_get_destination(),
        );
      }

      $row[] = array(
        'data' => array(
          '#theme' => 'links__node_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
      $rows[$preset->id] = $row;
    }

    $render = array(
      '#type' => 'tableselect',
      '#options' => $rows,
      '#header' => $header,
      '#multiple' => TRUE,
      '#empty' => t('No presets available.'),
    );

    return $render;
  }

}

/**
 * Make mass update of presets.
 *
 * Make mass update of presets, changing all presets in the $entity array
 * to update them with the field values in $updates.
 *
 * IMPORTANT NOTE: This function is intended to work when called from a form
 * submission handler. Calling it outside of the form submission process may not
 * work correctly.
 *
 * @param array $entitys
 *   Array of presets ids to update.
 * @param array $updates
 *   Array of key/value pairs with preset field names and the value to update
 *   that field to.
 */
function cacheflush_ui_mass_update(array $entitys, array $updates) {
  // We use batch processing to prevent timeout when updating a large number
  // of presets.
  if (count($entitys) > 10) {
    $batch = array(
      'operations' => array(
        array(
          '_cacheflush_ui_mass_update_batch_process',
          array($entitys, $updates),
        ),
      ),
      'finished' => '_cacheflush_ui_mass_update_batch_finished',
      'title' => t('Processing'),
      // We use a single multi-pass operation, so the default
      // 'Remaining x of y operations' message will be confusing here.
      'progress_message' => '',
      'error_message' => t('The update has encountered an error.'),
      // The operations do not live in the .module file, so we need to
      // tell the batch engine which file to load before calling them.
      'file' => drupal_get_path('module', 'cacheflush_ui') . '/includes/cacheflush_ui.class.inc',
    );
    batch_set($batch);
  }
  else {
    foreach ($entitys as $id) {
      _cacheflush_ui_mass_update_helper($id, $updates);
    }
    drupal_set_message(t('The update has been performed.'));
  }
}

/**
 * Updates individual presets when fewer than 10 are queued.
 *
 * @param int $id
 *   ID of preset to update.
 * @param array $updates
 *   Associative array of updates.
 *
 * @return object
 *   An updated preset object.
 *
 * @see cacheflush_ui_mass_update()
 */
function _cacheflush_ui_mass_update_helper($id, array $updates) {
  $preset = cacheflush_load($id);
  // For efficiency manually save the original preset before applying any
  // changes.
  $preset->original = clone $preset;
  foreach ($updates as $name => $value) {
    $preset->$name = $value;
  }
  cacheflush_save($preset);
  return $preset;
}

/**
 * Executes a batch operation for cacheflush_ui_mass_update().
 *
 * @param array $presets
 *   An array of presets IDs.
 * @param array $updates
 *   Associative array of updates.
 * @param array $context
 *   An array of contextual key/values.
 */
function _cacheflush_ui_mass_update_batch_process(array $presets, array $updates, array &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($presets);
    $context['sandbox']['presets'] = $presets;
  }

  // Process presets by groups of 5.
  $count = min(5, count($context['sandbox']['presets']));
  for ($i = 1; $i <= $count; $i++) {
    // For each id, load the preset, reset the values, and save it.
    $id = array_shift($context['sandbox']['presets']);
    $presets = _cacheflush_ui_mass_update_helper($id, $updates);

    // Store result for post-processing in the finished callback.
    $context['results'][] = l($presets->title, 'cacheflush/' . $presets->id . '/view');

    // Update our progress information.
    $context['sandbox']['progress']++;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Reports the status of batch operation for cacheflush_ui_mass_update().
 *
 * @param bool $success
 *   A boolean indicating whether the batch mass update operation successfully
 *   concluded.
 * @param int $results
 *   The number of presets updated via the batch mode process.
 * @param array $operations
 *   An array of function calls (not used in this function).
 */
function _cacheflush_ui_mass_update_batch_finished($success, $results, array $operations) {
  if ($success) {
    drupal_set_message(t('The update has been performed.'));
  }
  else {
    drupal_set_message(t('An error occurred and processing did not complete.'), 'error');
    $message = format_plural(count($results), '1 item successfully processed:', '@count items successfully processed:');
    $message .= theme('item_list', array('items' => $results));
    drupal_set_message($message);
  }
}

/**
 * Multiple delete confirmation form for CacheflushUIController::overviewForm.
 */
function cacheflush_ui_multiple_delete_confirm($form, &$form_state, $presets) {
  $form['presets'] = array(
    '#prefix' => '<ul>',
    '#suffix' => '</ul>',
    '#tree' => TRUE,
  );
  // array_filter returns only elements with TRUE values.
  foreach ($presets as $id => $value) {
    $title = db_query('SELECT title FROM {cacheflush} WHERE id = :id', array(':id' => $id))->fetchField();
    $form['presets'][$id] = array(
      '#type' => 'hidden',
      '#value' => $id,
      '#prefix' => '<li>',
      '#suffix' => check_plain($title) . "</li>\n",
    );
  }
  $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
  $form['#submit'][] = 'cacheflush_ui_multiple_delete_confirm_submit';
  $confirm_question = format_plural(count($presets), 'Are you sure you want to delete this item?', 'Are you sure you want to delete these items?');
  return confirm_form($form, $confirm_question, cacheflush_ui_get_path(), t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Form submission handler for cacheflush_ui_multiple_delete_confirm().
 */
function cacheflush_ui_multiple_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    cacheflush_delete_multiple(array_keys($form_state['values']['presets']));
    cache_clear_all();
    $count = count($form_state['values']['presets']);
    watchdog('cacheflush', 'Deleted @count presets.', array('@count' => $count));
    drupal_set_message(format_plural($count, 'Deleted 1 preset.', 'Deleted @count presets.'));
  }
  $form_state['redirect'] = cacheflush_ui_get_path();
}
