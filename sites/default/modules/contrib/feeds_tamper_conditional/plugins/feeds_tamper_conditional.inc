<?php
/**
 * @file
 * A Feeds Tamper plugin that allows appending to multivalue fields rather than overwriting them.
 * Only works with type 'update' not 'replace' in the Node Processor settings.
 */

$plugin = array(
  'form' => 'feeds_tamper_conditional_form',
  'callback' => 'feeds_tamper_conditional_callback',
  'name' => 'Conditional',
  'multi' => 'skip',
  'category' => 'Other',
);

/**
 * Form for plugin.
 */
function feeds_tamper_conditional_form($importer, $element_key, $settings) {
  $form = array();

  $form['help'] = array(
    '#markup' => t('Only writes the field if a condition is met.  Condition can be based on the value
      of any field.'),
  );

  // @todo add a hook here to allow modules to add their own format for the options in the dropdown.
  $feeds_filemaker = (get_class($importer->parser) == 'FeedsFileMakerParser')
    ? TRUE
    : FALSE;

  // Grab all of the mapping sources, for addition to the conditional field select.
  $replace = array();
  $mappings = $importer->processor->config['mappings'];

  foreach ($mappings as $mapping) {
    if($feeds_filemaker) {
      $prefix = $importer->config['parser']['config']['mappings'][$mapping['source']]['mapping'] . ' - ';
    }
    else {
      $prefix = '';
    }

    $replace[$mapping['source']] = $prefix . $mapping['target'] . ' [' . $mapping['source'] . ']';
  }

  // The field mapping to check.  The user chooses which field should be tested
  // against the condition.
  $form['conditional_field'] = array(
    '#type' => 'select',
    '#title' => t('Field mapping to check'),
    '#options' => $replace,
    '#required' => TRUE,
    '#default_value' => isset($settings['conditional_field'])
      ? $settings['conditional_field']
      : '',
  );

  // The operators that can be used to check whether the condition has been met
  $operators = array(
    'equals' => 'Equals',
    'not_equals' => 'Does not equal',
    'begins' => 'Begins with',
    'ends' => 'Ends with',
    'greater' => 'Greater than',
    'greater_equal' => 'Greater than or equal',
    'less' => 'Less than',
    'less_equal' => 'Less than or equal',
    'contains' => 'Contains',
    'not_contains' => 'Does not contain',
    'empty' => 'Is empty',
    'set' => 'Is set',
    'null' => 'Is null',
    'array' => 'Is array',
    'bool' => 'Is boolean',
    'int' => 'Is integer',
    'float' => 'Is float',
    'numeric' => 'Is numeric',
    'string' => 'Is string',
  );

  // The operator to use for validating the condition.
  $form['operator'] = array(
    '#type' => 'select',
    '#title' => t('Operator'),
    '#options' => $operators,
    '#default_value' => isset($settings['operator'])
      ? $settings['operator']
      : '',
    '#required' => TRUE,
  );

  // Option to Negate is applicable to conditions such as isset(), empty() etc.
  $form['negate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Negate'),
    '#default_value' => isset($settings['negate'])
      ? $settings['negate']
      : 0,
    '#states' => array(
      'visible' => array(   // action to take.
        'select[name="settings[operator]"]' => array(
          array('value' => 'begins'),
          array('value' => 'ends'),
          array('value' => 'empty'),
          array('value' => 'set'),
          array('value' => 'null'),
          array('value' => 'array'),
          array('value' => 'bool'),
          array('value' => 'int'),
          array('value' => 'float'),
          array('value' => 'numeric'),
          array('value' => 'string'),
        ),
      ),
    ),
  );

  // The value to check for
  $form['value'] = array(
    '#title' => t('Value to check'),
    '#default_value' => isset($settings['value'])
      ? $settings['value']
      : '',
    '#type' => 'textfield',
    '#required' => FALSE,
    '#states' => array(
      'invisible' => array(   // action to take.
        'select[name="settings[operator]"]' => array(
          array('value' => 'empty'),
          array('value' => 'set'),
          array('value' => 'null'),
          array('value' => 'array'),
          array('value' => 'bool'),
          array('value' => 'int'),
          array('value' => 'float'),
          array('value' => 'numeric'),
          array('value' => 'string'),
        ),
      ),
    ),
  );

  return $form;
}

/**
 * Callback for plugin.
 */
function feeds_tamper_conditional_callback(&$result, $item_key, $element_key, &$field, $settings, $source) {
  $condition_met = FALSE;

  // The value of the field that should be checked for the condition.
  $conditional_field_value = $result->items[$item_key][$settings['conditional_field']];

  switch($settings['operator']) {
    case 'equals': {
      $condition_met = ($conditional_field_value == $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'begins': {
      if(!isset($settings['negate']) || $settings['negate'] == 0) {
        $condition_met = feeds_tamper_conditional_begins_with($conditional_field_value, $settings['value']);
      }
      else {
        $condition_met = !feeds_tamper_conditional_begins_with($conditional_field_value, $settings['value']);
      }
    }
    break;
    case 'ends': {
      if(!isset($settings['negate']) || $settings['negate'] == 0) {
        $condition_met = feeds_tamper_conditional_ends_with($conditional_field_value, $settings['value']);
      }
      else {
        $condition_met = !feeds_tamper_conditional_ends_with($conditional_field_value, $settings['value']);
      }
    }
    break;
    case 'not_equals': {
      $condition_met = ($conditional_field_value != $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'greater': {
      $condition_met = ($conditional_field_value > $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'greater_equal': {
      $condition_met = ($conditional_field_value >= $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'less': {
      $condition_met = ($conditional_field_value < $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'less_equal': {
      $condition_met = ($conditional_field_value <= $settings['value']) ? TRUE : FALSE;
    }
    break;
    case 'contains': {
      $condition_met = is_int(stripos($conditional_field_value, $settings['value'])) ? TRUE : FALSE;
    }
    break;
    case 'not_contains': {
      $condition_met = is_int(stripos($conditional_field_value, $settings['value'])) ? FALSE : TRUE;
    }
    break;
    case 'empty': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? empty($conditional_field_value) : !empty($conditional_field_value));
    }
    break;
    case 'set': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? isset($conditional_field_value) : !isset($conditional_field_value));
    }
    break;
    case 'null': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_null($conditional_field_value) : !is_null($conditional_field_value));
    }
    break;
    case 'array': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_array($conditional_field_value) : !is_array($conditional_field_value));
    }
    break;
    case 'bool': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_bool($conditional_field_value) : !is_bool($conditional_field_value));
    }
    break;
    case 'int': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_int($conditional_field_value) : !is_int($conditional_field_value));
    }
    break;
    case 'float': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_float($conditional_field_value) : !is_float($conditional_field_value));
    }
    break;
    case 'numeric': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_numeric($conditional_field_value) : !is_numeric($conditional_field_value));
    }
    break;
    case 'string': {
      $condition_met = ((!isset($settings['negate']) || $settings['negate'] == 0) ? is_string($conditional_field_value) : !is_string($conditional_field_value));
    }
    break;
  }

  if(!$condition_met) {
    unset($result->items[$item_key][$element_key]);
  }
}

function feeds_tamper_conditional_begins_with($haystack, $needle) {
  // Enforce case insensitive check.
  $haystack = strtolower($haystack);
  $needle = strtolower($needle);

  return (substr($haystack, 0, strlen($needle)) === $needle);
}

function feeds_tamper_conditional_ends_with($haystack, $needle) {
  // Enforce case insensitive check.
  $haystack = strtolower($haystack);
  $needle = strtolower($needle);

  return substr($haystack, -strlen($needle)) === $needle;
}
