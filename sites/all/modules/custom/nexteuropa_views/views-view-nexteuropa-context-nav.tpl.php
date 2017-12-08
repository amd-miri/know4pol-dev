<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<span class="context-nav__label"><?php print $navigation_label; ?></span>
<div class="context-nav__items">
  <?php foreach ($rows as $row): ?>
    <span class="context-nav__item">
      <?php print $row; ?>
    </span>
  <?php endforeach; ?>
</div>
