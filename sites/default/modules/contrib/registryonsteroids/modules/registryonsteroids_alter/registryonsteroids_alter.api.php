<?php

/**
 * @file
 * registryonsteroids_alter.api.php
 */

/**
 * Let you alter the suggestions used to extend the element.
 *
 * Let you alter the suggestions used to extend the #theme value of the element.
 *
 * @param array $suggestions
 *   The array of suggestions.
 * @param array $element
 *   The element.
 */
function hook_registryonsteroids_theme_suggestions_alter(array &$suggestions, array &$element) {
  $front = drupal_is_front_page() ? 'front' : NULL;

  // Add a suggestions in the front if the current page is the front page.
  array_unshift($suggestions, $front);

  // Add the current month into the suggestions.
  $suggestions[] = date('F');

  // Add the current day into the suggestions.
  $suggestions[] = date('l');
}

/**
 * Let you alter the suggestions used to extend the element.
 *
 * Let you alter the suggestions used to extend the #theme_wrappers value of the
 * element.
 *
 * @param array $suggestions
 *   The array of suggestions.
 * @param array $element
 *   The element.
 */
function hook_registryonsteroids_theme_wrappers_suggestions_alter(array &$suggestions, array &$element) {
  $front = drupal_is_front_page() ? 'front' : NULL;

  // Add a suggestions in the front if the current page is the front page.
  array_unshift($suggestions, $front);

  // Add the current month into the suggestions.
  $suggestions[] = date('F');

  // Add the current day into the suggestions.
  $suggestions[] = date('l');
}
