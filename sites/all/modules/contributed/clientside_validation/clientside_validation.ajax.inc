<?php

/**
 * Check that a path is valid and accessible for internal and aliased paths, also if the path is an
 * external url, it is validated according to RFC 2396.
 *
 * @param $path
 *   The path to check is valid.
 */
function _clientside_validation_url_validation_callback() {
  $path = $_POST['value'];
  $result = array();
  $result['result'] = FALSE;

  // Check if the url is valid according to RFC 2396.
  if (filter_var($path, FILTER_VALIDATE_URL)) {
    $result['result'] = TRUE;
  }

  // If we have an internal URL, strip out the query string and fragment
  // before attempting to validate the URL.
  if (!url_is_external($path)) {
    $parsed_path = parse_url($path);
    if (isset($parsed_path['query'])) {
      $query = drupal_get_query_array($parsed_path['query']);
    }
    if (isset($parsed_path['fragment'])) {
      $fragment = $parsed_path['fragment'];
    }
    if ($path != $parsed_path['path']) {
      $path = $parsed_path['path'];
    }
  }

  // Checks a path exists and the current user has access to it.
  if (trim($path) && drupal_valid_path($path)) {
    $result['result'] = TRUE;
  }
  else {
    // Check if the aliased path, exists and the current user has access to it.
    $lookup_path = drupal_lookup_path('source', $path);
    if (drupal_valid_path($lookup_path)) {
      $result['result'] = TRUE;
    }
  }

  drupal_json_output($result);
}
