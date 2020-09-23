<?php

/**
 * @file
 * Know4pol_core.features.user_permission.inc.
 */

/**
 * Implements hook_user_default_permissions().
 */
function know4pol_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer know4pol search'.
  $permissions['administer know4pol search'] = array(
    'name' => 'administer know4pol search',
    'roles' => array(
      'administrator' => 'administrator',
      'webmaster' => 'webmaster',
    ),
    'module' => 'know4pol_search',
  );

  // Exported permission: 'clear pubsy_import feeds'.
  $permissions['clear pubsy_import feeds'] = array(
    'name' => 'clear pubsy_import feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'clear pubsy_update feeds'.
  $permissions['clear pubsy_update feeds'] = array(
    'name' => 'clear pubsy_update feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'clear pubsy_update_with_a_jrc_number feeds'.
  $permissions['clear pubsy_update_with_a_jrc_number feeds'] = array(
    'name' => 'clear pubsy_update_with_a_jrc_number feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'clear pubsy_update_with_a_specific_date feeds'.
  $permissions['clear pubsy_update_with_a_specific_date feeds'] = array(
    'name' => 'clear pubsy_update_with_a_specific_date feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'webmaster' => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'webmaster' => 'webmaster',
    ),
    'module' => 'node',
  );

  // Exported permission: 'import pubsy_import feeds'.
  $permissions['import pubsy_import feeds'] = array(
    'name' => 'import pubsy_import feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'import pubsy_update feeds'.
  $permissions['import pubsy_update feeds'] = array(
    'name' => 'import pubsy_update feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'import pubsy_update_with_a_jrc_number feeds'.
  $permissions['import pubsy_update_with_a_jrc_number feeds'] = array(
    'name' => 'import pubsy_update_with_a_jrc_number feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'import pubsy_update_with_a_specific_date feeds'.
  $permissions['import pubsy_update_with_a_specific_date feeds'] = array(
    'name' => 'import pubsy_update_with_a_specific_date feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock pubsy_import feeds'.
  $permissions['unlock pubsy_import feeds'] = array(
    'name' => 'unlock pubsy_import feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock pubsy_update feeds'.
  $permissions['unlock pubsy_update feeds'] = array(
    'name' => 'unlock pubsy_update feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock pubsy_update_with_a_jrc_number feeds'.
  $permissions['unlock pubsy_update_with_a_jrc_number feeds'] = array(
    'name' => 'unlock pubsy_update_with_a_jrc_number feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'unlock pubsy_update_with_a_specific_date feeds'.
  $permissions['unlock pubsy_update_with_a_specific_date feeds'] = array(
    'name' => 'unlock pubsy_update_with_a_specific_date feeds',
    'roles' => array(
      'webmaster' => 'webmaster',
    ),
    'module' => 'feeds',
  );

  return $permissions;
}
