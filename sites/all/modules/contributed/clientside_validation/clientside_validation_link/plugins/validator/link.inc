<?php

$plugin = array(
  'label' => t('Link'),
  'validator' => array(
    'class' => 'CvCoreLinkValidator',
  ),
);


class CvCoreLinkValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    $supports = (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && $element['#type'] == 'link_field'
      && isset($element['#entity_type'])
      && isset($element['#field_name'])
      && isset($element['#bundle'])
    );
    if (!$supports) {
      return FALSE;
    }
    $instance = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);
    return $instance && isset($instance['settings']['validate_url']) && $instance['settings']['validate_url'];

  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element['url']);
    return array(
      'rules' => array(
        $name => array(
          'drupalUrl' => TRUE,
        ),
      ),
      'messages' => array(
        $name => array(
          'drupalUrl' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function getMessage(array $element) {
    return t('The value in !title is not a valid url.', array('!title' => $element['#title']));
  }

}
