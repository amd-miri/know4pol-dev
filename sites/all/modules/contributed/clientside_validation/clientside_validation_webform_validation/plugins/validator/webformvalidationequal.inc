<?php

$plugin = array(
  'label' => t('Equal'),
  'validator' => array(
    'class' => 'CvWebformValidationEqualValidator',
    'constructor argument' => array(
      'js_rule' => 'equalTo',
      'webform_rule' => 'equal',
    ),
  ),
);

class CvWebformValidationEqualValidator extends CvWebformValidationValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    $first = reset($rule['components']);
    return $first['element_name'] != $this->getName($element);
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $rule = _clientside_validation_get_webform_validation_rules($element, $form_state['complete form'], $this->webform_rule);
    ksort($rule['components']);
    $firstone = reset($rule['components']);
    $form_key = implode('][', webform_component_parent_keys(node_load($firstone['nid']), $firstone));
    $name = $this->getName($element);
    $element['#cv_data'][$this->js_rule] = $firstone;
    return array(
      'rules' => array(
        $name => array(
          $this->js_rule => ':input[name=\'submitted[' . $form_key . ']\']',
        ),
      ),
      'messages' => array(
        $name => array(
          $this->js_rule => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('!title does not match @target.', array('!title' => $element['#title'], '@target' => $element['#cv_data'][$this->js_rule]['name']));
  }
}
