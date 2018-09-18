<?php

$plugin = array(
  'label' => t('Numeric'),
  'validator' => array(
    'class' => 'CvFieldValidation1NumericValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'numeric',
      'js_rule' => 'number',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1NumericValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    return TRUE;
  }

}
