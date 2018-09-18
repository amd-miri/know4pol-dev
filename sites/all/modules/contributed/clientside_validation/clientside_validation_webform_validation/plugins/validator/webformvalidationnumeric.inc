<?php

$plugin = array(
  'label' => t('Numeric'),
  'validator' => array(
    'class' => 'CvWebformValidationNumericValidator',
    'constructor argument' => array(
      'js_rule' => 'number',
      'webform_rule' => 'numeric',
    ),
  ),
);

class CvWebformValidationNumericValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
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
    return t('!title is not numeric.', array('!title' => $element['#title']));
  }
}