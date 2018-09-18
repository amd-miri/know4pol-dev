<?php

$plugin = array(
  'label' => t('Minimum'),
  'validator' => array(
    'class' => 'CvFieldValidation1MinValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'numeric',
      'js_rule' => 'min',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1MinValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $min = $this->getJsArg($element);
    return $min != '' && is_numeric($min);
  }

  public function getJsArg(array $element) {
    $data = parent::getJsArg($element);
    $min = '';
    if (strpos($data, '|') !== FALSE) {
      list($min) = explode('|', $data);
      if ($min != '' && is_numeric($min)) {
        $min = (int) $min;
      }
    }
    else {
      if ($data != '' && is_numeric($data)) {
        $min = (int) $data;
      }
    }
    return $min;
  }

}
