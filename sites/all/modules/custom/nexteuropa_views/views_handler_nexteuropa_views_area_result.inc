<?php

/**
 * @file
 * Custom handler for results summary.
 *
 * @codingStandardsIgnoreFile
 */

/**
 * Class views_handler_nexteuropa_views_area_result.
 */
class views_handler_nexteuropa_views_area_result extends views_handler_area_result {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['content'] = array(
      'default' => 'Showing results @start to @end',
      'translatable' => TRUE,
    );

    return $options;
  }

  /**
   * Find out the information to render.
   */
  public function render($empty = FALSE) {
    $markup = [
      '#markup' => parent::render(),
      '#prefix' => '<div class="filters__result-range">',
      '#suffix' => '</div>',
    ];
    return drupal_render($markup);
  }

}
