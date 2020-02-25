<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any.
 *
 * @ingroup views_templates
 */
?>
<div class="<?php print $classes; ?>">
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>
  <?php if ($rows): ?>
    <div class="browse-by-block ecl-dropdown">
      <button class="ecl-button ecl-button--default ecl-expandable__button" aria-controls="countries-dropdown" type="button"
              aria-expanded="false" id="countries-dropdown-button"><?php print t('Countries'); ?></button>
      <div aria-hidden="true" aria-labelledby="countries-dropdown-button" id="countries-dropdown" class="row dropdown-list">
      <?php print $rows; ?>
      </div>
    </div>
  <?php endif; ?>
</div>


<div style="margin-top:1rem">

  <button class="" aria-controls="example-expandable-1" aria-expanded="false" data-label-expanded="Hide me" data-label-collapsed="What is this all about?" id="example-expandable-button-1" type="button">What is this all about?</button>
  <div aria-hidden="true" aria-labelledby="example-expandable-button-1" id="example-expandable-1">
    <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</p>
    <p>Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat...</p>
  </div>
</div>
