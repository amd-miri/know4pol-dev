<?php

/**
 * @file
 * Administration forms for the ECAS module.
 */

/**
 * Implements hook_help().
 *
 * @todo Move this to the main .module file.
 */
function ecas_help($section) {
  switch ($section) {
    case 'admin/modules#description':
      return t('Allows users to authenticate via ECAS.');
  }
}

/**
 * Implements hook_permission().
 *
 * @todo Move this to the main .module file.
 */
function ecas_permission() {
  return array(
    'administer ecas' => array(
      'title' => t('Administer ECAS'),
      'description' => t('Perform administration tasks for ECAS.'),
    ),
  );
}

/**
 * Implements hook_menu().
 *
 * @todo Move this to the main .module file.
 */
function ecas_menu() {
  $items = array();

  $items['admin/config/ecas'] = array(
    'title' => 'EU Login',
    'description' => 'EU Login configuration settings.',
    'page callback' => 'system_admin_menu_block_page',
    'access arguments' => array('administer ecas'),
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
    'position' => 'right',
    'weight' => -20,
  );

  $items['admin/config/ecas/settings'] = array(
    'title' => 'Settings',
    'description' => 'EU Login configuration settings',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('ecas_admin_settings'),
    'access arguments' => array('administer ecas'),
    'type' => MENU_NORMAL_ITEM | MENU_LOCAL_TASK,
    'weight' => -10,
  );

  if (function_exists('_ecas_menu')) {
    _ecas_menu($items);
  }

  return $items;
}

/**
 * Form constructor for the ECAS administration form.
 */
