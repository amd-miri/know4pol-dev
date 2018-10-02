<?php

$plugin = array(
  'label' => t('IPv4'),
  'validator' => array(
    'class' => 'CvFAPIIPv4Validator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_ipv4',
      'js_rule' => 'ipv4',
      'js_arg' => TRUE,
    ),
  ),
);

class CvFAPIIPv4Validator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Invalid format of !title.', array('!title' => $element['#title']));
  }
}
