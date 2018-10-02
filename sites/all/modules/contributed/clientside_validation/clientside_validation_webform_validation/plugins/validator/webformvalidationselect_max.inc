<?php

$plugin = array(
  'label' => t('Maximum selection length'),
  'validator' => array(
    'class' => 'CvWebformValidationSelectMaxValidator',
    'constructor argument' => array(
      'js_rule' => 'maxlength',
      'webform_rule' => 'select_max',
    ),
  ),
);

class CvWebformValidationSelectMaxValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return t('Please select maximum @max options for !title.', array('@max' => $element['#cv_data']['maxlength'], '!title' => $element['#title']));
  }
}
