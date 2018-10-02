<?php

$plugin = array(
  'label' => t('Match field'),
  'validator' => array(
    'class' => 'CvFAPIMatchFieldValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_match_field',
      'js_rule' => 'equalTo',
      'js_arg' => NULL,
    ),
  ),
);

class CvFAPIMatchFieldValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('!title value does not match other field.', array('!title' => $element['#title']));
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    $name = is_array($rule['params']) ? $rule['params'][0] : $rule['params'];
    return ':input[name=\'' . $name . '\']';
  }

}
