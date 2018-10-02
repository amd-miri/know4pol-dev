<?php

$plugin = array(
  'label' => t('Max'),
  'validator' => array(
    'class' => 'CvWebformMaxValidator',
  ),
);

class CvWebformMaxValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#webform_component']['extra']['max'])
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $settings = $element['#webform_component']['extra'];
    $rule = (isset($settings['step']) && !empty($settings['step']) && $settings['step'] != 'any') ? 'webformMax' : 'max';
    return array(
      'rules' => array(
         $name => array(
          $rule => $rule == 'max' ? floatval($settings['max']) : array(floatval($settings['max']), floatval($settings['step'])),
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
    $settings = $element['#webform_component']['extra'];
    return (isset($settings['step']) && !empty($settings['step']) && $settings['step'] != 'any') ? t('!title field has to be less than @max and must be dividable by @step.', array('!title' => $element['#title'], '@max' => $settings['max'], '@step' => $settings['step'])) : t('!title field has to be less than @max.', array('!title' => $element['#title'], '@max' => $settings['max']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform') . '/plugins/validator/js/min_max.cv.js';
    return $files;
  }

}