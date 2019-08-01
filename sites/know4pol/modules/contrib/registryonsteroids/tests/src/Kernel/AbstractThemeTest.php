<?php

namespace Drupal\Tests\registryonsteroids\Kernel;

use Drupal\Tests\registryonsteroids\AbstractTest;

/**
 * Class AbstractThemeTest.
 */
abstract class AbstractThemeTest extends AbstractTest {

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    global $conf;

    theme_enable(['ros_theme']);
    $conf['theme_debug'] = FALSE;
    $conf['theme_default'] = 'ros_theme';

    module_enable(['ros_test']);
  }

  /**
   * Asserts that two theme registry entries are effectively equal.
   *
   * @param array $expected
   * @param array $actual
   */
  public function assertEqualThemeRegistryEntries(array $expected, array $actual) {
    $this->assertEquals(
      self::exportRegistryEntryNormalized($expected),
      self::exportRegistryEntryNormalized($actual));
  }

  /**
   * Exports a theme registry entry as a PHP statement.
   *
   * @param array $definition
   *
   * @return string
   */
  private static function exportRegistryEntryNormalized(array $definition) {
    foreach (['preprocess functions', 'process functions'] as $phase_key) {
      if (empty($definition[$phase_key])) {
        unset($definition[$phase_key]);
      }
      else {
        $definition[$phase_key] = array_values($definition[$phase_key]);
      }
    }

    ksort($definition);

    return self::exportArray($definition);
  }

  /**
   * Exports a mixed value as a PHP statement.
   *
   * Only supports what is also supported in var_export().
   * Array keys are omitted, if they are a regular integer sequence 0..n.
   *
   * @param mixed $value
   * @param string $indent
   *
   * @return string
   */
  private static function exportValue($value, $indent = '') {
    return \is_array($value)
      ? self::exportArray($value, $indent)
      : var_export($value, TRUE);
  }

  /**
   * Exports an array as a PHP statement.
   *
   * Only supports what is also supported in var_export().
   * Array keys are omitted, if they are a regular integer sequence 0..n.
   *
   * @param array $array
   * @param string $indent
   *
   * @return string
   */
  private static function exportArray(array $array, $indent = '') {
    $indent2 = $indent . '    ';

    $php = '';
    if (array_values($array) === $array) {
      // This array has regular "serial" keys.
      foreach ($array as $v) {
        $php .= "\n" . $indent2
          . self::exportValue($v, $indent2)
          . ',';
      }
    }
    else {
      foreach ($array as $k => $v) {
        $php .= "\n" . $indent2
          . var_export($k, TRUE)
          . ' => '
          . self::exportValue($v, $indent2)
          . ',';
      }
    }

    return '[' . $php . "\n" . $indent . ']';
  }

}
