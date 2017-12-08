<?php
/**
 * @file
 * nexteuropa_theme_settings.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function nexteuropa_theme_settings_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ds_extras_field_template';
  $strongarm->value = 1;
  $export['ds_extras_field_template'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'easy_breadcrumb-include_title_segment';
  $strongarm->value = 0;
  $export['easy_breadcrumb-include_title_segment'] = $strongarm;
  return $export;
}
