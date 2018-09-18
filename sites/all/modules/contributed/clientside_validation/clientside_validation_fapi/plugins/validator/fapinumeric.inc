<?php

$plugin = array(
  'label' => t('Numeric'),
  'validator' => array(
    'class' => 'CvFAPINumericValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_numeric',
      'js_rule' => 'number',
      'js_arg' => TRUE,
    ),
  ),
);

class CvFAPINumericValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Use only numbers at !title.', array('!title' => $element['#title']));
  }

}
