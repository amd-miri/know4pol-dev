<?php

$plugin = array(
  'label' => t('Minimum'),
  'validator' => array(
    'class' => 'CvElementsMinValidator',
  ),
);


class CvElementsMinValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && (
        $element['#type'] == 'numberfield'
        ||
        $element['#type'] == 'rangefield'
      )
      && isset($element['#min'])
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $step = isset($element['#step']) ? $element['#step'] : 1;
    $min = $element['#min'];
    $rule = drupal_strtolower($step) == 'any' ? 'min' : 'Html5Min';
    return array(
      'rules' => array(
        $name => array(
          $rule => $rule == 'min' ? floatval($min) : array('min' => floatval($min), 'step' => floatval($step)),
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
    return drupal_strtolower($step) == 'any' ? t('!title field has to be greater than @min', array('!title' => $element['#title'], '@min' => $element['#min'])) : t('!title field has to be greater than @min with steps of @step.', array('!title' => $element['#title'], '@min' => $element['#min'], '@step' => $step));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_elements') . '/plugins/validator/js/min_max.cv.js';
    return $files;
  }
}
