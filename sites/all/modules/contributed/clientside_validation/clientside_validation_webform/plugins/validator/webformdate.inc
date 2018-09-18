<?php

$plugin = array(
  'label' => t('Date'),
  'validator' => array(
    'class' => 'CvWebformDateValidator',
  ),
);

class CvWebformDateValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
      $element['#webform_component']['type'] == 'date'
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $settings = array();
    if (isset($element['#required']) && $element['#required']) {
      $day_name = $this->getName($element) . '[day]';
      $month_name = $this->getName($element) . '[month]';
      $year_name = $this->getName($element) . '[year]';
      $settings = array(
        'rules' => array(
          $day_name => array(
            'required' => TRUE,
          ),
          $month_name => array(
            'required' => TRUE,
          ),
          $year_name => array(
            'required' => TRUE,
          ),
        ),
        'messages' => array(
          $day_name => array(
            'required' => t('Day in !title field is required.', array('!title' => $element['#title'])),
          ),
          $month_name => array(
            'required' => t('Month in !title field is required.', array('!title' => $element['#title'])),
          ),
          $year_name => array(
            'required' => t('Year in !title field is required.', array('!title' => $element['#title'])),
          ),
        ),
      );
    }
    return $settings;
  }

  public function getMessage(array $element) {
  }

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    foreach (array('day', 'month', 'year') as $child) {
      $name = $this->getName($element[$child]);
      foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
        $element[$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
        $element[$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
      }
    }
  }

}
