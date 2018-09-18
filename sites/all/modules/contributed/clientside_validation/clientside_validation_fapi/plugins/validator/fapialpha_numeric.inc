<?php

$plugin = array(
  'label' => t('Alpha numeric'),
  'validator' => array(
    'class' => 'CvFAPIAlphaNumericValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_alpha_numeric',
      'js_rule' => 'regexMatchPCRE',
      'js_arg' => '/^[\p{L}\p{N}]*$/uD',
    ),
  ),
);

class CvFAPIAlphaNumericValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Use only alpha numerics characters at !title.', array('!title' => $element['#title']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/regexmatchpcre.cv.js';
    return $files;
  }

  public function getJsArg(array $element) {
    return array('expressions' => array('alphanumeric' => $this->js_arg), 'messages' => array('alphanumeric' => $this->getMessage($element)));
  }
}
