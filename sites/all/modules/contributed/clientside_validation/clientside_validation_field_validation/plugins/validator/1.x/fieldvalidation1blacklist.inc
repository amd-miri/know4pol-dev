<?php

$plugin = array(
  'label' => t('Blacklist'),
  'validator' => array(
    'class' => 'CvFieldValidation1BlacklistValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'blacklist',
      'js_rule' => 'blacklist',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1BlacklistValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    $arg = parent::getJsArg($element);
    return explode(',', $arg);
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/blacklist.cv.js';
    return $files;
  }

}
