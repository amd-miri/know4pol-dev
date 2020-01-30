<?php

/**
 * @file
 * Display Suite NE Bootstrap Three-Nine Stacked.
 */
?>

<<?php print $layout_wrapper . $layout_attributes; ?> class="<?php print $classes; ?>">

  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
    <?php print $header; ?>
  </<?php print $header_wrapper ?>>

  <div class="ecl-row ecl-u-z-navigation">
    <a id="main-content" tabindex="-1"></a>
    <?php if ($left): ?>
      <<?php print $left_wrapper; ?> class="ecl-col-md-3 ecl-u-z-navigation js-stickybit-parent<?php print $left_classes; ?>">
        <?php print $left; ?>
      </<?php print $left_wrapper; ?>>
      <section class="section ecl-col-md-9 <?php print $central_classes; ?>">
        <?php print $central; ?>
      </section>
    <?php else: ?>
      <section class="section ecl-col-md-12 <?php print $central_classes; ?>">
        <?php print $central; ?>
      </section>
    <?php endif; ?>
  </div>
  <<?php print $footer_wrapper ?> class="group-footer<?php print $footer_classes; ?>">
    <?php if ($footer_top): ?>
      <h3>Get this resource</h3>
      <?php print $footer_top; ?>
    <?php endif; ?>
    <?php if ($footer): ?>
      <h2 id="latest" class="ecl-heading ecl-heading--h2" anchor="News, Events, Resources">Latest on <?php print $title; ?> from the KnowledgeBase</h2>

      <?php print $footer; ?>
    <?php endif; ?>
    <?php if ($footer_bottom): ?>
    <h2 id="links" class="ecl-heading ecl-heading--h2">Related links</h2>

    <table class="ecl-table ecl-table--responsive">
      <tbody>
        <?php print $footer_bottom; ?>
      </tbody>
    </table>
    <?php endif; ?>
  </<?php print $footer_wrapper ?>>

</<?php print $layout_wrapper; ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children; ?>
<?php endif; ?>
