<?php

/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 * @see template_preprocess_search_results()
 *
 * @ingroup themeable
 */
?>
<?php if ($variables['elements']['search_results']['search_results']): ?>
  <ul class="ecl-list ecl-list--unstyled ecl-u-mv-m">
    <?php print render($variables['elements']['search_results']['search_results']['#children']); ?>
  </ul>
  <?php print render($variables['elements']['search_results']['search_pager']['#children']); ?>
<?php else : ?>
  <h2><?php print t('No results');?></h2>
  <?php print render($content); ?>
<?php endif; ?>
