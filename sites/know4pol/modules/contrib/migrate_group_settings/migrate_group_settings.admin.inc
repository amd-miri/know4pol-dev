<?php

/**
 * @file
 * Administration page.
 */

/**
 * Configuration form. It allows to edit database connection settings
 * for all migration groups.
 */
function migrate_group_settings_admin_settings($form, &$form_state) {

  $result = db_select('migrate_group', 'mg')
            ->fields('mg', array('name', 'arguments'))
            ->execute()->fetchAll();

  if (is_array($result)) {

    $form['total_groups'] = array(
      '#type' => 'hidden',
      '#value' => count($result),
    );

    $form['vt'] = array(
      '#type' => 'vertical_tabs',
      '#title' => 'Database connection for each group',
    );

    $index = 0;

    foreach($result as $r) {

      // Decrypt and unserialize.
      $arguments = unserialize($r->arguments);
      $arguments = MigrationBase::decryptArguments($arguments);

      $database = $arguments['source_database'];

      $form['vt'][$r->name] = array(
        '#type' => 'fieldset',
        '#title' => $r->name,
        '#weight' => 5,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#group' => 'content_types_config',
      );

      $form['vt'][$r->name][$index . '_group'] = array(
        '#type' => 'hidden',
        '#value' => $r->name,
      );

      $form['vt'][$r->name][$index . '_database'] = array(
        '#type' => 'textfield',
        '#title' => t('Database name'),
        '#default_value' => $database['database'],
      );
      
      $form['vt'][$r->name][$index . '_username'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#default_value' => $database['username'],
      );
      
      $form['vt'][$r->name][$index . '_password'] = array(
        '#type' => 'textfield',
        '#title' => t('Password'),
        '#default_value' => $database['password'],
      );

      $form['vt'][$r->name][$index . '_host'] = array(
        '#type' => 'textfield',
        '#title' => t('Host'),
        '#default_value' => $database['host'],
      );

      $form['vt'][$r->name][$index . '_db_prefix'] = array(
        '#type' => 'textfield',
        '#title' => t('Table prefix'),
        '#default_value' => $database['db_prefix'],
      );

      $form['vt'][$r->name][$index . '_port'] = array(
        '#type' => 'textfield',
        '#title' => t('Database port'),
        '#default_value' => $database['port'],
      );

      $index++;

    }
  }
  else {
    $form['from'] = array(
      '#type' => 'item',
      '#markup' => t("You don't have any migration group"),
    );
  }

  $form['#submit'][] = 'migrate_group_settings_admin_settings_submit';
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * Configuration form submit.
 */
function migrate_group_settings_admin_settings_submit($form, &$form_state) {

  $values = $form_state['values'];

  // For each migration group.
  for($i=0;$i<$values['total_groups'];$i++) {

    // Gather submitted values.
    $group = $values[$i . '_group'];
    $database = $values[$i . '_database'];
    $username = $values[$i . '_username'];
    $password = $values[$i . '_password'];
    $db_prefix = $values[$i . '_db_prefix'];
    $port = $values[$i . '_port'];
    $host = $values[$i . '_host'];
    
    // Get all arguments.
    $result = db_select('migrate_group', 'mg')
              ->fields('mg', array('name', 'arguments'))
              ->condition('name', $group, '=')
              ->execute()->fetchAssoc();

    if (!empty($result['arguments'])) {

      // Decrypt and unserialize.
      $arguments = unserialize($result['arguments']);
      $arguments = MigrationBase::decryptArguments($arguments);
      
      // Modify database connection arguments.
      $arguments['source_database']['database'] = $database;
      $arguments['source_database']['username'] = $username;
      $arguments['source_database']['password'] = $password;
      $arguments['source_database']['db_prefix'] = $db_prefix;
      $arguments['source_database']['port'] = $port;
      $arguments['source_database']['host'] = $host;

      // Encrypt and serialize.
      $arguments = MigrationBase::encryptArguments($arguments);
      $arguments = serialize($arguments);
      
      // Update all arguments.
      $num_updated = db_update('migrate_group')
                     ->fields(array(
                       'arguments' => $arguments,
                     ))
                     ->condition('name', $group, '=')
                     ->execute();
    }
  }
}
