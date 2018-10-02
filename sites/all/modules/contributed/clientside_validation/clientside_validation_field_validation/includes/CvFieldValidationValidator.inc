<?php

abstract class CvFieldValidationValidator extends ClientsideValidationValidator {
  protected $field_validation_rule;
  protected $js_rule;
  protected $js_arg;

  public function __construct($args) {
    parent::__construct();
    $this->field_validation_rule = $args['field_validation_rule'];
    $this->js_rule = $args['js_rule'];
    $this->js_arg = $args['js_arg'];
  }

  public function supports(array $element, array &$form_state) {
    $supports = (
      parent::supports($element, $form_state)
      && isset($element['#entity_type'])
      && isset($element['#bundle'])
      && isset($element['#field_name'])
      && field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle'])
    );
    if (!$supports) {
      return FALSE;
    }
    $rule = $this->getRule($element);
    if (!$rule) {
      return FALSE;
    }
    $parent_last = end($element['#parents']);
    if (($parent_last !== FALSE) && ($parent_last !== $rule->col) && $element['#type'] != 'select') {
      return FALSE;
    }
    return TRUE;
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $arg = $this->getJsArg($element);
    return array(
      'rules' => array(
        $name => array(
          $this->js_rule => is_numeric($arg) ? floatval($arg) : $arg,
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return isset($rule->data) ? $rule->data : $rule->settings['data'];
  }

  public function getRule($element) {
    $rules = array();
    if (function_exists('field_validation_get_field_rules')) {
      $rules = field_validation_get_field_rules(field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']));
    }
    else {
      ctools_include('export');
      $rules = ctools_export_load_object(
        'field_validation_rule',
        'conditions',
        array(
          'entity_type' => $element['#entity_type'],
          'bundle' => $element['#bundle'],
          'field_name' => $element['#field_name'],
        )
      );
    }
    foreach ($rules as $rule) {
      if (isset($rule->disabled) && !empty($rule->disabled)) {
        continue;
      }
      if ($rule->validator == $this->field_validation_rule) {
        return $rule;
      }
    }
    return FALSE;
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/clientside_validation_field_validation.js';
    return $files;
  }

  /**
   * Retrieves the message from the rule config.
   */
  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    $error_message = t($rule->error_message);
    $settings = $rule->settings;
    $tokens = array(
      '[entity-type]' => $rule->entity_type,
      '[bundle]' => $rule->bundle,
    );
    if (isset($settings['min']) && $settings['min'] != '') {
      $tokens['[min]'] = $settings['min'];
    }
    if (isset($settings['max']) && $settings['max'] != '') {
      $tokens['[max]'] = $settings['max'];
    }
    return field_filter_xss(strtr($error_message, $tokens));
  }

}
