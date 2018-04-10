<?php

/**
 * @file
 * CRUD methods for the suggestion module.
 */

/**
 * Database CRUD.
 */
class SuggestionStorage {

  // Source bitmaps.
  const CONTENT_BIT = 1;
  const DISABLED_BIT = 0;
  const PRIORITY_BIT = 4;
  const SURFER_BIT = 2;

  /**
   * Delete all content suggestions.
   *
   * @return object
   *   A Delete object.
   */
  public static function deleteContentSuggestion() {
    return db_delete('suggestion')->condition('src', self::CONTENT_BIT)->execute();
  }

  /**
   * Fetch all the suggestions.
   *
   * @param int $start
   *   The starting offset.
   * @param int $limit
   *   The query limit.
   *
   * @return array
   *   An array of suggestion objects.
   */
  public static function getAllSuggestions($start = NULL, $limit = 100) {
    if (is_numeric($start) && intval($limit)) {
      return db_query_range("SELECT * FROM {suggestion} ORDER BY ngram ASC", $start, $limit)->fetchAll();
    }
    return db_query("SELECT * FROM {suggestion} ORDER BY ngram ASC")->fetchAll();
  }

  /**
   * Fetch a set of suggestions.
   *
   * @param string $ngram
   *   The search string.
   * @param int $atoms
   *   The number of atoms.
   * @param int $limit
   *   The query limit.
   *
   * @return array
   *   An array of suggestions.
   */
  public static function getAutocomplete($ngram = '', $atoms = 0, $limit = 100) {
    $args = array(
      ':ngram' => $ngram,
      ':atoms' => (int) $atoms,
    );
    $stmt = "
      SELECT
        ngram,
        ngram
      FROM
        {suggestion}
      WHERE
        ngram LIKE :ngram
        AND src
        AND atoms <= :atoms
      ORDER BY
        density DESC,
        ngram ASC,
        atoms ASC
    ";
    return db_query_range($stmt, 0, (int) $limit, $args)->fetchAllKeyed();
  }

  /**
   * Calculate the suggestion's bitmap.
   *
   * @param string $ngram
   *   The text to index.
   * @param int $src
   *   The bits to OR with the current bitmap.
   *
   * @return int
   *   The new bitmap value.
   */
  public static function getBitmap($ngram = '', $src = self::CONTENT_BIT) {
    $args = array(
      ':ngram' => $ngram,
      ':src'   => (int) $src,
    );
    return db_query("SELECT IFNULL(SUM(src), 0) | :src FROM {suggestion} WHERE ngram = :ngram", $args)->fetchField();
  }

  /**
   * Fetch an array of content types.
   *
   * @return array
   *   An array of content types.
   */
  public static function getContentTypes() {
    return db_query("SELECT type, name FROM {node_type} ORDER BY name ASC, type ASC")->fetchAllKeyed();
  }

  /**
   * Fetch the row count.
   *
   * @param string $ngram
   *   The text to search for.
   *
   * @return int
   *   The number of rows in the suggestion table.
   */
  public static function getCount($ngram = '') {
    if ($ngram) {
      return db_query("SELECT COUNT(*) FROM {suggestion} WHERE ngram LIKE :ngram", array(':ngram' => $ngram))->fetchField();
    }
    return db_query("SELECT COUNT(*) FROM {suggestion}")->fetchField();
  }

  /**
   * Fetch an array of priority suggestions.
   *
   * @return array
   *   An array of suggestions.
   */
  public static function getKeywords() {
    return db_query("SELECT ngram FROM {suggestion} WHERE src & :src ORDER BY ngram ASC", array(':src' => self::PRIORITY_BIT))->fetchCol();
  }

  /**
   * Fetch the quantity for the supplied ngram.
   *
   * @param string $ngram
   *   The ngram value.
   *
   * @return int
   *   The qty value for the supplied ngram.
   */
  public static function getNgramQty($ngram = '') {
    return db_query("SELECT IFNULL(SUM(qty), 0) FROM {suggestion} WHERE ngram = :ngram", array(':ngram' => $ngram))->fetchField();
  }

