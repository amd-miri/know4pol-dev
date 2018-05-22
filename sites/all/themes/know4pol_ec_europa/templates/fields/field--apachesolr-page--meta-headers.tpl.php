<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>
<?php if($newsroom_type != 'Event'):?>
<?php foreach ($items as $delta => $item): ?>
  <span class="ecl-meta__item"><?php print render($item); ?></span>
<?php endforeach; ?>
<?php endif; ?>

