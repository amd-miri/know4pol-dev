<?php

$plugin = array(
  'label' => t('Maximum length'),
  'validator' => array(
    'class' => 'CvFAPIMaxlengthValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_length',
      'js_rule' => 'maxlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFAPIMaxlengthValidator extends CvFAPIValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $rule = $this->getRule($element);
    return count($rule['params']) > 1;
  }

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Invalid size of !title value.', array('!title' => $element['#title']));
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return is_array($rule['params']) ? $rule['params'][1] : $rule['params'];
  }

}
