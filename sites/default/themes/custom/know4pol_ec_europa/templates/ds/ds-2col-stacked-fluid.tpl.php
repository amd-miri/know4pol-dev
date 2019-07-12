<?php

/**
 * @file
 * Display Suite fluid 2 column stacked template.
 *
 * @TODO update once new grid style is defined.
 */
?>
  // Add sidebar classes so that we can apply the correct width in css.
<?php if (($left && !$right) || ($right && !$left)): ?>
  <?php $classes .= ' group-one-column'; ?>
<?php endif; ?>

<<?php print $layout_wrapper; print $layout_attributes; ?> class="ds-2col-stacked-fluid <?php print $classes; ?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
    <?php print $header; ?>
  </<?php print $header_wrapper ?>>

  <?php if ($left): ?>
    <<?php print $left_wrapper ?> class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
    </<?php print $left_wrapper ?>>
  <?php endif; ?>

  <?php if ($right): ?>
    <<?php print $right_wrapper ?> class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
    </<?php print $right_wrapper ?>>
  <?php endif; ?>

  <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
    <!-- Table with empty heading - enhanced -->
    <table class="ecl-table ecl-table--responsive">
      <thead>
        <!-- Those contain a hidden special char to avoid ECL bug. Char U+FEFF -->
        <tr>
          <th scope="col">﻿</th>
          <th scope="col">﻿</th>
        </tr>
      </thead>
      <tbody>
        <?php print $footer; ?>
      </tbody>
    </table>
  </<?php print $footer_wrapper ?>>

</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
