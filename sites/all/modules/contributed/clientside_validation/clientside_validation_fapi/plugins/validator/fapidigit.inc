<?php

$plugin = array(
  'label' => t('Digit'),
  'validator' => array(
    'class' => 'CvFAPIDigitValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_digit',
      'js_rule' => 'digits',
      'js_arg' => TRUE,
    ),
  ),
);

class CvFAPIDigitValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Use only digits on !title.', array('!title' => $element['#title']));
  }
}
