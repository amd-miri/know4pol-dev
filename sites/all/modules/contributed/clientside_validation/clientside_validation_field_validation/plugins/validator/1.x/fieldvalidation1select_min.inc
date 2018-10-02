<?php

$plugin = array(
  'label' => t('Select minimum'),
  'validator' => array(
    'class' => 'CvFieldValidation1SelectMinValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'select_min',
      'js_rule' => 'minlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1SelectMinValidator extends CvFieldValidationValidator {
}
