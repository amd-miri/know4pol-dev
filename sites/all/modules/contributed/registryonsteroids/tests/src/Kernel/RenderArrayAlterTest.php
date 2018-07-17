<?php

namespace Drupal\Tests\registryonsteroids\Kernel;

use Symfony\Component\Yaml\Yaml;

/**
 * Class RenderArrayAlterTest.
 */
class RenderArrayAlterTest extends AbstractThemeTest {

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();
    module_enable(['registryonsteroids_alter']);
  }

  /**
   * Test the render array extended by the module.
   *
   * @dataProvider renderArrayAlterProvider
   */
  public function testRenderArrayAlter(array $element, array $suggestions_parts, array $expected) {
    _registryonsteroids_alter_extend_theme_property_with_suggestions($element, $suggestions_parts);
    _registryonsteroids_alter_extend_theme_wrappers_property_with_suggestions($element, $suggestions_parts);

    $this->assertEquals($expected, $element);
  }

  /**
   * Return render array fixtures.
   *
   * @return array
   *   List of render array fixtures.
   */
  public function renderArrayAlterProvider() {
    return Yaml::parseFile(__DIR__ . '/../../fixtures/ros/renderarray/elements.yml');
  }

}
