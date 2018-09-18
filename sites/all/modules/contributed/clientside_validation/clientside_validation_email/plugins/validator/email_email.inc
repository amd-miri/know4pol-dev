<?php

$plugin = array(
  'label' => t('Email'),
  'validator' => array(
    'class' => 'CvCoreEmailValidator',
  ),
);


class CvCoreEmailValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#field_name'])
      && isset($element['#clientside_validation_type'])
      && $element['#clientside_validation_type'] == 'email'
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'email' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'email' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('The value in !title is not a valid email address.', array('!title' => $element['#title']));
  }

}
