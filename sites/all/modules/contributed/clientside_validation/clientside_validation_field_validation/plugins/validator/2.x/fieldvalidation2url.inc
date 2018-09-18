<?php

$plugin = array(
  'label' => t('URL'),
  'validator' => array(
    'class' => 'CvFieldValidation2URLValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_url_validator',
      'js_rule' => 'drupalURL',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2URLValidator extends CvFieldValidationValidator {

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    if ($rule->settings['external']) {
      return array('absolute' => TRUE);
    }
    return TRUE;
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/drupalurl.cv.js';
    return $files;
  }

}
