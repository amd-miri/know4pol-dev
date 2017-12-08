<?php
/**
 * @file
 * Nexteuropa_site_header.context.inc.
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_site_header_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'ec_europa_site_header';
  $context->description = 'Activate this context to show the ec site header';
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
        'language_selector_site-language_selector_site' => array(
          'module' => 'language_selector_site',
          'delta' => 'language_selector_site',
          'region' => 'header',
          'weight' => '-10',
        ),
        'nexteuropa_europa_search-nexteuropa_europa_search_form' => array(
          'module' => 'nexteuropa_europa_search',
          'delta' => 'nexteuropa_europa_search_form',
          'region' => 'header',
          'weight' => '-9',
        ),
        'easy_breadcrumb-easy_breadcrumb' => array(
          'module' => 'easy_breadcrumb',
          'delta' => 'easy_breadcrumb',
          'region' => 'header_bottom',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Activate this context to show the ec site header');
  t('digital transformation');

  $export['ec_europa_site_header'] = $context;

  return $export;
}
