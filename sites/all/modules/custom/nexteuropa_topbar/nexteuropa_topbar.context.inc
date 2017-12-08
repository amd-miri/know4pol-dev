<?php
/**
 * @file
 * Nexteuropa_topbar.context.inc.
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_topbar_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'ec_europa_topbar';
  $context->description = 'Activate this context to show the ec topbar';
  $context->tag = 'digital transformation';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-nexteuropa-site-links' => array(
          'module' => 'menu',
          'delta' => 'menu-nexteuropa-site-links',
          'region' => 'header_top',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Activate this context to show the ec topbar');
  t('digital transformation');
  $export['ec_europa_topbar'] = $context;

  return $export;
}
