<?php

$plugin = array(
  'label' => t('Maximum words'),
  'validator' => array(
    'class' => 'CvWebformValidationMaxWordsValidator',
    'constructor argument' => array(
      'js_rule' => 'maxWords',
      'webform_rule' => 'max_words',
    ),
  ),
);

class CvWebformValidationMaxWordsValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return format_plural($element['#cv_data']['maxWords'], '!title should be at most 1 word long.', '!title should be at most @count words long.', array('!title' => $element['#title']));
  }
}