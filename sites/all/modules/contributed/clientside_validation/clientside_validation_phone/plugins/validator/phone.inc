<?php

$plugin = array(
  'label' => t('Phone'),
  'validator' => array(
    'class' => 'CvCorePhoneValidator',
  ),
);


class CvCorePhoneValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#field_name'])
      && isset($element['#clientside_validation_type'])
      && $element['#clientside_validation_type'] == 'phone'
    );

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $info = field_info_field($element['#field_name']);
    $name = $this->getName($element);
    return array(
      'rules' => array(
        $name => array(
          'phone' => $info['settings']['country'],
        ),
      ),
      'messages' => array(
        $name => array(
          'phone' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_phone') . '/plugins/validator/js/phone.cv.js';
    return $files;
  }

  public function getMessage(array $element) {
    return t('The value in !title is not a valid phone number.', array('!title' => $element['#title']));
  }

}
