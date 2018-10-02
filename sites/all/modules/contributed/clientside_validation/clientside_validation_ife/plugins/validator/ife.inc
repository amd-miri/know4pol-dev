<?php

$plugin = array(
  'label' => t('Inline Form Errors'),
  'validator' => array(
    'class' => 'CvIFEValidator',
  ),
);


class CvIFEValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'form'
      && isset($element['#ife_display'])
      && $element['#ife_display'] == 3

    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $element['#validate'][] = 'clientside_validation_ife_validator';
    return array();
  }

  public function getMessage(array $element) {
  }

}
