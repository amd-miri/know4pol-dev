<?php

namespace Drupal\Tests\registryonsteroids\Kernel;

use Symfony\Component\Yaml\Yaml;

/**
 * Class RegistryDefinitionsTest.
 */
class RegistryDefinitionsTest extends AbstractThemeTest {

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
    module_enable(['registryonsteroids']);
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
   * Test the registry after the first part.
   *
   * @param string $hook
   * @param array $expected_intermediate_entry
   *
   * @dataProvider intermediateRegistryProvider
   */
  public function testIntermediateEntry($hook, array $expected_intermediate_entry) {
    $intermediate_registry = variable_get('ros_test_intermediate_theme_registry');

    if (NULL === $intermediate_registry) {
      if (PHP_VERSION_ID < 70000) {
        $this->markTestSkipped('Intermediate theme registry was not written, which seems normal on PHP 5.*. Skipping this test, as it is not required.');
      }
      $this->fail('Intermediate theme registry was not written');
    }
    $this->assertArrayHasKey($hook, $intermediate_registry);
    $this->assertEqualThemeRegistryEntries($expected_intermediate_entry, $intermediate_registry[$hook]);
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
    return Yaml::parseFile(__DIR__ . '/../../fixtures/ros/registry/registry.yml');
  }

  /**
   * Return registry fixtures.
   *
   * @return array
   *   List of registry fixtures.
   */
  public function intermediateRegistryProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/ros/registry/intermediate.yml');
  }

  /**
   * Return render fixtures.
   *
   * @return array
   *   List of registry fixtures.
   */
  public function renderProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/ros/render/render.yml');
  }

}
