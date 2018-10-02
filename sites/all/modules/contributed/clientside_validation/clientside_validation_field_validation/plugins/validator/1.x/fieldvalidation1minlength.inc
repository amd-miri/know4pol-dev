<?php

$plugin = array(
  'label' => t('Minimum length'),
  'validator' => array(
    'class' => 'CvFieldValidation1MinLengthValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'min_length',
      'js_rule' => 'minlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1MinLengthValidator extends CvFieldValidationValidator {
}
