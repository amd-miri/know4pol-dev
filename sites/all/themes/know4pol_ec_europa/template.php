<?php

/**
 * @file
 * Default theme functions.
 */

/**
 * Implements hook_menu_link().
 */
function know4pol_ec_europa_menu_link(array $variables) {
  // Add a class to menu links that link to unpublished nodes.
  $element = $variables['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
    $sub_menu = str_replace('<ul class="', '<ul class="dropdown-menu ', $sub_menu);
  }
  if (preg_match('@^node/(\d+)$@', $element['#href'], $matches)) {
    $node = node_load((int) $matches[1]);
    if ($node && $node->status == NODE_NOT_PUBLISHED) {
      // There appear to be some inconsistency
      // sometimes the classes come through
      // as an array and sometimes as a string.
      if (empty($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = array();
      }
      elseif (is_string($element['#localized_options']['attributes']['class'])) {
        $element['#localized_options']['attributes']['class'] = explode(' ', $element['#localized_options']['attributes']['class']);
      }
      $element['#localized_options']['attributes']['class'][] = 'menu-node-unpublished';
    }
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  $output = html_entity_decode($output);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements template_preprocess_node().
 */
function know4pol_ec_europa_preprocess_node(&$variables, $hook) {
  // For all content types.
  drupal_add_js('https://visualise.jrc.ec.europa.eu/javascripts/api/viz_v1.js', 'external');
  //drupal_add_js(path_to_theme() . '/assets/scripts/ecl-navigation-inpages.js', array('group' => JS_THEME));

  /* COUNEJE */

  // Node is a file
  if($variables['type'] == 'file') _preprocess_node_file($variables, $hook);
}
  
function _preprocess_node_file(&$variables, $hook) {
  $node = $variables['elements']['#node'];
  // is file a link or a file ?
  $node->file_link = _preprocess_node_file__field_file($node);
  // filetype icon
  $_icon_css = $node->field_file_type[LANGUAGE_NONE][0]['taxonomy_term']->field_file_type_classname[LANGUAGE_NONE];
  // default icon if no type
  $node->file_type_css = "." . count($_icon_css)?$_icon_css[0][value]:'ecl-icon--file';
  
  
  // languages versions
  $translations = translation_node_get_translations($node->nid);
  foreach ($translations as $t) {
    // other languages olny
	if($t->nid != $node->nid) {
	  $t_node = node_load($t->nid);
	  $t_node->file_link = _preprocess_node_file__field_file($t_node);
      $node->translations->data[] = $t_node;
	}
  }
} 

function _preprocess_node_file__field_file($node) {
  // Build link for ECL download 
  // If file is external
  if (count($node->field_is_legacy_link) && $node->field_is_legacy_link[LANGUAGE_NONE][0]['value']) {
	$link = $node->field_legacy_link[LANGUAGE_NONE][0][url];
  }
  // If internal and we have a file
  elseif (count($node->field_file_file)) {
	$file = $node->field_file_file[LANGUAGE_NONE][0];
    $link = file_create_url($file['uri']);
	$size = file_size_human($file['filesize']);
  }
  $info = [];
  if($size) $info[] = $size;
  if($more_info) $info[] = $more_info;  
  
  $info = join (' - ', $info);
  $info = (strlen($info))?'(' . $info . ')':null;
  
  return ['link'=>$link, 'info'=>$info];
}
/**
 * Implements hook_preprocess_hook().
 */
function know4pol_ec_europa_preprocess_menu_link__user_menu(&$variables) {
  $variables['element']['#attributes']['class'] = ['ecl-navigation-list__item'];
}

/**
 * Provides a readable filesize text from number;
 * Author: couneje;
 */

function file_size_human($size, $i=0, $base=1024) {
	// iterate per base until it can't be divided.
	for(;$size > $base; $size /= $base, $i++);
	// return rounded number and unit
	return round($size, $i>0?2:0) . ' ' . ["bytes", "KB", "MB", "GB", "TB", "PB", "><"][$i];
}
