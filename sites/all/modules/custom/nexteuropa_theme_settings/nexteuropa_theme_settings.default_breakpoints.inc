<?php
/**
 * @file
 * nexteuropa_theme_settings.default_breakpoints.inc
 */

/**
 * Implements hook_default_breakpoints().
 */
function nexteuropa_theme_settings_default_breakpoints() {
  $export = array();

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.europa.medium';
  $breakpoint->name = 'medium';
  $breakpoint->breakpoint = '(min-width: 480px) and (max-width: 767px)';
  $breakpoint->source = 'europa';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 3;
  $breakpoint->multipliers = array(
    '2x' => '2x',
    '1x' => '1x',
  );
  $export['breakpoints.theme.europa.medium'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.europa.mobile';
  $breakpoint->name = 'mobile';
  $breakpoint->breakpoint = '(min-width: 0px) and (max-width: 319px)';
  $breakpoint->source = 'europa';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 1;
  $breakpoint->multipliers = array(
    '2x' => '2x',
    '1x' => '1x',
  );
  $export['breakpoints.theme.europa.mobile'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.europa.narrow';
  $breakpoint->name = 'narrow';
  $breakpoint->breakpoint = '(min-width: 320px) and (max-width: 479px)';
  $breakpoint->source = 'europa';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 2;
  $breakpoint->multipliers = array(
    '2x' => '2x',
    '1x' => '1x',
  );
  $export['breakpoints.theme.europa.narrow'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.europa.normal';
  $breakpoint->name = 'normal';
  $breakpoint->breakpoint = '(min-width: 768px) and (max-width: 991px)';
  $breakpoint->source = 'europa';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 4;
  $breakpoint->multipliers = array(
    '2x' => '2x',
    '1x' => '1x',
  );
  $export['breakpoints.theme.europa.normal'] = $breakpoint;

  $breakpoint = new stdClass();
  $breakpoint->disabled = FALSE; /* Edit this to true to make a default breakpoint disabled initially */
  $breakpoint->api_version = 1;
  $breakpoint->machine_name = 'breakpoints.theme.europa.wide';
  $breakpoint->name = 'wide';
  $breakpoint->breakpoint = 'only screen and (min-width: 992px)';
  $breakpoint->source = 'europa';
  $breakpoint->source_type = 'theme';
  $breakpoint->status = 1;
  $breakpoint->weight = 5;
  $breakpoint->multipliers = array(
    '2x' => '2x',
    '1x' => '1x',
  );
  $export['breakpoints.theme.europa.wide'] = $breakpoint;

  return $export;
}
