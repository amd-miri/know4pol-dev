<?php

abstract class CvWebformValidator extends ClientsideValidationValidator {
  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#webform_component']) &&
      (!isset($element['#webform_component']['extra']['exclude_cv'])
      || !$element['#webform_component']['extra']['exclude_cv'])
    );
  }
}
