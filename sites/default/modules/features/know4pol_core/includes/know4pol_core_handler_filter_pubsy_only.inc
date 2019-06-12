<?php

/**
 * Create a handler for a custom views filter called "Pubsy only".
 */
class Know4polCoreHandlerFilterPubsyOnly extends views_handler_filter {

  /**
   * Override the value_form function.
   *
   * Options form subform for setting exposed filter options.
   */
  public function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    $form['value'] = array(
      '#title' => 'Pubsy only',
      '#type' => 'select',
      '#options' => array(0 => 'No', 1 => 'Yes'),
      '#default_value' => 0,
    );
  }

  /**
   * Alters Views query when filter is used.
   */
  public function query() {
    // Make sure base table is included in the query.
    $this->ensure_my_table();
    // Adds a relationship and a condition for the custom filter.
    if ($this->value[0] == 1) {
      $join = new views_join();
      $join->construct('field_data_field_pub_dc_rel_ispartofseries', $this->table, 'nid', 'entity_id', array(), 'LEFT');
      $this->query->add_relationship('field_data_field_pub_dc_rel_ispartofseries', $join, 'users');
      $this->query->add_where_expression($this->options['group'], "field_data_field_pub_dc_rel_ispartofseries.field_pub_dc_rel_ispartofseries_value LIKE '%JRC%'");
    }
  }

}
