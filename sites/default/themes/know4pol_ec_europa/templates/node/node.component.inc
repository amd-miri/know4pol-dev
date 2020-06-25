<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node(&$variables, $hook) {
  // For all content types.
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', 'external');
  switch ($variables['type']) {
    case 'file':
      _know4pol_ec_europa_preprocess_node__file($variables);
      break;

    case 'external_page':
      _know4pol_ec_europa_preprocess_node__external_page($variables);
      break;

    case 'visualisation':
      if ($variables['view_mode'] == 'node_embed' && isset($variables['field_vis_link_embed'][LANGUAGE_NONE][0])) {
        /* KNOW4POL-400 make the title link if flag checked */
        if ($variables['field_vis_link_embed'][LANGUAGE_NONE][0]['value'] == 0) {
          $variables['content']['title'][0]['#markup'] = strip_tags($variables['content']['title']['#items'][0]['value'], '<h3>');
          unset($variables['content']['node_link']);
        }
      }
      break;

    case 'knowledge_centre':
      // Those fields should be present together or removed.
      if (!isset($variables['content']['field_av_image']) || !isset($variables['content']['field_av_summary'])) {
        unset($variables['content']['field_av_image']);
        unset($variables['content']['field_av_summary']);
      }
      if (!isset($variables['content']['body']) || !isset($variables['content']['field_briefing_file'])) {
        unset($variables['content']['body']);
        unset($variables['content']['field_briefing_file']);
      }
      break;

    case 'topic':
      // Not in featured mode, no picture.
      if ($variables['view_mode'] == 'navigation' && !$variables['field_featured'][LANGUAGE_NONE][0]['value']) {
        unset($variables['content']['field_av_image']);
      }
      break;
  }
}

/**
 * Implements template_preprocess_node().
 *
 * @param array $variables
 *   The original variables from the preprocess_node hook.
 */
function _know4pol_ec_europa_preprocess_node__file(array &$variables) {
  $node = $variables['elements']['#node'];
  // Is file a link or a file ?
  $node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
    $node->field_is_legacy_link,
    $node->field_legacy_link,
    $node->field_file_file
  );
  // Filetype icon.
  $_icon_css = $node->field_file_type[LANGUAGE_NONE][0]['taxonomy_term']->field_file_type_classname[LANGUAGE_NONE];
  // Default icon if no type.
  $node->file_type_css = "." . count($_icon_css) ? $_icon_css[0]['value'] : 'ecl-icon--file';
  // Languages versions.
  $translations = translation_node_get_translations($node->nid);
  foreach ($translations as $t) {
    // Other languages olny.
    if ($t->nid != $node->nid) {
      $t_node = node_load($t->nid);
      $t_node->file_link = _know4pol_ec_europa_preprocess_node_file__field_file(
        $t_node->field_is_legacy_link,
        $t_node->field_legacy_link,
        $t_node->field_file_file
      );
      $node->translations->data[] = $t_node;
    }
  }
}

/**
 * Implements template_preprocess_node().
 *
 * @param array $variables
 *   The original variables from the preprocess_node hook.
 */
function _know4pol_ec_europa_preprocess_node__external_page(array &$variables) {
  // Default values if empty.
  if (!isset($variables['field_frame_height'][0]['value'])) {
    $variables['field_frame_height'] = [['value' => 350]];
  }
  // Default values if empty.
  if (!isset($variables['field_frame_width'][0]['value'])) {
    $variables['field_frame_width'] = [['value' => '100%']];
  }
}

/**
 * Preprocess fields field_file.
 *
 * Analyse legacy link content
 * and possible more info to display into the ECL block.
 *
 * @param array $field_is_legacy_link
 *   The field field_is_legacy_link of the content.
 * @param array $field_legacy_link
 *   The field field_legacy_link of the content.
 * @param array $field_file_file
 *   The field field_file_file of the content.
 *
 * @return array
 *   Parameters of the file (link and infos).
 */
function _know4pol_ec_europa_preprocess_node_file__field_file(array $field_is_legacy_link, array $field_legacy_link, array $field_file_file) {
  // Build link for ECL download.
  // If file is external.
  if (count($field_is_legacy_link) && $field_is_legacy_link[LANGUAGE_NONE][0]['value']) {
    $link = $field_legacy_link[LANGUAGE_NONE][0]['url'];
  }
  // If internal and we have a file.
  elseif (count($field_file_file)) {
    $file = $field_file_file[LANGUAGE_NONE][0];
    $link = file_create_url($file['uri']);
    $size = _know4pol_ec_europa_file_size_human($file['filesize']);
  }
  $info = array();
  if (isset($size)) {
    $info[] = $size;
  }
  // Check if type can be guessed from file extension.
  if (preg_match('/.*\.([\w]{2,4})(\?.*?)?$/i', $link, $matches)) {
    // Check type and map to restrict and avoid errors.
    if ($type = [
      'doc' => "DOC",
      'docx' => "DOC",
      'pdf' => "PDF",
      'zip' => "ZIP",
      'xls' => "XLS",
      'xslx' => "XLS",
      'ppt' => "Powerpoint",
      'pptx' => "Powerpoint",
      'txt' => "Text",
    ][drupal_strtolower($matches[1])]) {
      // Could be improved with mimetype mapping a taxonomy.
      $info[] = $type;
    }
  }

  $info = implode(' - ', $info);
  $info = (drupal_strlen($info)) ? '(' . $info . ')' : NULL;

  return array('link' => $link, 'info' => $info);
}
