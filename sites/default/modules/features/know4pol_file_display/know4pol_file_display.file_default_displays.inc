<?php

/**
 * @file
 * know4pol_file_display.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function know4pol_file_display_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_enclosure';
  $file_display->weight = -49;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['video__featured__file_field_enclosure'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_file_default';
  $file_display->weight = -37;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['video__featured__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_file_download_link';
  $file_display->weight = -36;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['video__featured__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_file_table';
  $file_display->weight = -41;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['video__featured__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_file_url_plain';
  $file_display->weight = -42;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['video__featured__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_file_video';
  $file_display->weight = -33;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'controls' => 1,
    'controls_list' => array(
      'fullscreen' => 'fullscreen',
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'loop' => 0,
    'muted' => 0,
    'width' => '400',
    'height' => '226',
    'preload' => '',
    'multiple_file_behavior' => 'tags',
  );
  $export['video__featured__file_field_file_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_media_large_icon';
  $file_display->weight = -38;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
  );
  $export['video__featured__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__file_field_ne_download_button';
  $file_display->weight = -39;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'label' => 'Download',
  );
  $export['video__featured__file_field_ne_download_button'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_avportal_image';
  $file_display->weight = -50;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
  );
  $export['video__featured__media_avportal_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_avportal_video';
  $file_display->weight = -45;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '400',
    'height' => '225',
  );
  $export['video__featured__media_avportal_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_dailymotion_image';
  $file_display->weight = -32;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
    'width' => '',
    'height' => '',
  );
  $export['video__featured__media_dailymotion_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_dailymotion_video';
  $file_display->weight = -34;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '400',
    'height' => '225',
    'autoplay' => 0,
    'iframe' => 1,
  );
  $export['video__featured__media_dailymotion_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_node_image';
  $file_display->weight = -40;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
  );
  $export['video__featured__media_node_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_vimeo_image';
  $file_display->weight = -43;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
  );
  $export['video__featured__media_vimeo_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_vimeo_video';
  $file_display->weight = -44;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '400',
    'height' => '225',
    'color' => '',
    'protocol_specify' => 0,
    'protocol' => 'https://',
    'autoplay' => 0,
    'loop' => 0,
    'title' => 1,
    'byline' => 0,
    'portrait' => 0,
    'api' => 0,
  );
  $export['video__featured__media_vimeo_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_youtube_image';
  $file_display->weight = -47;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
  );
  $export['video__featured__media_youtube_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__media_youtube_video';
  $file_display->weight = -48;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'width' => '400',
    'height' => '225',
    'theme' => 'dark',
    'color' => 'red',
    'autohide' => '2',
    'captions' => '1',
    'autoplay' => 0,
    'loop' => 0,
    'showinfo' => 0,
    'modestbranding' => 1,
    'rel' => 0,
    'nocookie' => 1,
    'protocol_specify' => 0,
    'protocol' => 'https:',
    'enablejsapi' => 0,
    'origin' => '',
  );
  $export['video__featured__media_youtube_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__no_wrapper_media_avportal_video';
  $file_display->weight = -31;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
  );
  $export['video__featured__no_wrapper_media_avportal_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__no_wrapper_media_dailymotion_video';
  $file_display->weight = -35;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '560',
    'height' => '340',
    'autoplay' => 0,
    'iframe' => 1,
  );
  $export['video__featured__no_wrapper_media_dailymotion_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__no_wrapper_media_vimeo_video';
  $file_display->weight = -46;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '360',
    'color' => '',
    'protocol_specify' => 0,
    'protocol' => 'https://',
    'autoplay' => 0,
    'loop' => 0,
    'title' => 1,
    'byline' => 1,
    'portrait' => 1,
    'api' => 0,
  );
  $export['video__featured__no_wrapper_media_vimeo_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__featured__no_wrapper_media_youtube_video';
  $file_display->weight = -30;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'width' => '640',
    'height' => '390',
    'theme' => 'dark',
    'color' => 'red',
    'autohide' => '2',
    'captions' => FALSE,
    'autoplay' => 0,
    'loop' => 0,
    'showinfo' => 1,
    'modestbranding' => 0,
    'rel' => 1,
    'nocookie' => 0,
    'protocol_specify' => 0,
    'protocol' => 'https:',
    'enablejsapi' => 0,
    'origin' => '',
  );
  $export['video__featured__no_wrapper_media_youtube_video'] = $file_display;

  return $export;
}
