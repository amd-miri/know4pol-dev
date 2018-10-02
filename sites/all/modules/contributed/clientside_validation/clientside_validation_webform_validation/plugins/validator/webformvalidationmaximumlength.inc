<?php

$plugin = array(
  'label' => t('Maximum length'),
  'validator' => array(
    'class' => 'CvWebformValidationMaximumLengthValidator',
    'constructor argument' => array(
      'js_rule' => 'maxlength',
      'webform_rule' => 'max_length',
    ),
  ),
);


class CvWebformValidationMaximumLengthValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return t('!title should be at most @maxlength characters long.', array('!title' => $element['#title'], '@maxlength' => $element['#cv_data']['maxlength']));
  }
}