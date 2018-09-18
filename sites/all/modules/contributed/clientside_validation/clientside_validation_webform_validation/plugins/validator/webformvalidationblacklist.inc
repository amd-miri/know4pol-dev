<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvWebformValidationBlacklistValidator',
    'constructor argument' => array(
      'js_rule' => 'blacklist',
      'webform_rule' => 'blacklist',
    ),
  ),
);

class CvWebformValidationBlacklistValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $data = explode(',', $rule['data']);
    $element['#cv_data']['rule'] = $rule;
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => $data,
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
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/blacklist.cv.js';
    return $files;
  }
}
