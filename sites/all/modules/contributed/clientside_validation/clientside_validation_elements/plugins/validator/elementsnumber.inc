<?php

$plugin = array(
  'label' => t('Number'),
  'validator' => array(
    'class' => 'CvElementsNumberValidator',
  ),
);


class CvElementsNumberValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && (
        $element['#type'] == 'numberfield'
        ||
        $element['#type'] == 'rangefield'
      )
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $step = isset($element['#step']) ? $element['#step'] : 1;
    $max = isset($element['#max']) ? $element['#max'] : 1;
    $min = isset($element['#min']) ? $element['#min'] : 1;
    $is_decimal = drupal_strtolower($step) == 'any' || floor($step) != $step || floor($min) != $min || floor($max) != $max;
    $rule = $is_decimal ? 'number' : 'integer';
    $element['#cv_data']['is_decimal'] = $is_decimal;
    return array(
      'rules' => array(
        $name => array(
          $rule => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          $rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return $element['#cv_data']['is_decimal'] ? t("!title field accepts only numbers (use a '.' as decimal point).", array('!title' => $element['#title'])) : t('!title field accepts only numbers.', array('!title' => $element['#title']));
  }

}
