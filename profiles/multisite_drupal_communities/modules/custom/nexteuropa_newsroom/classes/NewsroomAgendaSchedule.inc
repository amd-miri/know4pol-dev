<?php

/**
 * @file
 * Code for the NewsroomAgendaSchedule class.
 */

/**
 * NewsroomAgendaSchedule class.
 */
class NewsroomAgendaSchedule extends NewsroomAgenda {

  protected $lastAgendaDate = NULL;

  /**
   * NewsroomAgendaSchedule constructor.
   *
   * @param object $type
   *   Newsroom type.
   * @param array $topics
   *   Newsroom topic.
   * @param object $current_day
   *   Current date.
   */
  public function __construct($type, $topics, $current_day) {
    $this->setCurrentDate($current_day);
    parent::__construct($type, $topics);
  }

  /**
   * Gets the latest date in the agenda.
   *
   * @return Datetime
   *   Latest date in the agenda.
   */
  public function getLastAgendaDate() {
    return $this->lastAgendaDate;
  }

  /**
   * Sets the latest date in the agenda.
   *
   * @param object $value
   *   Latest date in the agenda.
   */
  public function setLastAgendaDate($value) {
    $this->lastAgendaDate = $value;
  }

  /**
   * Setups agenda conditions.
   */
  protected function setupAgenda() {
    $next_day = clone $this->getCurrentDate();
    // Build agenda for the current date.
    $next_day->modify('+1 day');
    $this->setCurrentItems($this->buildAgenda($this->getCurrentDate(), $next_day));
    $this->setLastAgendaDate($next_day);
    $this->findUpcomingItems();
    // We don't need navigation for the blocks.
    if (!$this->getIsBlock()) {
      $this->findPreviousDate();
      $this->findUpcomingDate();
    }
  }

  /**
   * Adds date url parts.
   *
   * @param object $date
   *   The current date.
   */
  protected function setUrlItems($date) {
    if ($date) {
      $this->addUrlPart($date->format('j'));
      $this->addUrlPart($date->format('n'));
      $this->addUrlPart($date->format('Y'));
    }
  }

  /**
   * Finds and sets upcoming items.
   */
  protected function findUpcomingItems() {
    $start_date = clone $this->getCurrentDate();
    // We start from the next day after the current.
    $start_date->modify('+1 day');
    $this->setLastAgendaDate($start_date);
    $upcoming_items = [];
    // We add one day to include the last day also.
    $last_event_date = $this->getUtmostDate(FALSE);
    if ($last_event_date) {
      $last_event_date->modify('+1 day');
      $number_to_display = $this->getItemsNumber();
      while ($this->getItemsCount() < $number_to_display && $start_date <= $last_event_date) {
        $next_day = clone $start_date;
        $next_day->modify('+1 day');
        $current_items = $this->buildAgenda($start_date, $next_day, FALSE);
        $upcoming_items = array_merge($upcoming_items, $current_items);
        $this->setLastAgendaDate($start_date);
        $start_date->modify('+1 day');
      }
    }
    $this->setUpcomingItems($upcoming_items);
  }

  /**
   * Checks agenda items for existence of events.
   *
   * @param array $items
   *   Agenda items.
   *
   * @return bool
   *   Has events.
   */
  protected function hasItems($items) {
    $has_current_items = FALSE;
    if ($items) {
      foreach ($items as $item) {
        if (!empty($item->getItems())) {
          $has_current_items = TRUE;
          break;
        }
      }
    }
    return $has_current_items;
  }

  /**
   * Finds and set upcoming date.
   */
  protected function findUpcomingDate() {
    $cache_key = 'get_agenda:upcoming_date:' . $this->getUniqueCachePart();

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $upcoming_date = $cache->data;
    }
    else {
      $upcoming_date = NULL;
      // We start from the latest item of the agenda on the current page.
      $last_agenda_date = $this->getLastAgendaDate();
      // We add one day to include the last day also.
      $last_event_date = $this->getUtmostDate(FALSE);
      if ($last_agenda_date && $last_event_date) {
        // We start from the next day after the current.
        $current_date = clone $last_agenda_date;
        $last_event_date->modify('+1 day');
        while ($current_date <= $last_event_date) {
          $next_day_date = clone $current_date;
          $next_day_date->modify('+1 day');
          $upcoming_items = $this->buildAgenda($current_date, $next_day_date);
          if ($this->hasItems($upcoming_items)) {
            $upcoming_date = $current_date;
            break;
          }

          $current_date->modify('+1 day');
        }
      }
      cache_set($cache_key, $upcoming_date, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_upcoming_date', 3600));
    }

    $this->setUpcomingDate($upcoming_date);
  }

  /**
   * Finds and sets previous available date.
   */
  protected function findPreviousDate() {
    $cache_key = 'get_agenda:previous_date:' . $this->getUniqueCachePart();

    if ($cache = cache_get($cache_key, NEXTEUROPA_NEWSROOM_CACHE_TABLE)) {
      $previous_date = $cache->data;
    }
    else {
      $current_date = clone $this->getCurrentDate();
      $first_event_date = $this->getUtmostDate();
      $previous_date = NULL;
      if ($first_event_date) {
        while ($current_date > $first_event_date) {
          $day_before = clone $current_date;
          $day_before->modify('-1 day');
          // Build agenda for the previous date and check do we have any items.
          $previous_items = $this->buildAgenda($day_before, $current_date);
          if ($this->hasItems($previous_items)) {
            $previous_date = $day_before;
            break;
          }

          $current_date->modify('-1 day');
        }
      }
      cache_set($cache_key, $previous_date, NEXTEUROPA_NEWSROOM_CACHE_TABLE, time() + variable_get('newsroom_ct_previous_date', 3600));
    }

    $this->setPreviousDate($previous_date);
  }

  /**
   * Loads result from the current query.
   *
   * @return array
   *   Result.
   */
  protected function loadResult() {
    return $this->getQuery()->execute()->fetchAll();
  }

  /**
   * Gets utmost date.
   *
   * @param bool $first
   *   Return the first or last utmost date in the result.
   *
   * @return object
   *   Utmost date.
   */
  protected function getUtmostDate($first = TRUE) {
    $utmost_date = NULL;
    $result = $this->getResult();
    if ($result) {
      $last_item = $first ? reset($result) : array_pop($result);
      if ($last_item) {
        $utmost_date = clone $last_item->start_date_obj;
      }
    }
    return $utmost_date;
  }

}
