<?php

/**
 * @file
 * Display Suite fluid 2 column stacked template.
 */
?>

<li <?php print $layout_attributes; ?> class="ds-2col-stacked-fluid ecl-u-mv-m group-one-column clearfix apachesolr">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
    <?php print $header; ?>
  </<?php print $header_wrapper ?>>

  <?php if ($right): ?>
    <<?php print $right_wrapper ?> class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
    </<?php print $right_wrapper ?>>
  <?php endif; ?>


  <?php if ($left): ?>
    <<?php print $left_wrapper ?> class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
    </<?php print $left_wrapper ?>>
  <?php endif; ?>

  <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
    <?php print $footer; ?>
  </<?php print $footer_wrapper ?>>
  
  <hr class="ecl-u-mt-m">
</li>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
