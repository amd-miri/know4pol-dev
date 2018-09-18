<?php

$plugin = array(
  'label' => t('Maximum length'),
  'validator' => array(
    'class' => 'CvFieldValidation2MaxLengthValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_length_validator',
      'js_rule' => 'maxlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2MaxLengthValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $max = $this->getJsArg($element);
    return $max != '' && is_numeric($max);
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return $rule->settings['max'];
  }

}
