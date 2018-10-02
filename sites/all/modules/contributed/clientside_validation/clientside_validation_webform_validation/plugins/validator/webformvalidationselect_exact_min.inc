<?php

$plugin = array(
  'label' => t('Exact selection length (min)'),
  'validator' => array(
    'class' => 'CvWebformValidationSelectExactMinValidator',
    'constructor argument' => array(
      'js_rule' => 'minlength',
      'webform_rule' => 'select_exact',
    ),
  ),
);

class CvWebformValidationSelectExactMinValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return format_plural($element['#cv_data']['minlength'], 'Please select 1 option for !title.', 'Please select @count options for !title.', array('!title' => $element['#title']));
  }
}
