<?php
/**
 * @file
 * nexteuropa_ds_fields.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function nexteuropa_ds_fields_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'europa_content_type_label';
  $ds_field->label = 'Content type label';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[node:content-type]',
      'format' => 'basic_html',
    ),
    'use_token' => 1,
  );
  $export['europa_content_type_label'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'europa_user_fullname_first';
  $ds_field->label = 'Full name (name first)';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'user' => 'user',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[user:field-firstname] [user:field-lastname]',
      'format' => 'basic_html',
    ),
    'use_token' => 1,
  );
  $export['europa_user_fullname_first'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'europa_user_fullname_last';
  $ds_field->label = 'Full name (surname first)';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'user' => 'user',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[user:field-lastname] [user:field-firstname]',
      'format' => 'basic_html',
    ),
    'use_token' => 1,
  );
  $export['europa_user_fullname_last'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'europa_collapse_button';
  $ds_field->label = 'Collapse button';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
    'taxonomy_term' => 'taxonomy_term',
    'comment' => 'comment',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<button class="btn btn-collapse" type="button" data-toggle="collapse" data-target="#collapse" aria-expanded="false" aria-controls="collapse"><span class="toggling-text"></span><i class="icon icon--blue-dark"></i></button>',
      'format' => 'full_html',
    ),
    'use_token' => 1,
  );
  $export['europa_collapse_button'] = $ds_field;

  return $export;
}
