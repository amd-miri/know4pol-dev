<?php

$plugin = array(
  'label' => t('Required'),
  'validator' => array(
    'class' => 'CvCoreRequiredValidator',
  ),
  'weight' => -99,
);

class CvCoreRequiredValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return
      parent::supports($element, $form_state)
      && isset($element['#required'])
      && ((boolean) $element['#required']);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    if ($element['#type'] == 'checkboxes') {
      $settings = array();
      $options = $element['#options'];
      ksort($options);
      reset($options);
      $firstone = key($options);
      $class = drupal_clean_css_identifier($this->getName($element[$firstone]) . '_group');
      $element['#attributes']['class'][] = $class;
      foreach (array_keys($element['#options']) as $child) {
        $settings['rules'][$this->getName($element[$child])]['require_from_group'] = array(1, '.' . $class . ' input[type="checkbox"]');
        $settings['messages'][$this->getName($element[$child])]['require_from_group'] = $this->getMessage($element);
        $settings['groups'][$class][] = $this->getName($element[$child]);
      }
      return $settings;
    }
    if ($element['#type'] == 'select') {
      // Use blacklist to avoid the '_none' value used as empty value by Drupal.
      $settings['rules'][$name]['blacklist'] = array('', '_none');
      $settings['messages'][$name]['blacklist'] = $this->getMessage($element);
      return $settings;
    }
    return array(
      'rules' => array(
        $name => array(
          'required' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'required' => $this->getMessage($element),
        ),
      )
    );
  }

  public function getMessage(array $element) {
    return isset($element['#required_error']) ? $element['#required_error'] : t('!title field is required.', array('!title' => $element['#title']));
  }

  public function setDataAttributes(array &$element, array &$form_state) {
    if ($element['#type'] == 'checkboxes') {
      $js_settings = $this->getJavascriptSettings($element, $form_state);
      foreach (array_keys($element['#options']) as $child) {
        $name = $this->getName($element[$child]);
        foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
          $element[$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = drupal_json_encode($rulearg);
          $element[$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
        }
      }
    }
    elseif ($element['#type'] == 'radios') {
      $js_settings = $this->getJavascriptSettings($element, $form_state);
      $name = $this->getName($element);
      foreach (array_keys($element['#options']) as $child) {
        foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
          $element[$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = drupal_json_encode($rulearg);
          $element[$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
        }
      }
    }
    else {
      parent::setDataAttributes($element, $form_state);
    }
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    if ($element['#type'] == 'select') {
      $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/blacklist.cv.js';
    }
    return $files;
  }
}
