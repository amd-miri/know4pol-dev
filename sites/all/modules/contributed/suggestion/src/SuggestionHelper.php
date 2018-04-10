<?php

/**
 * @file
 * Helper methods for the suggestion module.
 */

/**
 * Provides helper methods for suggestions.
 */
class SuggestionHelper {
  const C = 8;
  const MAX = 100;
  const MIN = 2;
  const EXP = 0.5;

  /**
   * Transform a string to an array.
   *
   * @param string $txt
   *   The string to process.
   *
   * @return array
   *   An array of atoms.
   */
  public static function atomize($txt = '') {
    $atoms = array();
    $stopwords = self::getStops('stopwords');

    foreach (preg_split('/\s+/', $txt) as $atom) {
      if (!empty($stopwords[$atom])) {
        continue;
      }
      $atoms[$atom] = $atom;
    }
    return $atoms;
  }

  /**
   * Calculate the ngram's density.
   *
   * @param int $src
   *   The ngram source.
   * @param int $atoms
   *   The number of atoms in the ngram.
   * @param int $qty
   *   The submission count.
   *
   * @return float
   *   The suggestion's score.
   */
  public static function calculateDensity($src = 0, $atoms = 1, $qty = 0) {
    $score = intval($src) * self::C;

    return (float) $score + self::getDelta((self::MAX - $score), intval(pow(($atoms + $qty), self::EXP)));
  }

  /**
   * Stopword get wrapper.
   *
   * @return mixed
   *   The value of the supplied field.
   */
  public static function getStops() {
    $stopwords = &drupal_static(__CLASS__ . '_' . __FUNCTION__, NULL);

    if (is_array($stopwords)) {
      return $stopwords;
    }
    $file_path = drupal_realpath(variable_get('suggestion_stopword_uri', file_default_scheme() . '://suggestion/suggestion_stopword.txt'));

    $stopwords = file_get_contents($file_path);
    $stopwords = array_fill_keys(preg_split('/\s*[\n\r]+\s*/s', $stopwords), 1);

    return $stopwords;
  }

  /**
   * Create a suggestion index from content titles.
   *
   * @param int $last_nid
   *   The last node ID processed.
   * @param int $limit
   *   The query limit.
   */
  public static function index($last_nid = 0, $limit = NULL) {
    $count = &drupal_static(__CLASS__ . '_' . __FUNCTION__ . '_count', 0);
    $nid = &drupal_static(__CLASS__ . '_' . __FUNCTION__ . '_nid', 0);

    variable_set('suggestion_synced', TRUE);

    if (!$last_nid) {
      SuggestionStorage::deleteContentSuggestion();
      SuggestionStorage::updateContentSrc();
    }
    $titles = SuggestionStorage::getTitles($last_nid, $limit);

    foreach ($titles as $nid => $title) {
      $count += self::insert($title, SuggestionStorage::CONTENT_BIT);
    }
  }

  /**
   * Add a suggestion.
   *
   * @param string $txt
   *   The title to index.
   * @param int $src
   *   The bits to OR with the current bitmap.
   * @param int $qty
   *   Default quantity.
   *
   * @return int
   *   The number of suggestions inserted.
   */
  public static function insert($txt = '', $src = SuggestionStorage::CONTENT_BIT, $qty = NULL) {
    $count = 0;
    $max = variable_get('suggestion_max', 45);
    $txt = self::tokenize($txt, variable_get('suggestion_min', 4));

    if (!$txt) {
      return 0;
    }
    $atoms = self::atomize($txt);

    foreach (array_keys(self::ngrams($atoms)) as $ngram) {
      if (strlen($ngram) > $max) {
        continue;
      }
      $count = str_word_count($ngram);
      $qty = is_numeric($qty) ? $qty + 1 : SuggestionStorage::getNgramQty($ngram) + 1;
      $src = SuggestionStorage::getBitmap($ngram, $src);

      $key = array('ngram' => $ngram);
      $fields = array(
        'atoms'   => $count,
        'density' => self::calculateDensity($src, $count, $qty),
        'qty'     => $qty,
        'src'     => $src,
      );
      SuggestionStorage::mergeSuggestion($key, $fields);

      $count++;
    }
    return $count;
  }

