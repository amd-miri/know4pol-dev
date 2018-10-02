<?php

$plugin = array(
  'label' => t('Integer'),
  'validator' => array(
    'class' => 'CvCoreIntegerValidator',
  ),
  'weight' => -99,
);


class CvCoreIntegerValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'textfield'
      && isset($element['#number_type'])
      && $element['#number_type'] == 'integer'
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'integer' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'integer' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('!title field accepts only numbers.', array('!title' => $element['#title']));
  }
}
