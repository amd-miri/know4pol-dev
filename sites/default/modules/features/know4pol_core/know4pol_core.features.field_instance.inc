<?php

/**
 * @file
 * Know4pol_core.features.field_instance.inc.
 */

/**
 * Implements hook_field_default_field_instances().
 */
function know4pol_core_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-topic-field_av_image'.
  $field_instances['node-topic-field_av_image'] = array(
    'bundle' => 'topic',
    'deleted' => 0,
    'description' => 'Caption to be set in the property of the media fields (File description). Should be EC copyright owner',
    'display' => array(
      'apachesolr_page' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'content_footer' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 34,
      ),
      'featured' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'featured',
        ),
        'type' => 'file_rendered',
        'weight' => 0,
      ),
      'navigation' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'navigation',
        ),
        'type' => 'file_rendered',
        'weight' => 1,
      ),
      'node_embed' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_av_image',
    'label' => 'Image or Video',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'entity_translation_sync' => FALSE,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'avportal' => 'avportal',
          'dailymotion' => 'dailymotion',
          'node' => 0,
          'private' => 0,
          'public' => 'public',
          'vimeo' => 'vimeo',
          'youtube' => 'youtube',
        ),
        'allowed_types' => array(
          'archive' => 0,
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 'video',
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 'media_default--media_browser_1',
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 'media_internet',
          'upload' => 'upload',
        ),
      ),
      'type' => 'media_generic',
      'weight' => 25,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Caption to be set in the property of the media fields (File description). Should be EC copyright owner');
  t('Image or Video');

  return $field_instances;
}
