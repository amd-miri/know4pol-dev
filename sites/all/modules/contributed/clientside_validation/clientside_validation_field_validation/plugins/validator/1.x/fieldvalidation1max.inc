<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvFieldValidation1MaxValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'numeric',
      'js_rule' => 'max',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1MaxValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $max = $this->getJsArg($element);
    return $max != '' && is_numeric($max);
  }

  public function getJsArg(array $element) {
    $data = parent::getJsArg($element);
    $max = '';
    if (strpos($data, '|') !== FALSE) {
      list($min, $max) = explode('|', $data);
      if ($max != '' && is_numeric($max)) {
        $max = (int) $max;
      }
    }
    return $max;
  }

}
