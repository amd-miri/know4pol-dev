<?php

$plugin = array(
  'label' => t('Hierarchical Select'),
  'validator' => array(
    'class' => 'CvHSValidator',
  ),
);


class CvHSValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'hierarchical_select'
      && isset($element['hierarchical_select']['selects'])
      && isset($element['#required']) && $element['#required']
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $settings = array();
    foreach(element_children($element['hierarchical_select']['selects']) as $child) {
      if ($element['#config']['enforce_deepest'] || $child < 1) {
        $name = $this->getName($element['hierarchical_select']['selects'][$child]);
        $settings['rules'][$name]['required'] = TRUE;
        $settings['messages'][$name]['required'] = $this->getMessage($element);
        $settings['rules'][$name]['blacklist'] = array('none', '_none', 'label_0');
        if (isset($element['#config']['special_items']['none'])) {
          $settings['rules'][$name]['blacklist'][] = $element['#config']['special_items']['none'];
        }
        $settings['messages'][$name]['blacklist'] = $this->getMessage($element);
      }
    }
    return $settings;
  }

  public function getMessage(array $element) {
    return isset($element['#required_error']) ? $element['#required_error'] : t('!title field is required.', array('!title' => $element['#title']));
  }

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    foreach(element_children($element['hierarchical_select']['selects']) as $child) {
      if ($element['#config']['enforce_deepest'] || $child < 1) {
        $name = $this->getName($element['hierarchical_select']['selects'][$child]);
        foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
          $element['hierarchical_select']['selects'][$child]['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = is_object($rulearg) || is_array($rulearg) ? drupal_json_encode($rulearg) : $rulearg;
          $element['hierarchical_select']['selects'][$child]['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
        }
      }
    }
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/blacklist.cv.js';
    return $files;
  }

}
