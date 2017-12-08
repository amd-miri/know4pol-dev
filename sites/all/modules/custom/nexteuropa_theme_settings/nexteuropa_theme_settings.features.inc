<?php
/**
 * @file
 * nexteuropa_theme_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nexteuropa_theme_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "breakpoints" && $api == "default_breakpoint_group") {
    return array("version" => "1");
  }
  if ($module == "breakpoints" && $api == "default_breakpoints") {
    return array("version" => "1");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return array("version" => "2");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function nexteuropa_theme_settings_image_default_styles() {
  $styles = array();

  // Exported image style: header_image_breakpoints_theme_europa_medium_1x.
  $styles['header_image_breakpoints_theme_europa_medium_1x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_medium_1x',
    'effects' => array(
      11 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 738,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_medium_2x.
  $styles['header_image_breakpoints_theme_europa_medium_2x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_medium_2x',
    'effects' => array(
      10 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 738,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_mobile_1x.
  $styles['header_image_breakpoints_theme_europa_mobile_1x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_mobile_1x',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 290,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_mobile_2x.
  $styles['header_image_breakpoints_theme_europa_mobile_2x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_mobile_2x',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 290,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_narrow_1x.
  $styles['header_image_breakpoints_theme_europa_narrow_1x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_narrow_1x',
    'effects' => array(
      9 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_narrow_2x.
  $styles['header_image_breakpoints_theme_europa_narrow_2x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_narrow_2x',
    'effects' => array(
      8 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_normal_1x.
  $styles['header_image_breakpoints_theme_europa_normal_1x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_normal_1x',
    'effects' => array(
      13 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 962,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_normal_2x.
  $styles['header_image_breakpoints_theme_europa_normal_2x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_normal_2x',
    'effects' => array(
      12 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 962,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_wide_1x.
  $styles['header_image_breakpoints_theme_europa_wide_1x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_wide_1x',
    'effects' => array(
      15 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1140,
          'height' => '',
          'upscale' => 1,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_breakpoints_theme_europa_wide_2x.
  $styles['header_image_breakpoints_theme_europa_wide_2x'] = array(
    'label' => 'header_image_breakpoints_theme_europa_wide_2x',
    'effects' => array(
      14 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1140,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 1,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: header_image_module_picture_empty_srcset_1x.
  $styles['header_image_module_picture_empty_srcset_1x'] = array(
    'label' => 'header_image_module_picture_empty_srcset_1x',
    'effects' => array(
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1140,
          'height' => '',
          'upscale' => 0,
          'retinafy' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_medium_1x.
  $styles['highlight_image_breakpoints_theme_europa_medium_1x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_medium_1x',
    'effects' => array(
      23 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 365,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_medium_2x.
  $styles['highlight_image_breakpoints_theme_europa_medium_2x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_medium_2x',
    'effects' => array(
      24 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 365,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_mobile_1x.
  $styles['highlight_image_breakpoints_theme_europa_mobile_1x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_mobile_1x',
    'effects' => array(
      25 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 290,
          'height' => 193,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_mobile_2x.
  $styles['highlight_image_breakpoints_theme_europa_mobile_2x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_mobile_2x',
    'effects' => array(
      26 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 290,
          'height' => 193,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_narrow_1x.
  $styles['highlight_image_breakpoints_theme_europa_narrow_1x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_narrow_1x',
    'effects' => array(
      27 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 364,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_narrow_2x.
  $styles['highlight_image_breakpoints_theme_europa_narrow_2x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_narrow_2x',
    'effects' => array(
      28 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 364,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_normal_1x.
  $styles['highlight_image_breakpoints_theme_europa_normal_1x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_normal_1x',
    'effects' => array(
      29 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 364,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_normal_2x.
  $styles['highlight_image_breakpoints_theme_europa_normal_2x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_normal_2x',
    'effects' => array(
      30 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 546,
          'height' => 364,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_wide_1x.
  $styles['highlight_image_breakpoints_theme_europa_wide_1x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_wide_1x',
    'effects' => array(
      31 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 360,
          'height' => 240,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_breakpoints_theme_europa_wide_2x.
  $styles['highlight_image_breakpoints_theme_europa_wide_2x'] = array(
    'label' => 'highlight_image_breakpoints_theme_europa_wide_2x',
    'effects' => array(
      32 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 360,
          'height' => 240,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: highlight_image_module_picture_empty_srcset_1x.
  $styles['highlight_image_module_picture_empty_srcset_1x'] = array(
    'label' => 'highlight_image_module_picture_empty_srcset_1x',
    'effects' => array(
      33 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 360,
          'height' => 240,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_medium_1x.
  $styles['teaser_image_breakpoints_theme_europa_medium_1x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_medium_1x',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_medium_2x.
  $styles['teaser_image_breakpoints_theme_europa_medium_2x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_medium_2x',
    'effects' => array(
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_mobile_1x.
  $styles['teaser_image_breakpoints_theme_europa_mobile_1x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_mobile_1x',
    'effects' => array(
      6 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 290,
          'height' => 193,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_mobile_2x.
  $styles['teaser_image_breakpoints_theme_europa_mobile_2x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_mobile_2x',
    'effects' => array(
      8 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 290,
          'height' => 193,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_narrow_1x.
  $styles['teaser_image_breakpoints_theme_europa_narrow_1x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_narrow_1x',
    'effects' => array(
      10 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 300,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_narrow_2x.
  $styles['teaser_image_breakpoints_theme_europa_narrow_2x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_narrow_2x',
    'effects' => array(
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 300,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_normal_1x.
  $styles['teaser_image_breakpoints_theme_europa_normal_1x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_normal_1x',
    'effects' => array(
      14 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_normal_2x.
  $styles['teaser_image_breakpoints_theme_europa_normal_2x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_normal_2x',
    'effects' => array(
      16 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_wide_1x.
  $styles['teaser_image_breakpoints_theme_europa_wide_1x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_wide_1x',
    'effects' => array(
      18 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_breakpoints_theme_europa_wide_2x.
  $styles['teaser_image_breakpoints_theme_europa_wide_2x'] = array(
    'label' => 'teaser_image_breakpoints_theme_europa_wide_2x',
    'effects' => array(
      20 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: teaser_image_module_picture_empty_srcset_1x.
  $styles['teaser_image_module_picture_empty_srcset_1x'] = array(
    'label' => 'teaser_image_module_picture_empty_srcset_1x',
    'effects' => array(
      22 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 167,
          'retinafy' => 0,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
