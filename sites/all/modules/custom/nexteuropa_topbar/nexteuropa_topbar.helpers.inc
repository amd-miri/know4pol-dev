<?php
/**
 * @file
 * Code for the Nexteuropa footer feature.
 */

/**
 * Function defining the nexteuropa user menu.
 *
 * @return array
 *   User menu block array.
 */
function _nexteuropa_topbar_user_menu_info() {
  return [
    'delta' => 'nexteuropa_user_menu',
    'module' => 'nexteuropa_topbar',
    'region' => 'header_top',
    'weight' => -11,
  ];
}

/**
 * Helper function to enable or disable the user menu in the topbar.
 */
function _nexteuropa_topbar_handle_user_menu($op) {
  $context = module_invoke('context', 'load', 'ec_europa_topbar');

  $user_menu = _nexteuropa_topbar_user_menu_info();

  if ($op) {
    $context->reactions['block']['blocks']['nexteuropa_topbar-nexteuropa_user_menu'] = $user_menu;
    $message = t('You activated the user menu, you are going to find it in the top right corner.');
  }
  else {
    if (!empty($context->reactions['block']['blocks']['nexteuropa_topbar-nexteuropa_user_menu'])) {
      unset($context->reactions['block']['blocks']['nexteuropa_topbar-nexteuropa_user_menu']);
      $message = t('You disabled the user menu, it will not appear anymore in the top right corner.');
    }
  }

  module_invoke('context', 'save', $context);
  drupal_set_message($message, 'status', FALSE);
}
