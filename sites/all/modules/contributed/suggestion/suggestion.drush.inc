<?php

/**
 * @file
 * Drush commands for suggestion module.
 */

/**
 * Implements hook_drush_command().
 */
function suggestion_drush_command() {
  return array(
    'suggestion-clear' => array(
      'description'         => 'Clear the suggestion table.',
      'drupal dependencies' => array(),
      'aliases'             => array('sug-clear'),
    ),
    'suggestion-index' => array(
      'description'         => 'Index suggestions.',
      'drupal dependencies' => array(),
      'aliases'             => array('sug-index'),
    ),
  );
}

/**
 * Truncate suggestion table.
 */
function drush_suggestion_clear() {
  variable_set('suggestion_synced', FALSE);
  SuggestionStorage::truncateSuggestion();
  drush_log('Cleared the suggestion table.', 'status');
}

/**
 * Index suggestions.
 */
function drush_suggestion_index() {
  drush_log('Indexing...', 'status');
  SuggestionHelper::index();
  drush_log('Finished indexing suggestions.', 'status');
}
