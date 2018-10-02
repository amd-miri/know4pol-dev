<?php

$plugin = array(
  'label' => t('Minimum length'),
  'validator' => array(
    'class' => 'CvFieldValidation2MinLengthValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_length_validator',
      'js_rule' => 'minlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2MinLengthValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $min = $this->getJsArg($element);
    return $min != '' && is_numeric($min);
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return $rule->settings['min'];
  }

}
