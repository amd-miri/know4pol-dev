<?php

class WorkbenchModerationMigrateDestinationHandler extends MigrateDestinationHandler {

  public function __construct() {
    $this->registerTypes(array('node'));
  }

  /**
   * Implements MigrationDestinationHandler::fields().
   */
  public function fields($entity_type, $bundle_type) {
    $fields = array();
    if (workbench_moderation_node_type_moderated($bundle_type)) {
      $fields['workbench_moderation_state_new'] = t('Moderation state');
    }
    return $fields;
  }

  /**
   * Implements MigrationDestinationHandler::prepare().
   */
  public function prepare($entity, $row) {
    // Prevents workbench_moderation_moderate from being called, which would
    // result in every node being resaved at shutdown time. We will do the
    // necessary history record writing in complete().
    if (workbench_moderation_node_type_moderated($entity->type)) {
      $entity->revision = FALSE;

      if (isset($entity->workbench_moderation_state_new)) {
        $entity->workbench_moderation_state_current =
          $entity->workbench_moderation_state_new;
      }
    }
  }

  /**
   * Implements MigrationDestinationHandler::complete().
   */
  public function complete($entity, $row) {
    if (workbench_moderation_node_type_moderated($entity->type)) {
      workbench_moderation_save_history($entity,
        $entity->workbench_moderation_state_new,
        $entity->workbench_moderation['my_revision']->state);
    }
  }
}

/**
 * Implements hook_migrate_api().
 */
function workbench_moderation_migrate_api() {
  return array(
    'api' => 2,
    'destination handlers' => array('WorkbenchModerationMigrateDestinationHandler'),
  );
}