  /**
   * Calculate a suggestion's score.
   *
   * @param array $atoms
   *   An array of strings.
   *
   * @return int
   *   The suggestion's score.
   */
  public static function getScore(array $atoms = array()) {
    $types = SuggestionHelper::types();

    if (!count($types)) {
      return 0;
    }
    $query = db_select('field_data_body', 'b');

    $query->fields('b', array('entity_id'));
    $query->join('node', 'n', 'n.nid = b.entity_id');
    $query->condition('n.status', 1);
    $query->condition('n.type', $types, 'IN');

    foreach ($atoms as $atom) {
      $query->condition('b.body_value', '%' . db_like($atom) . '%', 'LIKE');
    }
    return $query->execute()->rowCount();
  }

  /**
   * Build an array of source options.
   *
   * @return array
   *   An array of source options.
   */
  public static function getSrcOptions() {
    return array(
      self::DISABLED_BIT => t('Disabled'),
      self::CONTENT_BIT  => t('Content'),
      self::SURFER_BIT   => t('Surfer'),
      self::PRIORITY_BIT => t('Priority'),
    );
  }

  /**
   * Fetch the data for the suplied ngram.
   *
   * @param string $ngram
   *   The requested ngram.
   *
   * @return object
   *   An array of suggestion objects.
   */
  public static function getSuggestion($ngram = '') {
    return db_query("SELECT * FROM {suggestion} WHERE ngram = :ngram", array(':ngram' => $ngram))->fetchObject();
  }

  /**
   * Fetch an array of node titles.
   *
   * @param int $nid
   *   The Node ID of the last node batched.
   * @param int $limit
   *   The query limit.
   *
   * @return array
   *   A node ID to title hash.
   */
  public static function getTitles($nid = 0, $limit = NULL) {
    $args = array(
      ':nid'   => (int) $nid,
      ':types' => SuggestionHelper::types(),
    );
    if (!count($args[':types'])) {
      return array();
    }
    $stmt = "
      SELECT
        nid,
        title
      FROM
        {node}
      WHERE
        status = 1
        AND nid > :nid
        AND type IN (:types)
      ORDER BY
        nid ASC
    ";
    if (is_numeric($limit)) {
      return db_query_range($stmt, 0, $limit, $args)->fetchAllKeyed();
    }
    return db_query($stmt, $args)->fetchAllKeyed();
  }

  /**
   * Merge the supplied suggestion.
   *
   * @param array $key
   *   The suggestion key array.
   * @param array $fields
   *   The suggestion field array.
   *
   * @return object
   *   A Merge object.
   */
  public static function mergeSuggestion(array $key = array(), array $fields = array()) {
    return db_merge('suggestion')->key($key)->fields($fields)->execute();
  }

  /**
   * Search suggestions.
   *
   * @param string $ngram
   *   The requested ngram.
   * @param int $start
   *   The starting offset.
   * @param int $limit
   *   The query limit.
   *
   * @return array
   *   An array of suggestion objects.
   */
  public static function search($ngram, $start = NULL, $limit = 100) {
    $args = array(':ngram' => $ngram);

    if (is_numeric($start) && intval($limit)) {
      return db_query_range("SELECT * FROM {suggestion} WHERE ngram LIKE :ngram ORDER BY ngram ASC", $start, $limit, $args)->fetchAll();
    }
    return db_query("SELECT * FROM {suggestion} WHERE ngram LIKE :ngram ORDER BY ngram ASC", $args)->fetchAll();
  }

  /**
   * Truncate the suggestion table.
   *
   * @return object
   *   A new TruncateQuery object for this connection.
   */
  public static function truncateSuggestion() {
    return db_truncate('suggestion')->execute();
  }

  /**
   * Remove the content bit from the source bitmap.
   *
   * @return object
   *   An Update object.
   */
  public static function updateContentSrc() {
    return db_update('suggestion')
      ->expression('src', 'src & :src', array(':src' => intval(self::PRIORITY_BIT | self::SURFER_BIT)))
      ->condition('src', self::CONTENT_BIT, '&')
      ->execute();
  }

}
