<?php
/**
 * @file
 * Settings placeholder.
 */

/**
 * Class to define a style plugin handler.
 *
 * @codingStandardsIgnoreFile
 */
class views_plugin_style_nexteuropa_context_nav extends views_plugin_style_default {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['use_trimming'] = array('default' => NULL);
    return $options;
  }

  /**
   * Form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['use_trimming'] = array(
      '#type' => 'select',
      '#title' => t('Trimming to be applied'),
      '#options' => array(
        'default' => t('Default'),
        'yes' => t('Yes'),
      ),
      '#default_value' => $this->options['use_trimming'],
    );

  }

}
