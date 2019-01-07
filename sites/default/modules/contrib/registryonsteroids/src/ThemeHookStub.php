<?php

namespace Drupal\registryonsteroids;

/**
 * Contains data to build a modified theme registry entry.
 */
final class ThemeHookStub {

  /**
   * The base hook.
   *
   * @var string
   */
  private $baseHook;

  /**
   * The base hook stub.
   *
   * @var self
   */
  private $baseHookStub;

  /**
   * The info related to a theme hook.
   *
   * @var array
   */
  private $info;

  /**
   * Placeholders indexed by phase and weight.
   *
   * @var string[][]
   *   Format: $[$phase_key][$weight][] = $placeholder_or_function
   */
  private $placeholderssByPhasekeyAndWeight = [];

  /**
   * Replacements indexed by phase.
   *
   * @var string[][]
   *   Format: $[$phase_key]['@' . $function] = $function
   */
  private $replacementssByPhasekey = [];

  /**
   * Constructs a stub without parents ("root").
   *
   * @param string $hook
   * @param array $info
   * @param string[][] $functionsByPhasekeyAndWeight
   *   Format: $[$phase_key][$weight] = $function
   * @param string[][] $templateFunctionsByPhasekeyAndWeight
   *   Format: $[$phase_key][$weight] = $function
   *   Should be empty if this is not a template.
   */
  public function __construct($hook, array $info, array $functionsByPhasekeyAndWeight, array $templateFunctionsByPhasekeyAndWeight) {
    $this->baseHook = $hook;
    $this->baseHookStub = $this;
    // Remove original process/preprocess functions.
    // They will be replaced later.
    unset($info['process functions'], $info['preprocess functions']);
    $this->info = $info;
    foreach ($templateFunctionsByPhasekeyAndWeight as $phase_key => $functionsByWeight) {
      foreach ($functionsByWeight as $weight => $function) {
        $this->placeholderssByPhasekeyAndWeight[$phase_key][$weight][] = $function;
      }
    }

    foreach ($functionsByPhasekeyAndWeight as $phase_key => $functionsByWeight) {
      foreach ($functionsByWeight as $weight => $function) {
        $this->placeholderssByPhasekeyAndWeight[$phase_key][$weight][] = $function;
      }
    }
  }

  /**
   * Add variant to a specific hook.
   *
   * @param string $hook
   * @param array|null $info
   * @param array $functionsByPhasekeyAndWeight
   *
   * @return static
   */
  public function addVariant($hook, array $info = NULL, array $functionsByPhasekeyAndWeight) {
    $variant = clone $this;

    foreach ($functionsByPhasekeyAndWeight as $phase_key => $functionsByWeight) {
      foreach ($functionsByWeight as $weight => $function) {
        $this->baseHookStub->placeholderssByPhasekeyAndWeight[$phase_key][$weight][] = '@' . $function;
        $variant->replacementssByPhasekey[$phase_key]['@' . $function] = $function;
      }
    }

    if (NULL !== $info) {
      // Remove original process/preprocess functions.
      // They will be replaced later.
      unset($info['process functions'], $info['preprocess functions']);
      $variant->info = $info;
    }

    $variant->info['base hook'] = $this->baseHook;
    $variant->placeholderssByPhasekeyAndWeight = [];

    return $variant;
  }

  /**
   * Get a registry entry.
   *
   * @return array
   */
  public function getRegistryEntry() {
    $info = $this->info;

    foreach ($this->getPlaceholdersByPhasekeySorted() as $phase_key => $placeholders_sorted) {
      $info[$phase_key] = $placeholders_sorted;
    }

    if ([] !== $this->replacementssByPhasekey) {
      $info['registryonsteroids replace'] = $this->replacementssByPhasekey;
    }

    return $info;
  }

  /**
   * Placeholders indexed by phase and sorted.
   *
   * @return string[][][]
   *   Format: $[$phase_key][] = $function_or_placeholder
   */
  private function getPlaceholdersByPhasekeySorted() {
    $placeholders_by_phasekey = [];

    foreach ($this->placeholderssByPhasekeyAndWeight as $phase_key => $placeholderss_by_weight) {
      ksort($placeholderss_by_weight);
      $placeholders_by_phasekey[$phase_key] = [] !== $placeholderss_by_weight
        ? array_merge(...$placeholderss_by_weight)
        : [];
    }

    return $placeholders_by_phasekey;
  }

}
