<?php

$plugin = array(
  'label' => t('Decimal (point)'),
  'validator' => array(
    'class' => 'CvWebformDecimalPointValidator',
  ),
);

class CvWebformDecimalPointValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
      $element['#webform_component']['type'] == 'number'
      && !$element['#webform_component']['extra']['integer']
      && $element['#webform_component']['extra']['point'] == '.'
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
         $name => array(
          'number' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'number' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t("!title field accepts only numbers (use a '.' as decimal point).", array('!title' => $element['#title']));
  }

}
