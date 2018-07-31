<?php

/**
 * Renders the content using the original Quicktabs.
 *
 * Plugin for ecl-tabs.
 */
class Know4polEclTabs extends QuickRenderer {

  /**
   * The only method that renderer plugins must implement.
   *
   * @return array
   *   A render array to be passed to drupal_render().
   */
  public function render() {
    $quickset = $this->quickset;

    $render_array = array();

    $active_tab = $quickset->getActiveTab();
    if ($tabs = $this->buildTabLinks($active_tab)) {
      $qt_name = $quickset->getName();

      $tab_contents = '';
      foreach ($quickset->getContents() as $key => $item) {

        if (!empty($item)) {
          $item_content = $item->render();
          $tab_render = array(
            '#type' => 'markup',
            '#markup' => render($item_content),
            '#prefix' => '<section role="tabpanel" id="' . $qt_name . '-' . $key . '-tab" ' .
            'aria-labelledby="' . $key . '" aria-hidden="' .
            ($key == $active_tab ? 'false' : 'true') .
            '" class="ecl-tabs__tabpanel" tabindex="0">',
            '#suffix' => '</section>',
          );
          $tab_contents .= render($tab_render);
        }
      }

      $render_array['content'] = array(
        '#type' => 'markup',
        '#markup' => '<ul role="tablist" class="ecl-tabs__tablist ecl-navigation-list ecl-navigation-list--tabs">' .
        render($tabs) . '</ul>' . $tab_contents,
        '#prefix' => '<div class="ecl-tabs">',
        '#suffix' => '</div>',
      );
    }
    return $render_array;
  }

  /**
   * Build the actual tab links, with appropriate href, title and attributes.
   *
   * @param string $active_tab
   *   The index of the active tab.
   */
  protected function buildTabLinks($active_tab) {
    $quickset = $this->quickset;
    $qname = $quickset->getName();

    $tabs = array();
    foreach ($quickset->getContents() as $i => $tab) {
      if (!empty($tab)) {
        $tablink = array(
          '#markup' => '<li role="tab" aria-controls="' .
          $qname . '-' . $i . '-tab" id="' . $qname . '-' . $i . '"' .
          (($i == $active_tab) ?
              'aria-selected="true" tabindex="0"' :
              'aria-selected="false" tabindex="-1"') .
          'class="ecl-navigation-list__item ecl-navigation-list__link">' .
          $quickset->translateString($tab->getTitle(), 'tab', $i) . '</li>',
          '#type' => 'markup',
        );
        $tabs[$i] = $tablink;
      }
    }
    return $tabs;
  }

}
