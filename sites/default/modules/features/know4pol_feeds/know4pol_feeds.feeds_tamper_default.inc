<?php

/**
 * @file
 * know4pol_feeds.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function know4pol_feeds_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-blank_source_1-default_value';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'Blank source 1';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => '0',
    'only_if_empty' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set value or default value';
  $export['jrc_datasets_update-blank_source_1-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-body-rewrite';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'body';
  $feeds_tamper->plugin_id = 'rewrite';
  $feeds_tamper->settings = array(
    'text' => '<p>[body]</p>',
  );
  $feeds_tamper->weight = 2;
  $feeds_tamper->description = 'Rewrite';
  $export['jrc_datasets_update-body-rewrite'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-body-trim';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'body';
  $feeds_tamper->plugin_id = 'trim';
  $feeds_tamper->settings = array(
    'mask' => '',
    'side' => 'trim',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Trim';
  $export['jrc_datasets_update-body-trim'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_geographic_area-find_replace_regex';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_geographic_area';
  $feeds_tamper->plugin_id = 'find_replace_regex';
  $feeds_tamper->settings = array(
    'find' => '/(.*?\\"label\\"\\:\\s*\\")|(\\"}]$)/',
    'replace' => '',
    'limit' => '',
    'real_limit' => -1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Find replace REGEX';
  $export['jrc_datasets_update-field_dst_geographic_area-find_replace_regex'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_issue_date-default_value';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_issue_date';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'now',
    'only_if_empty' => 1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set value or default value';
  $export['jrc_datasets_update-field_dst_issue_date-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_other_resources_title-truncate_text';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_other_resources_title';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '255',
    'ellipses' => 1,
    'wordsafe' => 1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['jrc_datasets_update-field_dst_other_resources_title-truncate_text'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_related_organistaion-default_value';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_related_organistaion';
  $feeds_tamper->plugin_id = 'default_value';
  $feeds_tamper->settings = array(
    'default_value' => 'JRC',
    'only_if_empty' => 0,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Set value or default value';
  $export['jrc_datasets_update-field_dst_related_organistaion-default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_temporal_coverage_end-find_replace_regex';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_temporal_coverage_end';
  $feeds_tamper->plugin_id = 'find_replace_regex';
  $feeds_tamper->settings = array(
    'find' => '/(.*\\"start_date": "[0-9\\-]+)|("\\}]$)/',
    'replace' => '',
    'limit' => '',
    'real_limit' => -1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Find replace REGEX';
  $export['jrc_datasets_update-field_dst_temporal_coverage_end-find_replace_regex'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_temporal_coverage_end-find_replace_regex2';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_temporal_coverage_end';
  $feeds_tamper->plugin_id = 'find_replace_regex';
  $feeds_tamper->settings = array(
    'find' => '/.*?"end_date"\\:\\s*"/',
    'replace' => '',
    'limit' => '',
    'real_limit' => -1,
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Find replace REGEX';
  $export['jrc_datasets_update-field_dst_temporal_coverage_end-find_replace_regex2'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_temporal_coverage_end-newsroom_default_value';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_temporal_coverage_end';
  $feeds_tamper->plugin_id = 'newsroom_default_value';
  $feeds_tamper->settings = array(
    'default_value' => '[field_dst_temporal_coverage_star]',
  );
  $feeds_tamper->weight = 2;
  $feeds_tamper->description = 'Set default value if field is empty';
  $export['jrc_datasets_update-field_dst_temporal_coverage_end-newsroom_default_value'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_dst_temporal_coverage_star-find_replace_regex';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_dst_temporal_coverage_star';
  $feeds_tamper->plugin_id = 'find_replace_regex';
  $feeds_tamper->settings = array(
    'find' => '/(.*\\"start_date":\\s*")|(\\"}]$)|(",.*)/',
    'replace' => '',
    'limit' => '',
    'real_limit' => -1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Find replace REGEX';
  $export['jrc_datasets_update-field_dst_temporal_coverage_star-find_replace_regex'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-field_tags-convert_case';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'field_tags';
  $feeds_tamper->plugin_id = 'convert_case';
  $feeds_tamper->settings = array(
    'mode' => 'ucfirst',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert case';
  $export['jrc_datasets_update-field_tags-convert_case'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'jrc_datasets_update-short_title-truncate_text';
  $feeds_tamper->importer = 'jrc_datasets_update';
  $feeds_tamper->source = 'short_title';
  $feeds_tamper->plugin_id = 'truncate_text';
  $feeds_tamper->settings = array(
    'num_char' => '255',
    'ellipses' => 1,
    'wordsafe' => 1,
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Truncate';
  $export['jrc_datasets_update-short_title-truncate_text'] = $feeds_tamper;

  return $export;
}
