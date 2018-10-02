<?php

$plugin = array(
  'label' => t('Must be empty'),
  'validator' => array(
    'class' => 'CvFieldValidation1EmptyValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'must_be_empty',
      'js_rule' => 'empty',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1EmptyValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    return TRUE;
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/empty.cv.js';
    return $files;
  }

}
