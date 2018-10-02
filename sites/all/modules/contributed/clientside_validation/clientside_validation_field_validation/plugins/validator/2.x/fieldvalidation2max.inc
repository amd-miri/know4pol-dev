<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvFieldValidation2MaxValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_numeric2_validator',
      'js_rule' => 'max',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2MaxValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $max = $this->getJsArg($element);
    return $max != '' && is_numeric($max);
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return floatval($rule->settings['max']);
  }

}
