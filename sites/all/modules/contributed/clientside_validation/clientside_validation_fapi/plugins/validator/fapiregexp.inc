<?php

$plugin = array(
  'label' => t('Regular expression'),
  'validator' => array(
    'class' => 'CvFAPIRegexpValidator',
    'constructor argument' => array(
      'fapi_rule_callback' => 'fapi_validation_rule_regexp',
      'js_rule' => 'regexMatchPCRE',
      'js_arg' => NULL,
    ),
  ),
);

class CvFAPIRegexpValidator extends CvFAPIValidator {

  public function getMessage(array $element) {
    $rule = $this->getRule($element);
    return isset($rule['error']) && $rule['error'] ? t($rule['error'], array('%field' => $element['#title'])) : t('!title value does not match rule.', array('!title' => $element['#title']));
  }

  public function getJsArg(array $element) {
    $rule = $this->getRule($element);
    return array('expressions' => array('regexp' => is_array($rule['params']) ? $rule['params'][0] : $rule['params']), 'messages' => array('regexp' => $this->getMessage($element)));
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation') . '/plugins/validator/js/regexmatchpcre.cv.js';
    return $files;
  }

}
