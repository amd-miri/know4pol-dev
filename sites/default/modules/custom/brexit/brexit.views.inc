<?php

/**
 * @file
 * Views integration file for Brexit module.
 */

/**
 * Implements hook_views_data().
 */
function brexit_views_data() {
  $tables['brexit']['table']['group'] = t('Brexit');
  $tables['brexit']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  // Tread as boolean field.
  $tables['brexit']['vid'] = array(
    'title' => t('Boolean field'),
    'help' => t('Brexit revision indicator.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has revision for Brexit'),
      'type' => 'yes-no',
      // Cheating a bit with the filter, since vid <> 0 will achieve the boolean indicator.
      'use equal' => FALSE,
      // Since left join.
      'accept null' => TRUE,
    ),
  );

  return $tables;
}
