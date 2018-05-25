<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>

<?php foreach ($items as $delta => $item): ?>
  <span class="ecl-meta__item"><?php print render($item); ?></span>
<?php endforeach; ?>
