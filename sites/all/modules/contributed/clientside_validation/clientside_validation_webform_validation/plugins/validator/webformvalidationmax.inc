<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvWebformValidationMaximumValidator',
    'constructor argument' => array(
      'js_rule' => 'max',
      'webform_rule' => 'numeric',
    ),
  ),
);

class CvWebformValidationMaximumValidator extends CvWebformValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $minmax = explode('|', $rule['data']);
    return !empty($minmax[1]) && parent::supports($element, $form_state);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $data = explode('|', $rule['data']);
    $element['#cv_data']['max'] = floatval($data[1]);
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => floatval($data[1]),
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
    return t('!title has to be less than or equal to @max.', array('!title' => $element['#title'], '@max' => $element['#cv_data']['max']));
  }
}
