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
class views_plugin_style_nexteuropa_listing extends views_plugin_style {

  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['listing_columns'] = array('default' => NULL);
    $options['listing_modifier'] = array('default' => NULL);
    $options['listing_wrapper_modifier'] = array('default' => NULL);
    $options['listing_item_modifier'] = array('default' => NULL);
    return $options;
  }

  /**
   * Form.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['listing_columns'] = array(
      '#type' => 'select',
      '#title' => t('BEM: Listing Layout'),
      '#options' => array(
        'default' => t('Default'),
        'two_columns' => t('Two Columns'),
        'three_columns' => t('Three Columns'),
        'row_two' => t('Row with two items'),
        'row_three' => t('Row with three items'),
      ),
      '#default_value' => $this->options['listing_columns'],
    );

    $form['listing_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('BEM: Listing Modifier'),
      '#default_value' => $this->options['listing_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );

    $form['listing_wrapper_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('BEM: Listing Wrapper Modifier'),
      '#default_value' => $this->options['listing_wrapper_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );

    $form['listing_item_modifier'] = array(
      '#type' => 'textfield',
      '#title' => t('BEM: Listing Item Modifier'),
      '#default_value' => $this->options['listing_item_modifier'],
      '#description' => t('Class names separated by spaces.'),
    );
  }

}
