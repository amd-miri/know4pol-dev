<?php

$plugin = array(
  'label' => t('Date max'),
  'validator' => array(
    'class' => 'CvWebformDateMaxValidator',
  ),
);

class CvWebformDateMaxValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return (
      $element['#webform_component']['type'] == 'date'
      && (isset($element['#year_end']) || isset($element['#end_date']))
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $element_name = isset($element['#year_end']) ? $this->getName($element) . '[year]' : 'webform-component-' . str_replace('_', '-', implode('--', array_slice($element['#parents'], 1)));
    $rule_name = isset($element['#year_end']) ? 'max' : 'datemax';
    $settings = array();
    if (isset($element['#year_end'])) {
      $settings = array(
        'rules' => array(
          $element_name => array(
            $rule_name => $element['#year_end'],
          ),
        ),
        'messages' => array(
          $element_name => array(
            $rule_name => $this->getMessage($element),
          ),
        ),
      );
    }
    else {
      $settings['groups'][$element_name] = array(
        $this->getName($element) . '[year]',
        $this->getName($element) . '[month]',
        $this->getName($element) . '[day]',
      );
      foreach ($settings['groups'][$element_name] as $name) {
        $settings['rules'][$name][$rule_name] = explode('-', $element['#end_date']);
        $settings['messages'][$name][$rule_name] = $this->getMessage($element);
      }
    }
    return $settings;
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform') . '/plugins/validator/js/datemax.cv.js';
    return $files;
  }

  public function getMessage(array $element) {
    return isset($element['#year_end']) ? t('The year in !title must be before @date', array('!title' => $element['#title'], '@date' => $element['#year_end'])) : t('The entered date in !title must be before @date', array('!title' => $element['#title'], '@date' => $element['#end_date']));
  }

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    if (isset($element['#year_end'])) {
      $name = $this->getName($element['year']);
      foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
        $element['year']['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
        $element['year']['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
      }
    }
    else {
      $name = 'webform-component-' . str_replace('_', '-', implode('--', array_slice($element['#parents'], 1)));
      foreach (array('day', 'month', 'year') as $child) {
        $name = $this->getName($element[$child]);
        foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
          $element[$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
          $element[$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
        }
      }
    }
  }
}
