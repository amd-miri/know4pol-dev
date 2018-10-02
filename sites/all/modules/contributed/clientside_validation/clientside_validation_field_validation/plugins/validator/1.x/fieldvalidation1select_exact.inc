<?php

$plugin = array(
  'label' => t('Select exact'),
  'validator' => array(
    'class' => 'CvFieldValidation1SelectExactValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'select_exact',
      'js_rule' => 'exactlength',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1SelectExactValidator extends CvFieldValidationValidator {

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/exactlength.cv.js';
    return $files;
  }

}
