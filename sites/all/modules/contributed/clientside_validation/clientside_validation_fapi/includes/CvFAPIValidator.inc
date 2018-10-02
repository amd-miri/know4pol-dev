<?php

abstract class CvFAPIValidator extends ClientsideValidationValidator {
  protected $fapi_rule_callback;
  protected $js_rule;
  protected $js_arg;

  public function __construct($args) {
    parent::__construct();
    if (!isset($args['fapi_rule_callback'])) {
      dpm(debug_backtrace());
    }
    $this->fapi_rule_callback = $args['fapi_rule_callback'];
    $this->js_rule = $args['js_rule'];
    $this->js_arg = $args['js_arg'];
  }

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#rules'])
      && $this->getRule($element)
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $arg = $this->getJsArg($element);
    return array(
      'rules' => array(
        $name => array(
          $this->js_rule => is_numeric($arg) ? floatval($arg) : $arg,
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getJsArg(array $element) {
    return $this->js_arg;
  }

  public function getRule($element) {
    $data = _fapi_validation_data('rules');
    foreach ($element['#rules'] as $rule) {
      $params = array($element['#value']);
      $error_message = NULL;

      // If $rule is an array, use error message if is set.
      if (is_array($rule)) {
        if (isset($rule['error'])) {
          $error_message = $rule['error'];
        }
        if (!isset($rule['rule'])) {
          drupal_set_message(t('Rule array with wrong structure on %field.', array('%field' => $element['#name'])), 'error');
          continue;
        }
        $rule = $rule['rule'];
      }

      preg_match('/^(.*?)(\[(.*)\])?$/', $rule, $rs);

      $rule = $rs[1];
      // Parsing parameters.
      if (isset($rs[3]) && $rs[1] != 'regexp') {
        $params[] = preg_split('/ *, */', $rs[3]);
      }
      elseif (isset($rs[3])) {
        $params[] = $rs[3];
      }

      if (count($params) > 1) {
        $params = $params[1];
      }
      if (isset($data[$rule]) && $data[$rule]['callback'] == $this->fapi_rule_callback) {
        return array('rule' => $data[$rule], 'params' => $params, 'error' => $error = is_null($error_message) ? $data[$rule]['error_msg'] : $error_message);
      }
    }
    return FALSE;
  }
}
