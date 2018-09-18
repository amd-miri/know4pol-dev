<?php

$plugin = array(
  'label' => t('File'),
  'validator' => array(
    'class' => 'CvWebformFileValidator',
  ),
);

class CvWebformFileValidator extends CvWebformValidator {

  public function supports(array $element, array &$form_state) {
    if (!parent::supports($element, $form_state)) {
      return FALSE;
    }
    return $element['#webform_component']['type'] == 'file';
  }

  public function getName(array $element) {
    return (isset($element['upload']) && isset($element['upload']['#name'])) ? $element['upload']['#name'] : '';
  }
  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element);
    $settings = array();
    $extensions = array();
    if (isset($element['#webform_component']['filtering']['types']) && !empty($element['#webform_component']['extra']['filtering']['types'])) {
      $extensions = $element['#webform_component']['extra']['filtering']['types'];
    }
    if (isset($element['#webform_component']['extra']['filtering']['addextensions']) && !empty($element['#webform_component']['extra']['filtering']['addextensions'])) {
      $extensions = array_merge($extensions, explode(',', $element['#webform_component']['extra']['filtering']['addextensions']));
    }
    if ($extensions) {
      $element['#cv_data']['extensions'] = $extensions;
      $settings['rules'][$name]['extension'] = implode('|', $extensions);
      $settings['messages'][$name]['extension'] = $this->getMessage($element);
    }
    return $settings;
  }

  public function getMessage(array $element) {
    return t('Only files with a @exts extension are allowed for !title.', array('@exts' => implode(', ', $element['#cv_data']['extensions']), '!title' => $element['#title']));
  }

}
