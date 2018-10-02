<?php

$plugin = array(
  'label' => t('States required'),
  'validator' => array(
    'class' => 'CvStatesRequiredValidator',
  ),
);


class CvStatesRequiredValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    $supports = (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && isset($element['#states'])
    );
    if (!$supports) {
      return FALSE;
    }
    foreach ($element['#states'] as $state => $triggers) {
      while (strpos($state, '!') === 0) {
        $state = drupal_substr($state, 1);
      }
      if ($state == 'required' || $state == 'optional') {
        return TRUE;
      }
    }
    return FALSE;

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'statesrequired' => TRUE,
        ),
      ),
    );
  }

  public function getMessage(array $element) {
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_states') . '/plugins/validator/js/states.cv.js';
    return $files;
  }

}