function ecas_admin_settings() {
  $form['param'] = array(
    '#type' => 'fieldset',
    '#title' => t('EU Login module settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['param']['ecas_assurance_level'] = array(
    '#type' => 'select',
    '#title' => t('EU Login Assurance Level for this application'),
    '#default_value' => variable_get('ecas_assurance_level', constant('ECAS_DEFAULT_ASSURANCE_LEVEL')),
    '#options' => _ecas_assurance_levels(),
    '#description' => t('The EU Login Assurance Level defines which kinds of users may log into the application.'),
  );

  $ecas_domains = array(ECAS_DEFAULT_DOMAIN => 'Do not force the default domain');
  $ecas_domains += _ecas_domains();

  $form['param']['ecas_domain'] = array(
    '#type' => 'select',
    '#title' => t('Default EU Login domain'),
    '#default_value' => variable_get('ecas_domain', ECAS_DEFAULT_DOMAIN),
    '#options' => $ecas_domains,
    '#description' => t('This option specifies the default domain that will be displayed on the login page if none is specified in cookies sent by the browser.'),
  );

  $form['param']['ecas_account_request_url'] = array(
    '#type' => 'textfield',
    '#title' => t('EU Login Account Request URL'),
    '#default_value' => variable_get('ecas_account_request_url', ECAS_DEFAULT_ACCOUNT_REQUEST_URL),
    '#description' => t('URL used to redirect the user to the EU Login account request service. The %local_ecas_url% placeholder will be replaced by the absolute URL to /ecas.'),
  );
  $form['param']['ecas_change_password_url'] = array(
    '#type' => 'textfield',
    '#title' => t('EU Login Change Password URL'),
    '#default_value' => variable_get('ecas_change_password_url', ECAS_DEFAULT_CHANGE_PASSWORD_URL),
    '#description' => t('URL given to an EU Login user when he tries to get his password back using the user/password page.'),
  );

  $form['param']['debug_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug options'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('ecas_phpcas_debug', 0),
  );
  $form['param']['debug_fieldset']['ecas_phpcas_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable phpCas client debug mode.'),
    '#default_value' => variable_get('ecas_phpcas_debug', 0),
    '#description' => t('If this option is checked, the phpCAS client will log many informations for each login attempt in a given file.'),
  );
  $form['param']['debug_fieldset']['ecas_phpcas_debug_logpath'] = array(
    '#type' => 'textfield',
    '#title' => t('phpCas debug file path'),
    '#default_value' => variable_get('ecas_phpcas_debug_logpath', constant('ECAS_DEFAULT_DEBUG_LOGPATH')),
    '#description' => t('If the phpCas client debug mode is enabled, the debug informations will be stored into this file. Specify either an absolute path, or a path relative to the Drupal directory. Please ensure this file is writable by Drupal since this module does not check it.'),
  );

  $options = array('1' => t('Active'), '0' => t('Blocked'));
  $form['param']['ecas_account_option'] = array(
    '#type' => 'radios',
    '#title' => t('User account status (first login)'),
    '#default_value' => variable_get('ecas_account_option', 1),
    '#options' => $options,
    '#description' => t('Status of the user account after creation'),
  );

  $form['param'][ECAS_LOGIN_MESSAGE] = array(
    '#type' => 'textfield',
    '#title' => t('Login message'),
    '#default_value' => variable_get(ECAS_LOGIN_MESSAGE, _ecas_get_default_login_message()),
    '#description' => t('Status message shown to the user after login. Available placeholders: %ecas_username'),
  );

  $form['param'][ECAS_WARNING_MESSAGE] = array(
    '#type' => 'text_format',
    '#title' => t('Warning page message'),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('Message on the warning page when a blocked account user is trying to log in'),
  );

  _ecas_text_format_set_default_value($form['param'], ECAS_WARNING_MESSAGE);

  $form['param'][ECAS_WARNING_MESSAGE_NO_EMAIL] = array(
    '#type' => 'text_format',
    '#title' => t('Error message text in case of an missing e-mail address'),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('Text supplying information about the error caused by the an e-mail in the EU Login profile used in another.'),
  );

  _ecas_text_format_set_default_value(
    $form['param'],
    ECAS_WARNING_MESSAGE_NO_EMAIL
  );

  $form['param'][ECAS_WARNING_MESSAGE_EXISTING_EMAIL] = array(
    '#type' => 'text_format',
    '#title' => t('Error message text in case of an e-mail address already used'),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('Text supplying information about the error caused by the an e-mail in the EU Login profile used in another.'),
  );

  _ecas_text_format_set_default_value(
   $form['param'],
   ECAS_WARNING_MESSAGE_EXISTING_EMAIL
  );

  $form['param'][ECAS_WARNING_MESSAGE_NOT_CREATED] = array(
    '#type' => 'text_format',
    '#title' => t('Error message text in case of an drupal user is not created'),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('Text supplying information about the error caused by the non-creation of Drupal user from an EU Login profile.'),
  );
  _ecas_text_format_set_default_value(
   $form['param'],
   ECAS_WARNING_MESSAGE_NOT_CREATED
  );

  $form['param'][ECAS_WARNING_MESSAGE_INCOMPLETE_USER] = array(
    '#type' => 'text_format',
    '#title' => t('Error message text in case of an ecas user is incomplete'),
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t(
     'Text supplying information about the error because the EU Login profile does not contain the required data, other then the email.'
    ),
  );
  _ecas_text_format_set_default_value(
   $form['param'],
   ECAS_WARNING_MESSAGE_INCOMPLETE_USER
  );

  $form['param']['ecas_update_mail_address'] = array(
    '#type' => 'checkbox',
    '#title' => t("Update the user's mail address at login time."),
    '#default_value' => variable_get('ecas_update_mail_address', 1),
    '#description' => t('If this option is checked, the EU Login module will replace the mail address of the user with the one retrieved from the LDAP instance.'),
  );

  // ECAS has these extra user profile fields:
  // - 'First name field'
  // - 'Last name field'
  // - 'ECAS mail field'
  //
  // Profile and content profile do no longer exist for Drupal 7. Instead the
  // recommended method of adding extra user fields is done through the core
  // fields API. Fields are now also available for core user profiles.
  // Checkbox to enable or disable the whole integration stuff.
  $form['param']['ecas_profile_core_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable integration with the &quot;core user fields&quot;'),
    '#default_value' => variable_get('ecas_profile_core_enabled', 0),
    '#description' => t('If this option is checked, the EU Login feature will attempt to fill the extra core user fields with information retrieved from the LDAP instance: first name, last name, mail address'),
  );

  $form['param']['profile_core_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Core user fields integration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => !variable_get('ecas_profile_core_enabled', 0),
  );

  $form['param']['profile_core_fieldset']['ecas_profile_core_firstname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Firstname field'),
    '#default_value' => variable_get('ecas_profile_core_firstname_field', ECAS_DEFAULT_PROFILE_FIRSTNAME_FIELD),
    '#description' => t('Enter here the machinename of the field that will be filled with the firstname retrieved from ECAS. Leave empty if you do not want to retrieve it.'),
  );

  $form['param']['profile_core_fieldset']['ecas_profile_core_lastname_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Lastname field'),
    '#default_value' => variable_get('ecas_profile_core_lastname_field', ECAS_DEFAULT_PROFILE_LASTNAME_FIELD),
    '#description' => t('Enter here the machinename of the field that will be filled with the lastname retrieved from EU Login. Leave empty if you do not want to retrieve it.'),
  );

  $form['param']['profile_core_fieldset']['ecas_profile_core_ecas_email_field'] = array(
    '#type' => 'textfield',
    '#title' => t('ECAS Mail address field'),
    '#default_value' => variable_get('ecas_profile_core_ecas_email_field', ECAS_DEFAULT_PROFILE_ECAS_MAIL_FIELD),
    '#description' => t('Enter here the machinename of the field that will be filled with the mail address retrieved from ECAS. Leave empty if you do not want to retrieve it.'),
  );

  $args = array(
    '!link' => l(t('the admin page'), 'admin/config/people/accounts/fields'),
  );
  $form['param']['profile_core_fieldset']['footnote'] = array(
    '#markup' => '<p>' . t('Note: You can configure the core user fields using !link.', $args) . '</p>',
  );

  // Checkbox dedicated to the 'group_sync' module, developed by the FPFIS team.
  if (module_exists('group_sync')) {
    // Checkbox to enable or disable the whole integration stuff.
    $form['param']['ecas_group_sync_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable integration with the &quot;FPFIS Group Sync&quot; module'),
      '#default_value' => variable_get('ecas_group_sync_enabled', 0),
      '#description' => t('If this option is checked, the EU Login module will trigger the FPFIS Group Sync module to sync the user.'),
    );
  }

  // FPFIS Common SETTINGS.
  // Checkbox to enable or disable the whole FPFIS integration stuff.
  $form['param']['ecas_use_shared_fpfis'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the shared &quot;FPFIS Common&quot; library'),
    '#default_value' => variable_get('ecas_use_shared_fpfis', 0),
    '#description' => t('If this option is checked, the EU Login feature
    will attempt use the shared FPFIS Common library to connect to LDAP
    and the EU Login server. Otherwise a local implementation will be used.'),
  );

  return system_settings_form($form);
}

