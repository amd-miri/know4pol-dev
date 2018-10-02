<?php

$plugin = array(
  'label' => t('Time'),
  'validator' => array(
    'class' => 'CvWebformTimeRequiredValidator',
  ),
);

class CvWebformTimeRequiredValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
        $element['#webform_component']['type'] == 'time' && isset($element['hour']['#name']) && isset($element['#required']) && $element['#required']
        );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $hour_name = $this->getName($element['hour']);
    $minute_name = $this->getName($element['minute']);
    return array(
      'rules' => array(
        $hour_name => array(
          'required' => TRUE,
        ),
        $minute_name => array(
          'required' => TRUE,
        ),
      ),
      'messages' => array(
        $hour_name => array(
          'required' => t('Hour in !title field is required.', array('!title' => $element['#title'])),
        ),
        $minute_name => array(
          'required' => t('Minute in !title field is required.', array('!title' => $element['#title'])),
        ),
      ),
    );
  }

  public function getMessage(array $element) {

  }

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    foreach (array('hour', 'minute') as $child) {
      $name = $this->getName($element[$child]);
      foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
        $element[$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
        $element[$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
      }
    }
  }

}
