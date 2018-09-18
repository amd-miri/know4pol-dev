<?php

$plugin = array(
  'label' => t('Specific value'),
  'validator' => array(
    'class' => 'CvWebformValidationSpecificValValidator',
    'constructor argument' => array(
      'js_rule' => 'oneOf',
      'webform_rule' => 'specific_value',
    ),
  ),
);

class CvWebformValidationSpecificValValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $element['#cv_data']['rule'] = $rule;
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => array(
            'values' => explode(',', $rule['data']),
            'negate' => isset($rule['negate']) && $rule['negate'],
            'caseSensitive' => TRUE,
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
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/oneof.cv.js';
    return $files;
  }
}
