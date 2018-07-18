<?php

namespace Drupal\registryonsteroids;

/**
 * Class ThemeRegistryAltererLast.
 */
final class ThemeRegistryAltererLast implements ThemeRegistryAltererInterface {

  /**
   * {@inheritdoc}
   */
  public function alter(array &$registry) {
    foreach ($registry as &$info) {
      if (isset($info['base hook'])) {
        $base_hook = $info['base hook'];
        if (!isset($registry[$base_hook])) {
          // @todo Log this.
          continue;
        }
        $base_hook_info = $registry[$base_hook];
        foreach (FunctionGroupUtil::PHASE_KEYS as $phase_key) {
          $info[$phase_key] = isset($base_hook_info[$phase_key])
            ? $base_hook_info[$phase_key]
            : [];
        }

        unset($info['base hook']);
      }
    }

    foreach ($registry as &$info) {
      if (!isset($info['registryonsteroids replace'])) {
        continue;
      }

      foreach ($info['registryonsteroids replace'] as $phase_key => $replacements) {
        if (empty($info[$phase_key])) {
          continue;
        }
        foreach ($info[$phase_key] as $i => $function) {
          if (isset($replacements[$function])) {
            $info[$phase_key][$i] = $replacements[$function];
          }
        }
      }

      unset($info['registryonsteroids replace']);
    }

    foreach ($registry as &$info) {
      foreach (FunctionGroupUtil::PHASE_KEYS as $phase_key) {
        if (!isset($info[$phase_key])) {
          continue;
        }

        $info[$phase_key] = preg_grep('/^@/', $info[$phase_key], PREG_GREP_INVERT);
      }
    }

    unset($registry['*']);
  }

}
