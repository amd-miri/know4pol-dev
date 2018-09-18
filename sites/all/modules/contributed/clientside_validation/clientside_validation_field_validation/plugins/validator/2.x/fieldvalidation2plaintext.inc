<?php

$plugin = array(
  'label' => t('Plain text'),
  'validator' => array(
    'class' => 'CvFieldValidation2PlainTextValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_plain_text_validator',
      'js_rule' => 'plaintext',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2PlainTextValidator extends CvFieldValidationValidator {

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_field_validation') . '/plugins/validator/js/plaintext.cv.js';
    return $files;
  }

  public function getJsArg(array $element) {
    return TRUE;
  }
}
