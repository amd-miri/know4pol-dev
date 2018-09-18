<?php

$plugin = array(
  'label' => t('Decimal (comma)'),
  'validator' => array(
    'class' => 'CvWebformDecimalCommaValidator',
  ),
);

class CvWebformDecimalCommaValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
      $element['#webform_component']['type'] == 'number'
      && !$element['#webform_component']['extra']['integer']
      && $element['#webform_component']['extra']['point'] == ','
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
         $name => array(
          'numberDE' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'numberDE' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t("!title field accepts only numbers (use a ',' as decimal point).", array('!title' => $element['#title']));
  }

}
