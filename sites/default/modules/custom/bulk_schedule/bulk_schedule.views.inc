<?php

/**
 * @file
 * Views integration file for bulk_schedule module.
 */

/**
 * Implements hook_views_data().
 */
function bulk_schedule_views_data() {
  $tables['bulk_schedule']['table']['group'] = t('Bulk Schedule');
  $tables['bulk_schedule']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  // Tread as boolean field.
  $tables['bulk_schedule']['vid'] = array(
    'title' => t('Boolean field'),
    'help' => t('Bulk scheduled indicator.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => FALSE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has revision for bulk scheduling'),
      'type' => 'yes-no',
      // Cheating a bit with the filter, <> 0 will achieve this.
      'use equal' => FALSE,
      // Since left join.
      'accept null' => TRUE,
    ),
  );

  return $tables;
}
