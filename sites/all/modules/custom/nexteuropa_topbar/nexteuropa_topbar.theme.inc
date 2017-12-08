<?php

/**
 * @file
 * Nexteuropa user menu.
 */

/**
 * Returns HTML for the element.
 *
 * @param mixed $variables
 *   An associative array.
 *
 * @return string
 *   The markup itself.
 */
function theme_nexteuropa_user_menu($variables) {
  global $user;

  if (user_is_logged_in()) {
    if (module_exists('ecas')) {
      $logout_url = url('/ecaslogout');
    }
    else {
      $logout_url = url('/user/logout');
    }

    $items = [];
    $items[] = [
      'data' => t('Logged in as @username', ['@username' => format_username($user)]),
      'class' => ['site-user-menu__option'],
    ];
    $items[] = [
      'data' => l(t('Log out'), $logout_url),
      'class' => ['site-user-menu__option'],
    ];

    $variables = [
      'items' => $items,
      'attributes' => [
        'class' => [
          'site-user-menu__list',
        ],
      ],
    ];
    return theme('item_list', $variables);
  }
  else {
    if (theme_get_setting('ec_europa_user_login', 'europa')) {
      $path = module_exists('ecas') ? 'ecas' : 'user';
      $login = l(t('Log in'), $path, ['attributes' => ['class' => ['site-user-menu__list']]]);
      return $login;
    }
  }
}
