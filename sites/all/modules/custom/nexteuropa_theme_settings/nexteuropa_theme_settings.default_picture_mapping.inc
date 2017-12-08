<?php
/**
 * @file
 * nexteuropa_theme_settings.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function nexteuropa_theme_settings_default_picture_mapping() {
  $export = array();

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Header image';
  $picture_mapping->machine_name = 'header_image';
  $picture_mapping->breakpoint_group = 'europa';
  $picture_mapping->mapping = array(
    'breakpoints.theme.europa.wide' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_wide_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_wide_2x',
      ),
    ),
    'breakpoints.theme.europa.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_normal_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_normal_2x',
      ),
    ),
    'breakpoints.theme.europa.medium' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_medium_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_medium_2x',
      ),
    ),
    'breakpoints.theme.europa.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_narrow_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_narrow_2x',
      ),
    ),
    'breakpoints.theme.europa.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_mobile_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'header_image_breakpoints_theme_europa_mobile_2x',
      ),
    ),
  );
  $export['header_image'] = $picture_mapping;

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Highlight image';
  $picture_mapping->machine_name = 'highlight_image';
  $picture_mapping->breakpoint_group = 'europa';
  $picture_mapping->mapping = array(
    'breakpoints.theme.europa.wide' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_wide_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_wide_2x',
      ),
    ),
    'breakpoints.theme.europa.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_normal_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_normal_2x',
      ),
    ),
    'breakpoints.theme.europa.medium' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_medium_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_medium_2x',
      ),
    ),
    'breakpoints.theme.europa.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_narrow_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_narrow_2x',
      ),
    ),
    'breakpoints.theme.europa.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_mobile_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'highlight_image_breakpoints_theme_europa_mobile_2x',
      ),
    ),
  );
  $export['highlight_image'] = $picture_mapping;

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Teaser image';
  $picture_mapping->machine_name = 'teaser_image';
  $picture_mapping->breakpoint_group = 'europa';
  $picture_mapping->mapping = array(
    'breakpoints.theme.europa.wide' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_wide_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_wide_2x',
      ),
    ),
    'breakpoints.theme.europa.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_normal_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_normal_2x',
      ),
    ),
    'breakpoints.theme.europa.medium' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_medium_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_medium_2x',
      ),
    ),
    'breakpoints.theme.europa.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_narrow_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_narrow_2x',
      ),
    ),
    'breakpoints.theme.europa.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_mobile_1x',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_image_breakpoints_theme_europa_mobile_2x',
      ),
    ),
  );
  $export['teaser_image'] = $picture_mapping;

  return $export;
}
