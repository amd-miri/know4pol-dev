<?php

$plugin = array(
  'label' => t('Maximum'),
  'validator' => array(
    'class' => 'CvCoreMaximumValidator',
  ),
  'weight' => -99,
);

class CvCoreMaximumValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    if (!isset($element['#number_type']) || !isset($element['#entity_type'])) {
      return FALSE;
    }
    $instance = field_widget_instance($element, $form_state);
    return isset($instance['settings']['max']) && !empty($instance['settings']['max']);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $instance = field_widget_instance($element, $form_state);
    $name = $this->getName($element);
    $element['#cv_data']['max'] = $instance['settings']['max'];
    return array(
      'rules' => array(
        $name => array(
          'max' => floatval($instance['settings']['max']),
        ),
      ),
      'messages' => array(
        $name => array(
          'max' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('!title field has to be smaller than @max.', array('!title' => $element['#title'], '@max' => $element['#cv_data']['max']));
  }

}
