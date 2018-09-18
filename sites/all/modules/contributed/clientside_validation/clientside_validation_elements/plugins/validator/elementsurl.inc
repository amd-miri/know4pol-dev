<?php

$plugin = array(
  'label' => t('URL'),
  'validator' => array(
    'class' => 'CvElementsURLValidator',
  ),
);


class CvElementsURLValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'urlfield'
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'url' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'url' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('The value in !title is not a valid URL.', array('!title' => $element['#title']));
  }

}
