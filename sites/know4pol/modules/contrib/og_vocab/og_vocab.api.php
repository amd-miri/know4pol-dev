<?php


/**
 * @file
 * Hooks provided by the Organic groups vocabulary module.
 */

/**
 * @addtogroup hooks
 * @{
 */


/**
 * Allow modules to return TRUE if we are insiede an OG vocab admin
 * context.
 *
 * @return
 *   If countext found array keyed by the group-type and the group ID.
 */
function hook_og_vocab_is_admin_context() {
  $item = menu_get_item();
  if (strpos($item['path'], 'foo/admin') === 0){
    return array('group_type' => 'node', 'gid' => 1);
  }
}

/**
 * @} End of "addtogroup hooks".
 */

 /**
 * Implements og_vocab_get_accessible_vocabs_alter().
 */
function hook_og_vocab_get_accessible_vocabs_alter(&$result) {

  $query = db_select('og_vocab_relation', 'ogr');
  $query->fields('ogr', array('vid'));
  // Join with the OG-vocab.
  $query->innerJoin('og_vocab', 'ogv', 'ogr.vid = ogv.vid');
  $query->condition('ogv.entity_type', 'node');
  $result = $query
    ->execute()
    ->fetchAllAssoc('vid');
}
