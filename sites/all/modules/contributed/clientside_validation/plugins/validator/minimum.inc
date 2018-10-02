<?php

$plugin = array(
  'label' => t('Minimum'),
  'validator' => array(
    'class' => 'CvCoreMinimumValidator',
  ),
  'weight' => -99,
);

class CvCoreMinimumValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    if (!isset($element['#number_type']) || !isset($element['#entity_type'])) {
      return FALSE;
    }
    $instance = field_widget_instance($element, $form_state);
    return isset($instance['settings']['min']) && !empty($instance['settings']['min']);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $instance = field_widget_instance($element, $form_state);
    $name = $this->getName($element);
    $element['#cv_data']['min'] = $instance['settings']['min'];
    return array(
      'rules' => array(
        $name => array(
          'min' => floatval($instance['settings']['min']),
        ),
      ),
      'messages' => array(
        $name => array(
          'min' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('!title field has to be greater or equal than @min.', array('@min' => $element['#cv_data']['min'], '!title' => $element['#title']));
  }

}
