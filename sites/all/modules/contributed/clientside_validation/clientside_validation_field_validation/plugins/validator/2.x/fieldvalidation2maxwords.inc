<?php

$plugin = array(
  'label' => t('Maximum words'),
  'validator' => array(
    'class' => 'CvFieldValidation2MaxWordsValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'field_validation_words_validator',
      'js_rule' => 'maxWords',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation2MaxWordsValidator extends CvFieldValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $max = $this->getJsArg($element);
    return $max != '' && is_numeric($max);
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return $rule->settings['max'];
  }

}
