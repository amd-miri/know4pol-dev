<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvElementsMaxValidator',
  ),
);


class CvElementsMaxValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && (
        $element['#type'] == 'numberfield'
        ||
        $element['#type'] == 'rangefield'
      )
      && isset($element['#max'])
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $step = isset($element['#step']) ? $element['#step'] : 1;
    $max = $element['#max'];
    $rule = drupal_strtolower($step) == 'any' ? 'max' : 'Html5Max';
    return array(
      'rules' => array(
        $name => array(
          $rule => $rule == 'max' ? floatval($max) : array('max' => floatval($max), 'step' => floatval($step)),
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
    $step = isset($element['#step']) ? $element['#step'] : 1;
    return drupal_strtolower($step) == 'any' ? t('!title field has to be smaller than @max', array('!title' => $element['#title'], '@max' => $element['#max'])) : t('!title field has to be smaller than @max with steps of @step.', array('!title' => $element['#title'], '@max' => $element['#max'], '@step' => $step));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_elements') . '/plugins/validator/js/min_max.cv.js';
    return $files;
  }
}
