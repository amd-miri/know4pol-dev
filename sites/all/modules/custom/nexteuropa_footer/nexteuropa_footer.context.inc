<?php
/**
 * @file
 * nexteuropa_footer.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function nexteuropa_footer_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'nexteuropa_footer';
  $context->description = 'Activate this context to show the ec footer';
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
        'menu-menu-nexteuropa-inst-links' => array(
          'module' => 'menu',
          'delta' => 'menu-nexteuropa-inst-links',
          'region' => 'footer_right',
          'weight' => '-10',
        ),
        'menu-menu-nexteuropa-social-media' => array(
          'module' => 'menu',
          'delta' => 'menu-nexteuropa-social-media',
          'region' => 'footer_middle',
          'weight' => '-10',
        ),
        'menu-menu-nexteuropa-site-links' => array(
          'module' => 'menu',
          'delta' => 'menu-nexteuropa-site-links',
          'region' => 'footer_left',
          'weight' => '-10',
        ),
        'menu-menu-nexteuropa-service-links' => array(
          'module' => 'menu',
          'delta' => 'menu-nexteuropa-service-links',
          'region' => 'footer_bottom',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Activate this context to show the ec footer');
  t('digital transformation');
  $export['nexteuropa_footer'] = $context;

  return $export;
}
