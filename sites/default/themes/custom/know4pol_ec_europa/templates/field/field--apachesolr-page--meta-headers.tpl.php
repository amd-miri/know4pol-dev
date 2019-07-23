<?php

/**
 * @file
 * Template for ecl meta.
 */
?>

<?php if(!isset($hide_metas) || !$hide_metas): ?>
<?php foreach ($items as $delta => $item): ?>
  <span class="ecl-meta__item"><?php print render($item); ?></span>
<?php endforeach; ?>
<?php endif; ?>
