<?php

namespace Drupal\registryonsteroids;

/**
 * Utility class to find and group _process_ and _preprocess_ functions.
 */
final class FunctionGroupUtil {

  /**
   * Phases for process/preprocess functions.
   *
   * @var string[]
   *   Format: $[$phase_key] = $phase
   */
  const PHASES = [
    'preprocess functions' => 'preprocess',
    'process functions' => 'process',
  ];

  /**
   * Array keys of the above.
   *
   * These are also the keys used in theme registry entries.
   *
   * @var string[]
   *   Format: $[] = $phase_key
   */
  const PHASE_KEYS = [
    'preprocess functions',
    'process functions',
  ];

  /**
   * Group functions by hook, phase and weight.
   *
   * @param string[] $user_functions
   * @param string[] $prefixes
   *   A whitelist of prefixes (module names, themes, etc).
   *
   * @return string[][][]
   *   Format: $[$hook][$phase_key][$weight] = $function
   *   E.g. $['block']['preprocess'][51] = 'system_preprocess_block'.
   */
  public static function groupFunctionsByHookAndPhasekeyAndWeight(array $user_functions, array $prefixes) {
    $functions_by_prefix_and_phasekey_filtered = self::groupFunctionsByPrefixAndPhasekeyFiltered(
      $user_functions,
      $prefixes);

    $functions_by_hook_and_phasekey_and_weight = [];
    $weight = 0;
    foreach ($functions_by_prefix_and_phasekey_filtered as $functions_by_phasekey) {
      foreach ($functions_by_phasekey as $phase_key => $functions_by_hook) {
        foreach ($functions_by_hook as $hook => $function) {
          $functions_by_hook_and_phasekey_and_weight[$hook][$phase_key][$weight] = $function;
        }
      }
      ++$weight;
    }

    ksort($functions_by_hook_and_phasekey_and_weight);

    return $functions_by_hook_and_phasekey_and_weight;
  }

  /**
   * Group functions by prefix and phase, but filtered.
   *
   * @param string[] $user_functions
   * @param string[] $prefixes
   *   A whitelist of prefixes (module names, themes, etc).
   *
   * @return string[][][]
   *   Format: $[$prefix][$phase_key][$themehook] = $function
   *   E.g. $['system']['preprocess']['block'] = 'system_preprocess_block'.
   */
  public static function groupFunctionsByPrefixAndPhasekeyFiltered(array $user_functions, array $prefixes) {
    $functions_by_prefix_and_phasekey = self::groupFunctionsByPrefixAndPhasekey(
      $user_functions);

    // Only keep functions with known prefix.
    $functions_by_prefix_and_phasekey_filtered = [];
    foreach ($prefixes as $prefix) {
      if (!isset($functions_by_prefix_and_phasekey[$prefix])) {
        continue;
      }
      $functions_by_prefix_and_phasekey_filtered[$prefix] = $functions_by_prefix_and_phasekey[$prefix];
    }

    return $functions_by_prefix_and_phasekey_filtered;
  }

  /**
   * Group functions by prefix and phase.
   *
   * @param string[] $user_functions
   *
   * @return string[][][]
   *   Format: $[$prefix][$phase_key][$themehook] = $function
   *   E.g. $['system']['preprocess']['block'] = 'system_preprocess_block'.
   */
  public static function groupFunctionsByPrefixAndPhasekey(array $user_functions) {
    $candidate_functions = preg_grep('/process/', $user_functions);

    $functions_by_prefix_and_phasekey = [];
    foreach (self::PHASES as $phase_key => $phase) {
      $needle = '_' . $phase . '_';

      $phase_functions = preg_grep('/_' . $phase . '_/', $candidate_functions);
      foreach ($phase_functions as $function) {
        $fragments = explode($needle, $function);
        if (!isset($fragments[1])) {
          // This should be unreachable code with the preg_grep() above.
          continue;
        }

        if (!isset($fragments[2])) {
          // This is the normal case with only one occurence of $needle.
          list($prefix, $hook) = $fragments;
          $functions_by_prefix_and_phasekey[$prefix][$phase_key][$hook] = $function;
          continue;
        }

        // This is a rare case with more than one occurence of $needle.
        // This doesn't have to be very fast, because it is rare.
        $prefix = array_shift($fragments);
        while ([] !== $fragments) {
          $hook = implode($needle, $fragments);
          $functions_by_prefix_and_phasekey[$prefix][$phase_key][$hook] = $function;
          $prefix .= $needle . array_shift($fragments);
        }
      }

      $phase_functions = preg_grep('/_' . $phase . '$/', $candidate_functions);
      $substr_length = -drupal_strlen($phase) - 1;
      foreach ($phase_functions as $function) {
        $prefix = drupal_substr($function, 0, $substr_length);
        $functions_by_prefix_and_phasekey[$prefix][$phase_key]['*'] = $function;
      }
    }

    return $functions_by_prefix_and_phasekey;
  }

}
