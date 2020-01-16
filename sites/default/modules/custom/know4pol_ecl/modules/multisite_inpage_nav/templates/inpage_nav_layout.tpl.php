<?php

/**
 * @file
 * Display Suite NE Bootstrap Three-Nine Stacked.
 */
?>

<div class="ecl-row ecl-u-z-navigation">
  <a id="main-content" tabindex="-1"></a>
  <?php if ($left): ?>
  <div class="ecl-col-md-3 ecl-u-z-navigation js-stickybit-parent">
  <?php print $left; ?>
  </div>
  <section class="section ecl-col-md-9">
    <?php print $central; ?>
  </section>
<?php else: ?>
  <section class="section ecl-col-md-12">
    <?php print $central; ?>
  </section>
<?php endif; ?>
</div>
