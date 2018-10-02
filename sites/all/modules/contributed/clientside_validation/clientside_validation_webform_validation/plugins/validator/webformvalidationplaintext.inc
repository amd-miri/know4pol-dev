<?php

$plugin = array(
  'label' => t('Plain text'),
  'validator' => array(
    'class' => 'CvWebformValidationPlainTextValidator',
    'constructor argument' => array(
      'js_rule' => 'plaintext',
      'webform_rule' => 'plain_text',
    ),
  ),
);

class CvWebformValidationPlainTextValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $element['#cv_data']['rule'] = $rule;
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => array(
            'tags' => '',
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
    return $element['#cv_data']['rule']['negate'] ? t('!title must contain HTML tags.', array('!title' => $element['#title'])) : t('!title only allows the use of plain text.', array('!title' => $element['#title']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/plaintext.cv.js';
    return $files;
  }
}
