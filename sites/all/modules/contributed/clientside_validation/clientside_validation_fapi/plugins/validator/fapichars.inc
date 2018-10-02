<?php

$plugin = array(
  'label' => t('Specific characters'),
  'validator' => array(
    'class' => 'CvFAPICharsValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_chars',
      'js_rule' => 'chars',
      'js_arg' => NULL,
    ),
  ),
);

class CvFAPICharsValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Invalid characters on !title value.', array('!title' => $element['#title']));
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return $rule['params'];
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_fapi') . '/plugins/validator/js/chars.cv.js';
    return $files;
  }

}
