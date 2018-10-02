<?php

$plugin = array(
  'label' => t('Numeric'),
  'validator' => array(
    'class' => 'CvFieldValidation2NumericValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_numeric2_validator',
      'js_rule' => 'number',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2NumericValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    return TRUE;
  }

}
