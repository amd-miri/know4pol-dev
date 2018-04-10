<?php

/**
 * @file
 * Code for the NexteuropaNewsroomAgendaItem class.
 */

/**
 * NexteuropaNewsroomAgendaItem class.
 */
class NexteuropaNewsroomAgendaItem {

  protected $items = [];
  protected $date = NULL;

  /**
   * Gets agenda items.
   *
   * @return array
   *   Agenda items.
   */
  public function getItems() {
    return $this->items;
  }

  /**
   * Sets agenda items.
   *
   * @param array $value
   *   Agenda items.
   */
  public function setItems($value) {
    $this->items = $value;
  }

  /**
   * Gets agenda date.
   *
   * @return Datetime
   *   Agenda date.
   */
  public function getDate() {
    return $this->date;
  }

  /**
   * Sets agenda date.
   *
   * @param string $value
   *   Agenda date.
   */
  public function setDate($value) {
    $this->date = $value;
  }

  /**
   * Adds item to items array.
   *
   * @param object $value
   *   DB result value.
   */
  public function addItem($value) {
    $node = node_load($value->nid);
    $value->title = $node->title;
    $value->related_items = NexteuropaNewsroomRelatedItemHelper::getRelatedItems($value->nid);
    $value->url = NexteuropaNewsroomHelper::getNodeMainUrl($node);
    $value->prepared_start_date = $value->start_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
    $value->prepared_end_date = $value->end_date_obj->format(NexteuropaNewsroomAgenda::OUTPUT_DATE_FORMAT);
    $this->items[] = $value;
  }

  /**
   * Checks if agenda items is empty.
   *
   * @return bool
   *   Is empty.
   */
  public function isEmpty() {
    return empty($this->getItems());
  }

}
