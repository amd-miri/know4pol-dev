<?php

/**
 * @file
 * jrc_events_core.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function jrc_events_core_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_institute_banner',
      1 => 'field_institute_name',
      2 => 'field_institute_slogan',
      3 => 'field_co_com_email',
      4 => 'field_pubsy_ids',
      5 => 'name',
      6 => 'description',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_content|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_content|node|event|form';
  $field_group->group_name = 'group_event_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_location',
      2 => 'field_country_iso',
      3 => 'field_event_involvement',
      4 => 'field_event_registration',
      5 => 'field_event_type',
      6 => 'field_image',
      7 => 'field_short_title',
      8 => 'field_town',
      9 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-event-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_event_content|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_date|node|event|form';
  $field_group->group_name = 'group_event_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Dates',
    'weight' => '4',
    'children' => array(
      0 => 'field_event_date',
      1 => 'field_last_update',
      2 => 'field_publish_date',
      3 => 'field_unpublish_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-event-date field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_event_date|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_metadata|node|event|form';
  $field_group->group_name = 'group_event_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '6',
    'children' => array(
      0 => 'field_resource',
      1 => 'field_meta_creator',
      2 => 'field_mk',
      3 => 'path',
      4 => 'redirect',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-event-metadata field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_event_metadata|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institute_news|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_institute_news';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'News Colors',
    'weight' => '4',
    'children' => array(
      0 => 'field_institute_central_news_lab',
      1 => 'field_institute_news_button',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institute-news field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_institute_news|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institute_right_blocks|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_institute_right_blocks';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Right Blocks Colors',
    'weight' => '3',
    'children' => array(
      0 => 'field_institute_right_block_lab',
      1 => 'field_institute_right_col_bg',
      2 => 'field_institute_right_menu_bg',
      3 => 'field_institute_right_menu_hover',
      4 => 'field_institute_right_menu_item',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institute-right-blocks field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_institute_right_blocks|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institute_top_banner|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_institute_top_banner';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Top & Banner Color',
    'weight' => '1',
    'children' => array(
      0 => 'field_institute_banner_color',
      1 => 'field_institute_top_stripe_color',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institute-top-banner field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_institute_top_banner|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institutes_carousel|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_institutes_carousel';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Carousel Colors',
    'weight' => '2',
    'children' => array(
      0 => 'field_institute_carousel_bg',
      1 => 'field_institute_carousel_bullet',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institutes-carousel field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_institutes_carousel|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institutes_science_areas|taxonomy_term|institutes|form';
  $field_group->group_name = 'group_institutes_science_areas';
  $field_group->entity_type = 'taxonomy_term';
  $field_group->bundle = 'institutes';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Science Areas Colors',
    'weight' => '5',
    'children' => array(
      0 => 'field_institute_footer_bg',
      1 => 'field_institute_footer_lab',
      2 => 'field_institute_footer_term_lab',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institutes-science-areas field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_institutes_science_areas|taxonomy_term|institutes|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_old_info|node|event|form';
  $field_group->group_name = 'group_old_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Old information',
    'weight' => '3',
    'children' => array(
      0 => 'field_old_id',
      1 => 'field_original_keywords',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-old-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_old_info|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_related|node|event|form';
  $field_group->group_name = 'group_related';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Related information',
    'weight' => '1',
    'children' => array(
      0 => 'field_related_content',
      1 => 'field_related_documents',
      2 => 'field_related_twitter_hashtag',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-related field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_related|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_subsite_group_content|node|event|form';
  $field_group->group_name = 'group_subsite_group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Subsite group content',
    'weight' => '5',
    'children' => array(
      0 => 'og_group_ref',
      1 => 'group_content_access',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-subsite-group-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_subsite_group_content|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomies|node|event|form';
  $field_group->group_name = 'group_taxonomies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Taxonomies',
    'weight' => '2',
    'children' => array(
      0 => 'field_tags',
      1 => 'field_highlighted',
      2 => 'field_identities',
      3 => 'field_institutes',
      4 => 'field_related_topics',
      5 => 'field_research_areas',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-taxonomies field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_taxonomies|node|event|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Carousel Colors');
  t('Content');
  t('Dates');
  t('Metadata');
  t('News Colors');
  t('Old information');
  t('Related information');
  t('Right Blocks Colors');
  t('Science Areas Colors');
  t('Subsite group content');
  t('Taxonomies');
  t('Top & Banner Color');

  return $field_groups;
}
