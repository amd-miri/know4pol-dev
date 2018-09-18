<?php

$plugin = array(
  'label' => t('Hierarchical Select'),
  'validator' => array(
    'class' => 'CvTermReferenceTreeValidator',
  ),
);


class CvTermReferenceTreeValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'checkbox_tree'
      && isset($element['#required']) && $element['#required']
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $class = drupal_clean_css_identifier($this->getName($element) . '_group');
    $element['#attributes']['class'][] = $class;
    return $this->getJavascriptSettingsRecur($element, $element, $form_state);

  }

  public function getJavascriptSettingsRecur(array &$element, array &$root_element, array &$form_state, &$settings = array()) {
    if ($element['#type'] == 'checkbox') {
      $class = drupal_clean_css_identifier($this->getName($root_element) . '_group');
      $settings['rules'][$this->getName($element)]['require_from_group'] = array(1, '.' . $class . ' input[type="checkbox"]');
      $settings['messages'][$this->getName($element)]['require_from_group'] = $this->getMessage($root_element);
      $settings['groups'][$class][] = $this->getName($element);
    }
    foreach (element_children($element) as $child) {
      $this->getJavascriptSettingsRecur($element[$child], $root_element, $form_state, $settings);
    }
    return $settings;
  }

  public function getMessage(array $element) {
    return isset($element['#required_error']) ? $element['#required_error'] : t('!title field is required.', array('!title' => $element['#title']));
  }

  public function setDataAttributes(array &$element, array &$form_state) {
    $js_settings = $this->getJavascriptSettings($element, $form_state);
    $this->setDataAttributesRecur($element, $form_state, $js_settings);
  }

  public function setDataAttributesRecur(&$element, $form_state, $js_settings) {
    if ($element['#type'] == 'checkbox') {
      $name = $this->getName($element);
      foreach ($js_settings['rules'][$name] as $rulename => $rulearg) {
        $element['#attributes']['data-rule' . drupal_ucfirst(drupal_strtolower($rulename))] = drupal_json_encode($rulearg);
        $element['#attributes']['data-msg' . drupal_ucfirst(drupal_strtolower($rulename))] = $js_settings['messages'][$name][$rulename];
      }
    }
    foreach (element_children($element) as $child) {
      $this->setDataAttributesRecur($element[$child], $form_state, $js_settings);
    }
  }
}
