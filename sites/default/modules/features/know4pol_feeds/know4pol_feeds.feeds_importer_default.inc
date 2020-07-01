<?php

/**
 * @file
 * know4pol_feeds.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function know4pol_feeds_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'jrc_datasets_update';
  $feeds_importer->config = array(
    'name' => 'JRC datasets update',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsExJsonPath',
      'config' => array(
        'sources' => array(
          'dataset_id' => array(
            'name' => 'dataset_id',
            'value' => 'name',
            'debug' => 0,
            'weight' => '0',
          ),
          'field_dst_related_organistaion' => array(
            'name' => 'field_dst_related_organistaion',
            'value' => 'organization.title',
            'debug' => 0,
            'weight' => '1',
          ),
          'field_dst_point_of_contact' => array(
            'name' => 'field_dst_point_of_contact',
            'value' => 'extras[?(@[\'key\']==\'contact-email\')].value',
            'debug' => 0,
            'weight' => '2',
          ),
          'full_title' => array(
            'name' => 'full_title',
            'value' => 'title',
            'debug' => 0,
            'weight' => '3',
          ),
          'short_title' => array(
            'name' => 'short_title',
            'value' => 'title',
            'debug' => 0,
            'weight' => '4',
          ),
          'body' => array(
            'name' => 'body',
            'value' => 'notes',
            'debug' => 0,
            'weight' => '5',
          ),
          'field_dst_data_access_files_titl' => array(
            'name' => 'field_dst_data_access_files_title',
            'value' => 'resources[?(@[\'resource_type\']==\'distribution\')].name',
            'debug' => 0,
            'weight' => '7',
          ),
          'field_dst_data_access_files_url' => array(
            'name' => 'field_dst_data_access_files_url',
            'value' => 'resources[?(@[\'resource_type\']==\'distribution\')].url',
            'debug' => 0,
            'weight' => '8',
          ),
          'field_dst_other_resources_title' => array(
            'name' => 'field_dst_other_resources_title',
            'value' => 'resources[?(@[\'resource_type\']==\'other_resource\' || @[\'resource_type\']==\'publication\')].name',
            'debug' => 0,
            'weight' => '11',
          ),
          'field_dst_other_resources_url' => array(
            'name' => 'field_dst_other_resources_url',
            'value' => 'resources[?(@[\'resource_type\']==\'other_resource\' || @[\'resource_type\']==\'publication\')].url',
            'debug' => 0,
            'weight' => '12',
          ),
          'field_last_update' => array(
            'name' => 'field_last_update',
            'value' => 'extras[?(@[\'key\']==\'date-updated\')].value',
            'debug' => 0,
            'weight' => '13',
          ),
          'field_dst_issue_date' => array(
            'name' => 'field_dst_issue_date',
            'value' => 'extras[?(@[\'key\']==\'date-released\')].value',
            'debug' => 0,
            'weight' => '14',
          ),
          'field_dst_landing_page' => array(
            'name' => 'field_dst_landing_page',
            'value' => 'url',
            'debug' => 0,
            'weight' => '15',
          ),
          'field_dst_geographic_area' => array(
            'name' => 'field_dst_geographic_area',
            'value' => 'extras[?(@[\'key\']==\'geographic_area_list\')].value',
            'debug' => 0,
            'weight' => '16',
          ),
          'field_dst_temporal_coverage_star' => array(
            'name' => 'field_dst_temporal_coverage_start',
            'value' => 'extras[?(@[\'key\']==\'temporal-coverage\')].value',
            'debug' => 0,
            'weight' => '17',
          ),
          'field_dst_temporal_coverage_end' => array(
            'name' => 'field_dst_temporal_coverage_end',
            'value' => 'extras[?(@[\'key\']==\'temporal-coverage\')].value',
            'debug' => 0,
            'weight' => '18',
          ),
          'field_dst_update_frequency' => array(
            'name' => 'field_dst_update_frequency',
            'value' => 'extras[?(@[\'key\']==\'frequency-of-update\')].value',
            'debug' => 0,
            'weight' => '19',
          ),
          'field_dst_dataset_language' => array(
            'name' => 'field_dst_dataset_language',
            'value' => 'extras[?(@[\'key\']==\'dataset-language\')].value',
            'debug' => 0,
            'weight' => '21',
          ),
          'field_tags' => array(
            'name' => 'field_tags',
            'value' => 'tags.*.name',
            'debug' => 0,
            'weight' => '22',
          ),
          'updated_date' => array(
            'name' => 'updated_date',
            'value' => 'metadata_modified',
            'debug' => 0,
            'weight' => '23',
          ),
          'created_date' => array(
            'name' => 'created_date',
            'value' => 'metadata_created',
            'debug' => 0,
            'weight' => '24',
          ),
        ),
        'context' => array(
          'value' => 'result.results.*',
        ),
        'display_errors' => 0,
        'source_encoding' => array(
          0 => 'auto',
        ),
        'debug_mode' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'dataset_id',
            'target' => 'field_dst_dataset_id',
            'unique' => 1,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'field_dst_related_organistaion',
            'target' => 'field_related_organisations:label',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'field_dst_point_of_contact',
            'target' => 'field_dst_point_of_contact',
            'unique' => FALSE,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'full_title',
            'target' => 'title_field',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'short_title',
            'target' => 'title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          5 => array(
            'source' => 'body',
            'target' => 'body:et:en',
            'unique' => FALSE,
            'language' => 'und',
          ),
          6 => array(
            'source' => 'field_tags',
            'target' => 'field_tags',
            'unique' => FALSE,
            'language' => 'und',
          ),
          7 => array(
            'source' => 'field_dst_data_access_files_titl',
            'target' => 'field_dst_data_files:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          8 => array(
            'source' => 'field_dst_data_access_files_url',
            'target' => 'field_dst_data_files:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          9 => array(
            'source' => 'field_dst_other_resources_title',
            'target' => 'field_dst_other_resources:title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          10 => array(
            'source' => 'field_dst_other_resources_url',
            'target' => 'field_dst_other_resources:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          11 => array(
            'source' => 'field_dst_issue_date',
            'target' => 'field_dst_issue_date:start',
            'timezone' => '__SITE__',
            'language' => 'und',
          ),
          12 => array(
            'source' => 'field_dst_landing_page',
            'target' => 'field_dst_landing_page:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
          13 => array(
            'source' => 'field_dst_geographic_area',
            'target' => 'field_geographic_coverage',
            'term_search' => '0',
            'autocreate' => 1,
            'language' => 'und',
          ),
          14 => array(
            'source' => 'field_dst_temporal_coverage_star',
            'target' => 'field_dst_temporal_coverage:start',
            'timezone' => '__SITE__',
            'language' => 'und',
          ),
          15 => array(
            'source' => 'field_dst_temporal_coverage_end',
            'target' => 'field_dst_temporal_coverage:end',
            'timezone' => '__SITE__',
            'language' => 'und',
          ),
          16 => array(
            'source' => 'field_dst_update_frequency',
            'target' => 'field_update_frequency',
            'term_search' => '0',
            'autocreate' => 1,
            'language' => 'und',
          ),
          17 => array(
            'source' => 'field_dst_dataset_language',
            'target' => 'field_dst_dataset_language',
            'term_search' => '0',
            'autocreate' => 1,
            'language' => 'und',
          ),
          18 => array(
            'source' => 'created_date',
            'target' => 'created',
            'unique' => FALSE,
            'language' => 'und',
          ),
          19 => array(
            'source' => 'updated_date',
            'target' => 'changed',
            'unique' => FALSE,
            'language' => 'und',
          ),
          20 => array(
            'source' => 'updated_date',
            'target' => 'field_last_update:start',
            'timezone' => '__SITE__',
            'language' => 'und',
          ),
          21 => array(
            'source' => 'Blank source 1',
            'target' => 'status',
            'unique' => FALSE,
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'dataset',
        'language' => 'en',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '43200',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['jrc_datasets_update'] = $feeds_importer;

  return $export;
}
