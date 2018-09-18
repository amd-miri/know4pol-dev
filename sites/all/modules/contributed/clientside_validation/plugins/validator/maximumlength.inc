<?php

$plugin = array(
  'label' => t('Maximum length'),
  'validator' => array(
    'class' => 'CvCoreMaximumLengthValidator',
  ),
  'weight' => -99,
);

class CvCoreMaximumLengthValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return
      (isset($element['#maxlength']) && $element['#maxlength'] > 0)
      || (isset($element['#type']) && $element['#type'] == 'select' && $element['#multiple']);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    if ($element['#type'] == 'select') {
      $max = count($element['#options']);
      if (isset($element['#entity_type'])) {
        $field = field_widget_field($element, $form_state);
        // If field cardinality equals 1, only one option can be selected.
        // If field cardinality is unlimited, it is set to -1.
        if ($field['cardinality'] > 1) {
          $max = $field['cardinality'];
        }
      }
    }
    else {
      $max = $element['#maxlength'];
    }
    $name = $this->getName($element);
    $element['#cv_data']['maxlength'] = $max;
    return array(
      'rules' => array(
        $name => array(
          'maxlength' => (int) $max,
        ),
      ),
      'messages' => array(
        $name => array(
          'maxlength' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    if ($element['#type'] == 'select') {
      return t('!title field has to have maximum @max values.', array('!title' => $element['#title'], '@max' => $element['#cv_data']['maxlength']));
    }
    return t('!title field has a maximum length of @max.', array('!title' => $element['#title'], '@max' => $element['#cv_data']['maxlength']));
  }

}
