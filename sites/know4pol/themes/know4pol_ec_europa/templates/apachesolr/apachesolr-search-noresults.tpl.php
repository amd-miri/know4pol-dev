<?php

/**
 * @file
 * Contains template file.
 */
?>
<section<?php print $atomium['attributes']['wrapper']; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!empty($title['#markup'])): ?>
    <h3<?php print $atomium['attributes']['title']; ?>><?php print render($title); ?></h3>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
</section>
