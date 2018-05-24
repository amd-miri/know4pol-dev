<?php

/**
 * @file
 * Provides a controller for CacheFlushEntity CRUD functionality.
 */

/**
 * Main class for cacheflush entities.
 */
class CacheFlushEntity extends Entity {

  /**
   * Creates a default Cacheflush object.
   *
   * @see Entity::__construct()
   */
  public function __construct(array $values = array(), $entity_type = NULL) {
    parent::__construct($values, 'cacheflush');
  }

  /**
   * Permanently saves the entity.
   *
   * @see entity_save()
   */
  public function save() {

    // In case created timestamp is missing we create it.
    if (!isset($this->created) || empty($this->created)) {
      $this->created = REQUEST_TIME;
    }

    // We always save timestamp of last action.
    $this->changed = REQUEST_TIME;
    return entity_get_controller($this->entityType)->save($this);
  }

}

/**
 * A controller extending EntityAPIController.
 */
class CacheFlushEntityAPIController extends EntityAPIController {

  /**
   * Override EntityAPIController:create().
   */
  public function create(array $values = array()) {
    global $user;
    // Add is_new property if it is not set.
    $values += array('is_new' => TRUE, 'uid' => $user->uid, 'title' => NULL);
    if (isset($this->entityInfo['entity class']) && $class = $this->entityInfo['entity class']) {
      return new $class($values, $this->entityType);
    }
    return (object) $values;
  }

}
