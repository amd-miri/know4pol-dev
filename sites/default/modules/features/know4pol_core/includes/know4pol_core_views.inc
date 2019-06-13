<?php

/**
 * @file
 * Views integration file for know4pol-core feature.
 */

/**
 * Implements hook_views_api().
 */
function know4pol_core_views_api() {
  return array(
    'api' => 3,
  );
}

/**
 * Implements hook_views_data().
 */
function know4pol_core_views_data() {
  $data = array();

  // Create a custom views filter.
  $data['node']['pubsy_only'] = array(
    'group' => t('Custom'),
    'real field' => 'field_pub_dc_rel_ispartofseries',
    'title' => t('Pubsy only'),
    'help' => t('Show only the Pubsy publications.'),
    'filter' => array(
      'handler' => 'Know4polCoreHandlerFilterPubsyOnly',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_pre_build().
 */
function know4pol_core_views_pre_build(&$view) {
  // For all views, if they use the og_vocabulary.
  if (isset($view->argument['og_vocabulary_target_id'])) {
    $node = menu_get_item();
    $view->args[] = $node['page_arguments'][0]->og_vocabulary[LANGUAGE_NONE][0]['target_id'];
  }
}

/**
 * Implements hook_views_pre_render().
 */
function know4pol_core_views_pre_render(&$view) {
  // For the organisation_related_knowledge_services view,
  // we would replace the description field by
  // the organisation custom KS descripion field,if availaible.
  if ($view->name == "organisation_related_knowledge_services") {
    $node = menu_get_item();
    if (isset($node['page_arguments'][0]->field_org_ks_specific_desc[LANGUAGE_NONE])) {
      foreach ($node['page_arguments'][0]->field_org_ks_specific_desc[LANGUAGE_NONE] as $item) {
        $node_field_collection = field_collection_item_load($item['value'], FALSE);
        $ks_desc_nid = $node_field_collection->field_org_ks_desc_related_ks[LANGUAGE_NONE][0]['target_id'];
        $ks_desc_new_description = $node_field_collection->field_org_ks_desc_specific_desc[LANGUAGE_NONE][0]['value'];
        if (isset($view->result) && !empty($view->result) && !empty($ks_desc_new_description)) {
          foreach ($view->result as $key => $value) {
            if ($value->nid == $ks_desc_nid) {
              $view->result[$key]->field_field_short_description[0]['rendered']['#markup'] =
              $view->result[$key]->field_field_short_description[0]['raw']['value'] =
              $view->result[$key]->field_field_short_description[0]['raw']['safe_value'] = $ks_desc_new_description;
            }
          }
        }
      }
    }
  }
}
