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
  // maybe move this to template with preprocess.
  if ($view->name == "organisation_related_knowledge_services") {
    // When result.
    if (isset($view->result) && !empty($view->result)) {
      $node = menu_get_item()['page_arguments'][0];
      if (isset($node->field_org_ks_specific_desc[LANGUAGE_NONE])) {
        // Go through all values.
        foreach ($node->field_org_ks_specific_desc[LANGUAGE_NONE] as $item) {
          $node_field_collection = field_collection_item_load($item['value'], FALSE);
          $ks_desc_nid = $node_field_collection->field_org_ks_desc_related_ks[LANGUAGE_NONE][0]['target_id'];
          // Needded to render properly fields.
          $collection = $node_field_collection->view('full');
          $ks_desc_new_description = render($collection['field_collection_item'][$item['value']]['field_org_ks_desc_specific_desc']);
          // Find the corresponding in the view to alter.
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

/**
 * Implements hook_views_query_alter().
 */
function know4pol_core_views_query_alter(&$view, &$query) {
  if ($view->name == 'organisation_related_knowledge_services') {
    // Get the nid.
    if ($node = menu_get_object()) {
      $nid = $node->nid;
    }
    $dbquery = db_select('og_membership', 'om');
    $dbquery->distinct();
    $dbquery->fields('om', array('gid'));
    $dbquery->condition('etid', $nid);
    $result = $dbquery->execute()->fetchAll();
    foreach ($result as $row) {
      $tids[] = $row->gid;
    }
    $query->add_where(1, 'node.nid', $tids, 'IN');
  }
}
