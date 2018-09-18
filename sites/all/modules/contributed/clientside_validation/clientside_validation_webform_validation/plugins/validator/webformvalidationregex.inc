<?php

$plugin = array(
  'label' => t('Regular expression'),
  'validator' => array(
    'class' => 'CvWebformValidationRegexValidator',
    'constructor argument' => array(
      'js_rule' => 'regexMatch',
      'webform_rule' => 'regex',
    ),
  ),
);

class CvWebformValidationRegexValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $element['#cv_data']['rule'] = $rule;
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => array(
            'regex' => $rule['data'],
            'negate' => $rule['negate'],
          ),
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    $rule = $element['#cv_data']['rule'];
    return $rule['error_message'];
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/regexmatch.cv.js';
    return $files;
  }
}