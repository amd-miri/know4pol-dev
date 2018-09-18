<?php

$plugin = array(
  'label' => t('Empty'),
  'validator' => array(
    'class' => 'CvWebformValidationEmptyValidator',
    'constructor argument' => array(
      'js_rule' => 'empty',
      'webform_rule' => 'must_be_empty',
    ),
  ),
);

class CvWebformValidationEmptyValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => TRUE,
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
    return t('!title does not contain the correct data.', array('!title' => $element['#title']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/empty.cv.js';
    return $files;
  }
}