  /**
   * Build a set of ngrams from the set of atoms.
   *
   * @param array $atoms
   *   An array of strings.
   *
   * @return array
   *   An array of ngrams keys.
   */
  public static function ngrams(array $atoms = array()) {
    $count = count($atoms);
    $max = variable_get('suggestion_atoms', 6);
    $ngrams = array();

    for ($i = 0; $i < $count; $i++) {
      for ($j = 1; $j <= $max; $j++) {
        $ngrams[implode(' ', array_slice($atoms, $i, $j))] = 1;
      }
    }
    $atoms = array_reverse($atoms);

    for ($i = 0; $i < $count; $i++) {
      for ($j = 1; $j <= $max; $j++) {
        $ngrams[implode(' ', array_slice($atoms, $i, $j))] = 1;
      }
    }
    return $ngrams;
  }

  /**
   * Convert an array of submitted form options to a bitmap.
   *
   * @param array $bits
   *   An array of form options.
   *
   * @return int
   *   The option values bitwise OR.
   */
  public static function optionBits(array $bits = array()) {
    $src = 0;

    foreach ($bits as $bit) {
      $src |= intval($bit);
    }
    return $src;
  }

  /**
   * Build an array of defalut options from bitmaps.
   *
   * @param int $src
   *   The ngrams source bitmap.
   *
   * @return array
   *   An array of default option.
   */
  public static function srcBits($src = 0) {
    $bits = array();

    if (intval($src) <= 0) {
      return array(0);
    }
    foreach (array_keys(SuggestionStorage::getSrcOptions()) as $bit) {
      if ($bit & $src) {
        $bits[] = $bit;
      }
    }
    return $bits;
  }

  /**
   * Tokenize the text into space separated lowercase strings.
   *
   * @param string $txt
   *   The text to process.
   * @param int $min
   *   The minimum number of characters in a token.
   *
   * @return string
   *   The tokenized string.
   */
  public static function tokenize($txt = '', $min = 4) {
    $min--;

    $regx = array(
      '/[^a-z]+/s'                  => ' ',
      '/\b(\w{1,' . $min . '})\b/s' => '',
      '/\s\s+/s'                    => ' ',
      '/^\s+|\s+$/s'                => '',
    );
    return preg_replace(array_keys($regx), array_values($regx), strtolower(trim($txt)));
  }

  /**
   * Build an array of content types used in auto-complete.
   *
   * @return array
   *   An array of enabled content types.
   */
  public static function types() {
    $types = &drupal_static(__CLASS__ . '_' . __FUNCTION__, NULL);

    if (is_array($types)) {
      return $types;
    }
    foreach (variable_get('suggestion_types', array()) as $type => $status) {
      if ($status) {
        $types[] = $type;
      }
    }
    return $types ? $types : array();
  }

  /**
   * Calculate the ngram's density.
   *
   * @param string $ngram
   *   The ngram to update.
   * @param int $src
   *   The ngram source.
   *
   * @return object
   *   A Merge object.
   */
  public static function updateSrc($ngram = '', $src = 0) {
    $obj = SuggestionStorage::getSuggestion($ngram);

    $key = array('ngram' => $ngram);
    $fields = array(
      'atoms'   => $obj->atoms,
      'density' => self::calculateDensity($src, $obj->atoms, $obj->qty),
      'qty'     => $obj->qty,
      'src'     => $src,
    );
    return SuggestionStorage::mergeSuggestion($key, $fields);
  }

  /**
   * Estimate the performance.
   *
   * @param float $delta
   *   The current performance remainder.
   * @param int $n
   *   The summation N - 1.
   *
   * @return float
   *   The suggestion's remainder summation.
   */
  protected static function getDelta($delta, $n) {
    if ($delta < self::MIN || !$n) {
      return 0;
    }
    $x = pow($delta, self::EXP);

    return $x + self::getDelta(($delta - $x), ($n - 1));
  }

}
