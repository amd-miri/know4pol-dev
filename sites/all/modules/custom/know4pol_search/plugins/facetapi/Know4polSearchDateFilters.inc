<?php

/**
 * @file
 * The core Facetapi widget list for OG vocab.
 */

/**
 * Facetapi widget that allows filtering by date (before / after).
 */
class Know4polSearchDateFilters extends FacetapiWidget {

  /**
   *
   */
  public function __construct($id, array $realm, FacetapiFacet $facet, stdClass $settings) {
    parent::__construct($id, $realm, $facet, $settings);
  }

  /**
   *
   */
  private function getDatesFromats() {
    $formats = array();
    foreach (system_get_date_types() as $key => $value) {
      $formats[$value['title']] = array();
      $formats[$value['title']][$key] = variable_get('date_format_' . $key);
    }
    return $formats;
  }

  /**
   * Overrides FacetapiWidget::settingsForm().
   */
  public function settingsForm(&$form, &$form_state) {
    $form['widget']['widget_settings'][$this->id]['datepicker'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display as date picker'),
      '#default_value' => !empty($this->settings->settings['datepicker']),
      '#description' => t('Uses ECL component Datepickers.'),

    );

    $form['widget']['widget_settings'][$this->id]['dateformat'] = array(
      '#type' => 'select',
      '#title' => t('Date formatter'),
      '#default_value' => $this->settings->settings['dateformat'],
      '#options' => $this->getDatesFromats(),
      '#description' => t('Limits the number of displayed facets via JavaScript.'),
      '#states' => array(
        'visible' => array(
          'select[name="widget"]' => array('value' => $this->id),
        ),
      ),
    );
  }

  /**
   * Overrides FacetapiWidget::getDefaultSettings().
   */
  public function getDefaultSettings() {
    return array(
      'soft_limit' => 20,
      'nofollow' => 1,
      'show_expanded' => 0,
    );
  }

  /**
   * Implements FacetapiWidget::execute().
   *
   * Transforms the render array into something that can be themed by
   * theme_item_list().
   *
   * @see FacetapiWidgetLinks::setThemeHooks()
   * @see FacetapiWidgetLinks::buildListItems()
   */
  public function execute() {

  }

  /**
   *
   */
  public function init() {
    // Capture searcher for code readability.
    $searcher = $this->facet->getAdapter()->getSearcher();

    // Initialize the render array.
    $this->build = array(
      '#title' => $this->facet['label'],
      '#description' => $this->facet['description'],
      '#weight' => $this->facet['weight'],
      '#adapter' => $this->facet->getAdapter(),
      '#realm_name' => $this->realm['name'],
      '#facet' => $this->facet->getFacet(),
      '#settings' => $this->settings,
      $this->facet['field alias'] => $this->facet->getBuild(),
      '#attributes' => array(
        'class' => array(
          drupal_html_class("facetapi-" . $this->id),
          drupal_html_class("facetapi-facet-{$this->facet['name']}"),
        ),
        'id' => drupal_html_id("facetapi-facet-$searcher-{$this->realm['name']}-{$this->facet['name']}"),
      ),

    );

    // Apply sorting algorithms to the render array.
    $this->sortFacet($this->build);

    return $this;
  }

}
