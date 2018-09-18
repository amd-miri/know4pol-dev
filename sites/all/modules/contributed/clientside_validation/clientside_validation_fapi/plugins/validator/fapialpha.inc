<?php

$plugin = array(
  'label' => t('Alpha'),
  'validator' => array(
    'class' => 'CvFAPIAlphaValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_alpha',
      'js_rule' => 'regexMatchPCRE',
      'js_arg' => '/^[\p{L}]*$/uD',
    ),
  ),
);

class CvFAPIAlphaValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('Use only alpha characters at !title.', array('!title' => $element['#title']));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/regexmatchpcre.cv.js';
    return $files;
  }

  public function getJsArg(array $element) {
    return array('expressions' => array('alpha' => $this->js_arg), 'messages' => array('alpha' => $this->getMessage($element)));
  }

}
