<?php

$plugin = array(
  'label' => t('Unique'),
  'validator' => array(
    'class' => 'CvWebformValidationUniqueValidator',
    'constructor argument' => array(
      'js_rule' => 'notEqualTo',
      'webform_rule' => 'unique',
    ),
  ),
);

class CvWebformValidationUniqueValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $settings = array();
    $rule['components'];
    ksort($rule['components']);
    $firstone = reset($rule['components']);
    $group  = $firstone['element_name'] . '_group';
    $name = $this->getName($element);
    foreach ($rule['components'] as  $component) {
      if ($component['element_name'] != $name) {
        $settings['rules'][$name]['notEqualTo'][] = ':input[name="' . $component['element_name'] . '"]';
      }
      $settings['groups'][$group][] = $component['element_name'];
    }
    $settings['messages'][$name]['notEqualTo'] = $this->getMessage($element);
    return $settings;
  }

  public function getMessage(array $element) {
    return t('The value of !title is not unique.', array('!title' => $element['#title']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/notequalto.cv.js';
    return $files;
  }
}
