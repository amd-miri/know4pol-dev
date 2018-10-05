<?php

namespace Drupal\registryonsteroids;

/**
 * Interface ThemeRegistryAltererInterface.
 */
interface ThemeRegistryAltererInterface {

  /**
   * Alter the Drupal's registry.
   *
   * @param array $registry
   */
  public function alter(array &$registry);

}
