<?php

/**
 * @file
 * The core Facetapi widget list for OG vocab.
 */

/**
 * Facetapi widget that renders facets as list with OG vocab name.
 */
class Know4polSearchFacetapiWidgetOGVocab extends FacetapiWidgetCheckboxLinks {

  /**
   * Overrides FacetapiWidget::__construct().
   */
  public function __construct($id, array $realm, FacetapiFacet $facet, stdClass $settings) {
    parent::__construct($id, $realm, $facet, $settings);
    $this->key = $facet['name'];
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
    $element = &$this->build[$this->facet['field alias']];
    // Sets each item's theme hook, builds item list.
    $this->setThemeHooks($element);
    $items = $this->buildListItems($element);
    $element = array(
      // If items are still in the list theme it.
      '#theme' => (count($items) ? 'item_list' : NULL),
      '#items' => $items,
      '#attributes' => $this->build['#attributes'],
    );
  }

  /**
   * Transforms the render array for use with theme_item_list().
   *
   * The recursion allows this function to act on the various levels of a
   * hierarchical data set.
   *
   * @see FacetapiWidgetLinks::buildListItems()
   */
  public function buildListItems($build) {
    $settings = $this->settings->settings;
    // Initializes links attributes, adds rel="nofollow" if configured.
    $attributes = ($settings['nofollow']) ? array('rel' => 'nofollow') : array();
    $attributes += array('class' => $this->getItemClasses());

    // Builds rows.
    $items = array();
    $last_vid = NULL;
    $vid_enable = array();

    foreach ($build as &$item) {
      $row = array('class' => array());

      // Allow adding classes via altering.
      if (isset($item['#class'])) {
        $attributes['class'] = array_merge($attributes['class'], $item['#class']);
      }
      // Initializes variables passed to theme hook.
      $variables = array(
        'text' => $item['#markup'],
        'path' => $item['#path'],
        'count' => $item['#count'],
        'options' => array(
          'attributes' => $attributes,
          'html' => $item['#html'],
          'query' => $item['#query'],
        ),
      );

      // Adds the facetapi-zero-results class to items that have no results.
      if (!$item['#count']) {
        $variables['options']['attributes']['class'][] = 'facetapi-zero-results';
      }

      // Add an ID to identify this link.
      $variables['options']['attributes']['id'] = drupal_html_id('facetapi-link');

      // If the item has no children, it is a leaf.
      if (empty($item['#item_children'])) {
        $row['class'][] = 'leaf';
      }
      else {
        // If the item is active or the "show_expanded" setting is selected,
        // show this item as expanded so we see its children.
        if ($item['#active'] || !empty($settings['show_expanded'])) {
          $row['class'][] = 'expanded';
          $row['children'] = $this->buildListItems($item['#item_children']);
        }
        else {
          $row['class'][] = 'collapsed';
        }
      }

      // Gets theme hook, adds last minute classes.
      $class = ($item['#active']) ? 'facetapi-active' : 'facetapi-inactive';
      $variables['options']['attributes']['class'][] = $class;

      // Themes the link, adds row to items.
      $row['data'] = theme($item['#theme'], $variables);

      // Get term.
      $term = _know4pol_search_facetapi_load_term($item);

      // Skip unknown term.
      if ($item['term'] == FALSE) {
        continue;
      }

      // Don't we know this vid already ?
      if (!array_key_exists($term->vid, $vid_enable)) {
        // Is this vocabulary par of the current OG ?
        $gid = og_vocab_relation_get($term->vid);
        if (!isset($gid->gid) || $gid->gid != $this->getGidFromQueryContext($item['#query']['f'])) {
          $vid_enable[$term->vid] = array(
            'enable' => FALSE,
          );
        }
        else {
          // Allow and load name.
          $voc = taxonomy_vocabulary_load($term->vid);
          $vid_enable[$term->vid] = array(
            'enable' => TRUE,
            'title' => $voc->name,
          );
        }
      }

      // If term allowed (part of OG group).
      if ($vid_enable[$term->vid]['enable']) {
        // Display Taxonomy title if setting enabled.
        if (!empty($settings['show_subtaxonomies'])) {

          // If vid id different.
          if ($last_vid != $term->vid) {
            // Get the title for this vid.
            $items[] = array(
              'class' => array('leaf', 'ecl-form-label'),
              'data' => $voc->name,
            );
            $last_vid = $term->vid;
          }
        }
        $items[] = $row;
      }
    }
    return $items;
  }

  /**
   * Allows the plugin to add settings to the display form.
   *
   * @see facetapi_facet_display_form()
   */
  public function settingsForm(&$form, &$form_state) {
    parent::settingsForm($form, $form_state);

    $states = array(
      'visible' => array(
        'select[name="widget"]' => array('value' => $this->id),
      ),
    );

    $form['widget']['widget_settings']['links'][$this->id]['show_subtaxonomies'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display sub-taxonomies titles'),
      '#default_value' => !empty($this->settings->settings['show_subtaxonomies']) ? $this->settings->settings['show_subtaxonomies'] : FALSE,
      '#states' => $states,
    );
  }

  /**
   * Get gid from query array for a term.
   *
   * @param array $f
   *   The f from query in facetapi item.
   *
   * @return string
   *   The group_ref (node number)
   */
  private function getGidFromQueryContext(array $f) {
    foreach ($f as $s) {
      if (preg_match('/^sm_og_group_ref\:node\:([0-9]+)$/', $s, $r)) {
        return $r[1];
      }
    }
    return NULL;
  }

}
