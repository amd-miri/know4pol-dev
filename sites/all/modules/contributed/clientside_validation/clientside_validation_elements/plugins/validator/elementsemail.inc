<?php

$plugin = array(
  'label' => t('Email'),
  'validator' => array(
    'class' => 'CvElementsEmailValidator',
  ),
);


class CvElementsEmailValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'emailfield'
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
