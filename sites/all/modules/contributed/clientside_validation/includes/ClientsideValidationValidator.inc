<?php

abstract class ClientsideValidationValidator {
  public function __construct() {
  }
  public function supports(array $element, array &$form_state) {
    $name = $this->getName($element);
    return !empty($name) && isset($element['#title']);
  }
  abstract public function getJavascriptSettings(array &$element, array &$form_state);

  public function getName(array $element) {
    if (!isset($element['#name'])) {
      return '';
    }
    return  (isset($element['#multiple']) && $element['#multiple']) ? $element['#name'] . '[]' : $element['#name'];
  }
  public function jsFiles(array &$element) {
    return array();
  }

  abstract public function getMessage(array $element);

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    $name = $this->getName($element);
    foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
      $element['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
      $element['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
    }
  }
}

