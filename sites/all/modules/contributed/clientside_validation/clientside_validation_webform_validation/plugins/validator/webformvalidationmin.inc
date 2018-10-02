<?php

$plugin = array(
  'label' => t('Minimum'),
  'validator' => array(
    'class' => 'CvWebformValidationMinimumValidator',
    'constructor argument' => array(
      'js_rule' => 'min',
      'webform_rule' => 'numeric',
    ),
  ),
);

class CvWebformValidationMinimumValidator extends CvWebformValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $minmax = explode('|', $rule['data']);
    return !empty($minmax[0]) && parent::supports($element, $form_state);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $data = explode('|', $rule['data']);
    $element['#cv_data']['min'] = floatval($data[0]);
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => floatval($data[0]),
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('!title field has to be greater or equal than @min.', array('!title' => $element['#title'], '@min' => $element['#cv_data']['min']));
  }
}