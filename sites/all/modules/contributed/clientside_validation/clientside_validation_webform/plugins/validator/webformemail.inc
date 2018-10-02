<?php

$plugin = array(
  'label' => t('Email'),
  'validator' => array(
    'class' => 'CvWebformEmailValidator',
  ),
);

class CvWebformEmailValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
      $element['#webform_component']['type'] == 'email'
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
