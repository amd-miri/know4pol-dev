<?php

/**
 * @file
 * Cacheflush Rules action include.
 */

/**
 * Implements hook_rules_event_info().
 */
function cacheflush_rules_rules_event_info() {
  return array(
    'cacheflush_before' => array(
      'label' => t('Before clearing cache'),
      'group' => t('Cacheflush'),
      'variables' => array(
        'cacheflush' => array(
          'type' => 'cacheflush',
          'label' => t('Preset'),
        ),
      ),
    ),
    'cacheflush_after' => array(
      'label' => t('After clearing cache'),
      'group' => t('Cacheflush'),
      'variables' => array(
        'cacheflush' => array(
          'type' => 'cacheflush',
          'label' => t('Preset'),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 */
function cacheflush_rules_rules_action_info() {

  return array(
    'cacheflush_run_preset' => array(
      'base' => 'cacheflush_rules_clear',
      'label' => t('Clear cache by entity id.'),
      'group' => t('Cacheflush'),
      'parameter' => array(
        'preset_id' => array(
          'type' => 'integer',
          'label' => t('Entity id'),
        ),
      ),
    ),
  );
}

/**
 * Rules action function.
 */
function cacheflush_rules_clear($id) {
  module_load_include('inc', 'cacheflush', 'cacheflush.api');
  _cacheflush_clear_preset($id);
}
