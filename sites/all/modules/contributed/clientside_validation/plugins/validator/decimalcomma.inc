<?php

$plugin = array(
  'label' => t('Decimal (comma)'),
  'validator' => array(
    'class' => 'CvCoreDecimalCommaValidator',
  ),
  'weight' => -99,
);

class CvCoreDecimalCommaValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    if (!isset($element['#type']) || !isset($element['#number_type'])) {
      return FALSE;
    }

    $separator = '.';
    if (isset($element['#entity_type'])) {
      $field = field_widget_field($element, $form_state);
      if (isset($field['settings']['decimal_separator'])) {
        $separator = $field['settings']['decimal_separator'];
      }
    }

    return (
      $element['#type'] == 'textfield'
      && in_array($element['#number_type'], array('decimal', 'float'))
      && $separator == ','
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'numberDE' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'numberDE' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/decimalcomma.cv.js';
    return $files;
  }

  public function getMessage(array $element) {
    return t("!title field accepts only numbers (use a ',' as decimal point).", array('!title' => $element['#title']));
  }

}
