<?php

namespace Drupal\Tests\registryonsteroids\Kernel;

use Symfony\Component\Yaml\Yaml;

/**
 * Class CoreRegistryDefinitionsTest.
 */
class CoreRegistryDefinitionsTest extends AbstractThemeTest {

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
    module_disable(['registryonsteroids']);
  }

  /**
   * Test the registry definition validity.
   *
   * @dataProvider registryProvider
   */
  public function testRegistryDefinitions($hook, $definition) {
    $registry = theme_get_registry(TRUE);

    $this->assertArrayHasKey($hook, $registry);
    $this->assertEqualThemeRegistryEntries($definition, $registry[$hook]);
  }

  /**
   * Test the registry definition against the missing definitions.
   *
   * @dataProvider registryMissingProvider
   */
  public function testMissingRegistryDefinitions($hook) {
    $registry = theme_get_registry(TRUE);
    $this->assertArrayNotHasKey($hook, $registry);
  }

  /**
   * Test the render of a theme hook.
   *
   * @dataProvider renderProvider
   */
  public function testPreprocessProcessCascade($hook, $render) {
    $this->assertEquals(
      "\n" . implode("\n", $render) . "\n",
      "\n" . theme($hook) . "\n");
  }

  /**
   * Return registry fixtures.
   *
   * @return array
   *   List of registry fixtures.
   */
  public function registryProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/core/registry/registry.yml');
  }

  /**
   * Return registry fixtures that should exist in core but doesn't.
   *
   * @return array
   *   List of registry fixtures.
   */
  public function registryMissingProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/core/registry/registry_missing.yml');
  }

  /**
   * Return render fixtures.
   *
   * @return array
   *   List of registry fixtures.
   */
  public function renderProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/core/render/render.yml');
  }

}
