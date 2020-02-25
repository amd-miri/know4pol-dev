<?php

/**
 * @file
 * Block related hooks for know4pol-search module.
 */

/**
 * Implements hook_block_info().
 */
function know4pol_search_block_info() {
  $blocks['know4pol_search'] = array(
    'info' => t('Know4pol search form block'),
    'cache' => DRUPAL_NO_CACHE,
  );
  $blocks['know4pol_main_search'] = array(
    'info' => t('Know4pol main search form block'),
    'cache' => DRUPAL_NO_CACHE,
  );
  $blocks['apachesolr_freetext_search_block'] = array(
    'info' => t('Apache Solr Search Block'),
    'cache' => DRUPAL_NO_CACHE,
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 *
 * Displays the search form block.
 */
function know4pol_search_block_view($delta = '') {
  $block = array();

  // Prevent strict warnings.
  $searchform = drupal_get_form('know4pol_search_form');
  $mainsearchform = drupal_get_form('know4pol_mainsearch_form');

  switch ($delta) {
    case 'apachesolr_freetext_search_block':
      $arg = menu_get_item()['map'];
      if ($arg[0] == 'search' && $arg[1] == 'site') {
        $keys = urldecode($arg[2]);
      }
      else {
        $keys = urldecode($arg[1]);
      }
      $block_content = drupal_get_form('_know4pol_search_freetext_search_form', $keys);
      $block['content'] = drupal_render($block_content);
      break;

    case 'know4pol_search':
      $block['subject'] = t('Search our KnowledgeBase');
      $block['content'] = drupal_render($searchform);
      $block['html_id'] = 'searchkb';
      $block['inpage_anchor'] = t('Search KnowledgeBase');
      break;

    case 'know4pol_main_search':
      $block['subject'] = '';
      $block['content'] = drupal_render($mainsearchform);
      break;
  }
  return $block;
}
