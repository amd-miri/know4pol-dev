<?php

$plugin = array(
  'label' => t('Regular expression'),
  'validator' => array(
    'class' => 'CvFieldValidation2RegexpValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_regex_validator',
      'js_rule' => 'regexMatch',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2RegexpValidator extends CvFieldValidationValidator {

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/regexmatch.cv.js';
    return $files;
  }

}
