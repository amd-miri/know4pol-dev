<?php

$plugin = array(
  'label' => t('Must be empty'),
  'validator' => array(
    'class' => 'CvFieldValidation2EmptyValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_must_be_empty_validator',
      'js_rule' => 'empty',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2EmptyValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    return TRUE;
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/empty.cv.js';
    return $files;
  }

}
