<?php

$plugin = array(
  'label' => t('Select maximum'),
  'validator' => array(
    'class' => 'CvFieldValidation2SelectMaxValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_number_of_selections_validator',
      'js_rule' => 'maxlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2SelectMaxValidator extends CvFieldValidationValidator {

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
