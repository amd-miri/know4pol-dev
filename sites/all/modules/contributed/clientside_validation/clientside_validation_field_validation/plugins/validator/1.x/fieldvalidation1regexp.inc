<?php

$plugin = array(
  'label' => t('Regular expression'),
  'validator' => array(
    'class' => 'CvFieldValidation1RegexpValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'regex',
      'js_rule' => 'regexMatch',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1RegexpValidator extends CvFieldValidationValidator {

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/regexmatch.cv.js';
    return $files;
  }

}
