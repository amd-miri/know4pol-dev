<?php

$plugin = array(
  'label' => t('Date format'),
  'validator' => array(
    'class' => 'CvDateDateFormatValidator',
  ),
  'weight' => -99,
);


class CvDateDateFormatValidator extends ClientsideValidationValidator {

  public function supports(array $element, array &$form_state) {
    return (
      parent::supports($element, $form_state)
      && isset($element['#type'])
      && in_array($element['#type'], array('date_popup', 'date_text'))
      && isset($element['date'])
    );
  }

  public function getJavascriptSettings(array &$element, array &$form_state) {
    $name = $this->getName($element['date']);
    $granularity = date_format_order($element['#date_format']);
    $format = date_limit_format($element['#date_format'], array_intersect($granularity, array('month', 'day', 'year')));
    $splitter = '/';
    if (strpos($format, '.') !== FALSE) {
      $splitter = '.';
    }
    elseif (strpos($format, ' ') !== FALSE) {
      $splitter = ' ';
    }
    elseif (strpos($format, '-') !== FALSE) {
      $splitter = '-';
    }
    $parts = explode($splitter, $format);
    $daypos = (array_search('d', $parts) === FALSE) ? array_search('j', $parts) : array_search('d', $parts);
    foreach (array('m', 'M', 'F', 'n') as $m) {
      $monthpos = array_search($m, $parts);
      if ($monthpos !== FALSE) {
        break;
      }
    }
    $yearpos = array_search('Y', $parts);
    return array(
      'rules' => array(
        $name => array(
          'dateFormat' => array(
            'format' => $format,
            'splitter' => $splitter,
            'daypos' => $daypos,
            'monthpos' => $monthpos,
            'yearpos' => $yearpos
          )
        ),
      ),
      'messages' => array(
        $name => array(
          'dateFormat' => $this->getMessage($element),
        ),
      ),
    );
  }

  public function jsFiles(array &$element) {
    $files = parent::jsFiles($element);
    $files[] = drupal_get_path('module', 'clientside_validation_date') . '/plugins/validator/js/dateformat.cv.js';
    return $files;
  }

  public function getMessage(array $element) {
    return t('The value in !title is not a valid date.', array('!title' => $element['#title']));
  }

}