/**
 * Returns the assurance levels.
 *
 * @return array
 *   An associative array of assurance levels descriptions, keyed by
 *   assurance level.
 */
function _ecas_assurance_levels() {
  $assurance_levels = array(
    'TOP' => t('TOP: EC only'),
    'HIGH' => t('HIGH: + Other institutions'),
    'MEDIUM' => t('MEDIUM: + Sponsored'),
    'LOW' => t('LOW: + External + Self-registered'),
  );
  drupal_alter('ecas_assurance_levels', $assurance_levels);
  return $assurance_levels;
}

/**
 * Returns the available ECAS domains.
 *
 * @return array
 *   The available ECAS domains.
 */
function _ecas_domains() {
  $known_ecas_domains = array(
    'eu.europa.ec' => 'European Commission',
    'eu.europa.cdt' => 'Translation Centre',
    'eu.europa.curia' => 'Court of Justice of the European Union',
    'eu.europa.gsa' => 'European GNSS Supervisory Authority',
    'eu.europa.eca' => 'European Court of Auditors',
    'external' => 'External',
    'eu.europa.consilium' => 'Council of the European Union',
    'eu.europa.eesc' => 'European Economic and Social Committee',
    'eu.europa.cor' => 'Committee of the Regions',
    'eu.europa.europarl' => 'European Parliament',
  );
  drupal_alter('ecas_domains', $known_ecas_domains);
  return $known_ecas_domains;
}

/**
 * Sets the default value of a text_format form input based on a variable.
 *
 * @param array $form_param_input
 *   The 'param' item of the form input containing the where to set the
 *   default value.
 * @param string $variable_name
 *   The variable name containing the default value.
 */
function _ecas_text_format_set_default_value(array &$form_param_input, $variable_name) {

  $value = variable_get($variable_name, _ecas_get_default_warning_message($variable_name));

  if (is_array($value)) {
    $form_param_input[$variable_name]['#default_value'] = $value['value'];
    $form_param_input[$variable_name]['#format'] = $value['format'];

    return;
  }

  $form_param_input[$variable_name]['#default_value'] = $value;
  $form_param_input[$variable_name]['#format'] = filter_default_format();
}
