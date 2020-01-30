<?php

/**
 * @file
 * Contains template file.
 */
?>

<div<?php print $atomium['attributes']['wrapper']; ?>>
  <h2 id="explore" class="ecl-heading ecl-heading--h2"><?php print $label ?></h2>
  <div class="ecl-field__body">
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>><?php print render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>
