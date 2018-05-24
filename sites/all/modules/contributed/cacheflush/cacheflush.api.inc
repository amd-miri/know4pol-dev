<?php

/**
 * @file
 * Cacheflusher module inc file with dinamic clear cache functions.
 */

/**
 * Clear all caches function.
 */
function _cacheflush_clear_all() {

  // Clear all caches.
  drupal_flush_all_caches();
  drupal_set_message(t('All caches cleared.'));
  drupal_goto($_SERVER['HTTP_REFERER']);
}

/**
 * Call clear cache and send back.
 *
 * @param int $preset_id
 *   Preset id to do clear cache for.
 */
function cacheflush_clear_preset_menu_callback($preset_id) {
  _cacheflush_clear_preset($preset_id);
  drupal_goto($_SERVER['HTTP_REFERER']);
}

/**
 * Based on settings decide witch clear cache function to be called.
 *
 * @param int $preset_id
 *   Preset id to do clear cache for.
 */
function _cacheflush_clear_preset($preset_id) {

  $entity = cacheflush_load($preset_id);
  if (!$entity) {
    drupal_set_message(t('Invalid ID'), 'error');
    return;
  }
  if ($entity->status == 0) {
    drupal_set_message(t('This entity is disabled.'), 'error');
    drupal_access_denied();
    return;
  }
  // Call: hook_cacheflush_before_clear().
  module_invoke_all('cacheflush_before_clear', $entity);

  $presets = unserialize($entity->data);

  if ($presets) {
    foreach ($presets as $cache) {
      foreach ($cache['functions'] as $value) {
        call_user_func_array($value['#name'], $value['#params']);
      }
    }
  }

  drupal_set_message(t("All predefined cache options at @name was cleared.", array('@name' => $entity->title)));
  // Call: hook_cacheflush_after_clear().
  module_invoke_all('cacheflush_after_clear', $entity);
}
