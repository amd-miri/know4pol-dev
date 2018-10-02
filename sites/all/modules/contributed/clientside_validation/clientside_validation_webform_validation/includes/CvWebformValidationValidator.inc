<?php

abstract class CvWebformValidationValidator extends CvWebformValidator {
  protected $webform_rule;
  protected $js_rule;
  public function __construct($args) {
    parent::__construct();
    $this->webform_rule = $args['webform_rule'];
    $this->js_rule = $args['js_rule'];
  }

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    return !!$rule;
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $name = $this->getName($element);
    $element['#cv_data'][$this->js_rule] = $rule['data'];
    return array(
      'rules' => array(
         $name => array(
          $this->js_rule => is_numeric($rule['data']) ? floatval($rule['data']) : $rule['data'],
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }
}
