<?php

$plugin = array(
  'label' => t('Minimum selection length'),
  'validator' => array(
    'class' => 'CvWebformValidationSelectMinValidator',
    'constructor argument' => array(
      'js_rule' => 'minlength',
      'webform_rule' => 'select_min',
    ),
  ),
);

class CvWebformValidationSelectMinValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return t('Please select at least @min options for !title.', array('@min' => $element['#cv_data']['minlength'], '!title' => $element['#title']));
  }
}
