<?php

$plugin = array(
  'label' => t('Decimal'),
  'validator' => array(
    'class' => 'CvFAPIDecimalValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_decimal',
      'js_rule' => 'pattern',
      'js_arg' => NULL,
    ),
  ),
);

class CvFAPIDecimalValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Use only decimal on !title.', array('!title' => $element['#title']));
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    if (count($rule['params']) == 2) {
      return '^[0-9]{' . $rule['params'][0] . '}\.[0-9]{' . $rule['params'][1] . '}$';
    }
    return '\d+\.\d+';
  }

}
