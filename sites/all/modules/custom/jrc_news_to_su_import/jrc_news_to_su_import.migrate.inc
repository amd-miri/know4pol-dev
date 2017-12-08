<?php

/**
 * @file
 * Migration of all no-highlighted News to Scince Update content type.
 */

/**
 * Implements hook_migrate_api().
 */
function jrc_news_to_su_import_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'news_science_updates' => array(
        'title' => t('Import no-hightlighted news to Science updates'),
      ),
    ),
    'migrations' => array(
      'NewsScienceUpdates' => array(
        'class_name' => 'JrcNewsToSuImportMigration',
        'group_name' => 'news_science_updates',
      ),
    ),
  );
  return $api;
}

/**
 * Migration of the Copyright field content.
 */
class JrcNewsToSuImportMigration extends Migration {

  /**
   * Class construct function.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('No-Highlighted News to Science updates Migration');
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'node ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Source fields available.
    $fields = array(
      'migrate_redirects' => t('Redirects'),
      'body' => t('Body'),
      'body_summary' => t('Body summary'),
      'field_identities' => t('Identities'),
      'field_image' => t('Image'),
      'field_institutes' => t('Institutes'),
      'field_last_update' => t('Last update'),
      'field_last_update_timezone' => t('Last update timezone'),
      'field_meta_creator' => t('Meta creator'),
      'field_mk' => t('Meta keywords'),
      'field_news_date' => t('News date'),
      'field_news_date_timezone' => t('News date timezone'),
      'field_news_publication_date' => t('News publication date'),
      'field_related_content' => t('Related content'),
      'field_related_documents' => t('Related documents'),
      'field_related_topics' => t('Related topics'),
      'field_research_areas' => t('Research areas'),
      'field_short_title' => t('Short title'),
      'field_tags' => t('Tags'),
      'group_content_access' => t('Group content access'),
      'og_group_ref' => t('OG group reference'),
    );

    $query = db_select('node', 'n')
      ->fields('n')
      ->condition('n.type', 'news', '=')
      ->orderBy('nid', 'ASC');

    $query->Join('field_data_field_highlighted', 'h', 'n.nid=h.entity_id');
    $query->condition('field_highlighted_tid', '1908', '=');

    $this->source = new MigrateSourceSQL($query, $fields);
    $this->destination = new MigrateDestinationNode('science_updates');

    // Map fields.
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'changed');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('promote', 'promote')->defaultValue(0);
    $this->addFieldMapping('sticky', 'sticky')->defaultValue(0);
    $this->addFieldMapping('revision')->defaultValue(1);
    $this->addFieldMapping('language')->defaultValue('en');
    $this->addFieldMapping('revision_uid')->defaultValue(1);
    $this->addFieldMapping('is_new')->defaultValue(1);
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:summary', 'body_summary');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_identities', 'field_identities');
    $this->addFieldMapping('field_identities:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_image', 'field_image');
    $this->addFieldMapping('field_image:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_institutes', 'field_institutes');
    $this->addFieldMapping('field_institutes:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_last_update', 'field_last_update');
    $this->addFieldMapping('field_last_update:timezone', 'field_last_update_timezone');
    $this->addFieldMapping('field_meta_creator', 'field_meta_creator');
    $this->addFieldMapping('field_mk', 'field_mk');
    $this->addFieldMapping('field_news_date', 'field_news_date');
    $this->addFieldMapping('field_news_date:timezone', 'field_news_date_timezone');
    $this->addFieldMapping('field_news_publication_date', 'field_news_publication_date');
    $this->addFieldMapping('field_related_content', 'field_related_content');
    $this->addFieldMapping('field_related_content:format')->defaultValue("full_html");
    $this->addFieldMapping('field_related_documents', 'field_related_documents');
    $this->addFieldMapping('field_related_documents:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_related_topics', 'field_related_topics');
    $this->addFieldMapping('field_research_areas', 'field_research_areas');
    $this->addFieldMapping('field_research_areas:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_short_title', 'field_short_title');
    $this->addFieldMapping('field_tags', 'field_tags');
    $this->addFieldMapping('field_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('group_content_access', 'group_content_access');
    $this->addFieldMapping('og_group_ref', 'og_group_ref');
    $this->addFieldMapping('workbench_moderation_state_new')->defaultValue('published');
    $this->addFieldMapping('migrate_redirects', 'migrate_redirects');
    $this->addFieldMapping('migrate_redirects_language')->defaultValue('en');
  }

  /**
   * Class prepareRow function.
   */
  public function prepareRow($row) {
    $node = node_load($row->nid);

    if ($node->body[LANGUAGE_NONE] != NULL) {
      $row->body = $node->body[LANGUAGE_NONE][0]['value'];
      $row->body_summary = $node->body[LANGUAGE_NONE][0]['summary'];
    }
    if ($node->field_identities[LANGUAGE_NONE] != NULL) {
      $row->field_identities = array_column($node->field_identities[LANGUAGE_NONE], 'tid');
    }
    $row->field_image = $node->field_image[LANGUAGE_NONE][0]['fid'];
    if ($node->field_institutes[LANGUAGE_NONE] != NULL) {
      $row->field_institutes = array_column($node->field_institutes[LANGUAGE_NONE], 'tid');
    }
    $row->field_last_update = strtotime($node->field_last_update[LANGUAGE_NONE][0]['value']);
    $row->field_last_update_timezone = $node->field_last_update[LANGUAGE_NONE][0]['timezone'];
    if ($node->field_meta_creator[LANGUAGE_NONE] != NULL) {
      $row->field_meta_creator = $node->field_meta_creator[LANGUAGE_NONE][0]['value'];
    }
    if ($node->field_mk[LANGUAGE_NONE] != NULL) {
      $row->field_mk = $node->field_mk[LANGUAGE_NONE][0]['value'];
    }
    $row->field_news_date = strtotime($node->field_news_date[LANGUAGE_NONE][0]['value']);
    $row->field_news_date_timezone = $node->field_news_date[LANGUAGE_NONE][0]['timezone'];
    if ($node->field_news_publication_date[LANGUAGE_NONE] != NULL) {
      $row->field_news_publication_date = $node->field_news_publication_date[LANGUAGE_NONE][0]['value'];
    }
    if ($node->field_related_content[LANGUAGE_NONE] != NULL) {
      $row->field_related_content = $node->field_related_content[LANGUAGE_NONE][0]['value'];
    }
    if ($node->field_related_documents[LANGUAGE_NONE] != NULL) {
      $row->field_related_documents = array_column($node->field_related_documents[LANGUAGE_NONE], 'fid');
    }
    if ($node->field_related_topics[LANGUAGE_NONE] != NULL) {
      $row->field_related_topics = array_column($node->field_related_topics[LANGUAGE_NONE], 'target_id');
    }
    if ($node->field_research_areas[LANGUAGE_NONE] != NULL) {
      $row->field_research_areas = array_column($node->field_research_areas[LANGUAGE_NONE], 'tid');
    }
    if ($node->field_short_title[LANGUAGE_NONE] != NULL) {
      $row->field_short_title = $node->field_short_title[LANGUAGE_NONE][0]['value'];
    }
    else {
      $row->field_short_title = $node->title;
    }
    if ($node->field_tags[LANGUAGE_NONE] != NULL) {
      $row->field_tags = array_column($node->field_tags[LANGUAGE_NONE], 'tid');
    }
    if ($node->group_content_access[LANGUAGE_NONE] != NULL) {
      $row->group_content_access = $node->group_content_access[LANGUAGE_NONE][0]['value'];
    }
    if ($node->og_group_ref[LANGUAGE_NONE] != NULL) {
      $row->og_group_ref = array_column($node->og_group_ref[LANGUAGE_NONE], 'gid');
    }
    if ($node->path['alias'] != NULL) {
      $row->migrate_redirects = $node->path['alias'];
    }
  }

}
