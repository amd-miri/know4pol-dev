<?php

$plugin = array(
  'label' => t('Minimum words'),
  'validator' => array(
    'class' => 'CvFieldValidation1MinWordsValidator',
    'constructor argument' => array(
      'field_validation_rule' => 'min_words',
      'js_rule' => 'minWords',
      'js_arg' => NULL,
    ),
  ),
);

class CvFieldValidation1MinWordsValidator extends CvFieldValidationValidator {
}
