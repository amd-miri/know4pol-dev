<?php

$plugin = array(
  'label' => t('Require one or more of several fields'),
  'validator' => array(
    'class' => 'CvWebformValidationSomeOfSeveralValidator',
    'constructor argument' => array(
      'js_rule' => 'require_from_group',
      'webform_rule' => 'someofseveral',
    ),
  ),
);


class CvWebformValidationSomeOfSeveralValidator extends CvWebformValidationValidator {

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    ksort($rule['components']);
    $firstone = reset($rule['components']);
    $name = $this->getName($element);
    $names = array();
    $group_names = array();
    $group = $firstone['element_name'] . '_group';
    $element['#cv_data']['rule'] = $rule;
    foreach ($rule['components'] as $component) {
      $names[] = ':input[name="' . $component['element_name'] . '"]';
      $group_names[] = $component['element_name'];
    }

    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => array(isset($rule['data']) ? ((int) $rule['data']) : 1, implode(', ', $names)),
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
      'groups' => array(
        $group => $group_names,
      ),
    );
  }

  public function getMessage(array $element) {
    $rule = $element['#cv_data']['rule'];
    $names = array();
    foreach ($rule['components'] as $component) {
      $names[] = _webform_filter_xss($component['name']);
    }
    return t('You must complete at least @min_selections of these items:', array('@min_selections' => isset($rule['data']) ? ((int) $rule['data']) : 1)) . theme('item_list', array('items' => $names));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_webform_validation') . '/plugins/validator/js/oneof.cv.js';
    return $files;
  }
}
