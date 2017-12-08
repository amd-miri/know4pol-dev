<?php

/**
 * @file
 * Nexteuropa footer drush integration.
 */

/**
 * Implements hook_drush_command().
 *
 * @see drush_parse_command()
 */
function nexteuropa_footer_drush_command() {
  $items = [];

  $items['ec-footer-translate'] = [
    'description' => t('Translate EC Footer menu items.'),
    'options' => [
      'all' => t('Generate all the menu items.'),
    ],
    'drupal dependencies' => ['features'],
    'aliases' => ['ecfooter'],
  ];

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function nexteuropa_footer_drush_help($section) {
  switch ($section) {
    case 'drush:ec-footer-translate':
      return dt('Translate EC Footer menu items.');
  }
}

/**
 * Generate dummy content.
 */
function drush_nexteuropa_footer_ec_footer_translate($all = TRUE) {
  if ($all && $logs = _nexteuropa_footer_translate()) {
    foreach ($logs['title'] as $title) {
      $tokens = ['@menu_name' => $title['menu_name'], '@lang' => $title['lang']];
      drush_print(dt('Menu @menu_name title translation: "@lang" updated.', $tokens));
    }

    foreach ($logs['item'] as $title) {
      $tokens = ['@mlid' => $title['mlid'], '@lang' => $title['lang']];
      drush_print(dt('Menu item @mlid translation: "@lang" updated.', $tokens));
    }
  }
}
