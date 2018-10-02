<?php

$plugin = array(
  'label' => t('Minimum words'),
  'validator' => array(
    'class' => 'CvWebformValidationMinWordsValidator',
    'constructor argument' => array(
      'js_rule' => 'minWords',
      'webform_rule' => 'min_words',
    ),
  ),
);

class CvWebformValidationMinWordsValidator extends CvWebformValidationValidator {
  public function getMessage(array $element) {
    return format_plural($element['#cv_data']['minWords'], '!title should be at least 1 word long.', '!title should be at least @count words long.', array('!title' => $element['#title']));
  }
}
