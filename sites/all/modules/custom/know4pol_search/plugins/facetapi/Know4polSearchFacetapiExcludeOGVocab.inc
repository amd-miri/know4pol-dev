<?php

/**
 * @file
 * Filter to exclude specified facet items from being shown on the facet.
 *
 * This is heavily inspired by the excellent blog post from Trellon
 * http://www.trellon.com/content/blog/apachesolr-and-facetapi.
 */

/**
 * Plugin that excludes specified facet items.
 */
class Know4polSearchFacetapiExcludeOGVocab extends FacetapiFilter {

  /**
   * Filters facet items.
   */
  public function execute(array $build) {
    $remove = explode(PHP_EOL, $this->settings->settings['exclude_vmn']);
    $result_build = array();

    foreach ($build as &$item) {
      $term = _know4pol_search_facetapi_load_term($item);
      // Term vid not in the list of excuded vocab ?
      if (!in_array($term->vocabulary_machine_name, $remove)) {
        $result_build[] = $item;
      }
    }
    return $result_build;
  }

  /**
   * Adds settings to the filter form.
   */
  public function settingsForm(&$form, &$form_state) {
    $form['exclude_vmn'] = array(
      '#title' => t('Exclude terms that belong to those (OG) vocabularies'),
      '#type' => 'textarea',
      '#description' => t("Machine_name list of vocavularies to hide. One per line"),
      '#default_value' => $this->settings->settings['exclude_vmn'],
    );
  }

  /**
   * Returns an array of default settings.
   */
  public function getDefaultSettings() {
    return array(
      'exclude_vmn' => '',
    );
  }

}
