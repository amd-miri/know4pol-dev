<?php

/**
 * @file
 * Contains template file.
 */
?>

<h2 id="brief" class="ecl-heading ecl-heading--h2">Brief me</h2>
<div class="field-name-field-av-image">
  <div class="ecl-field__body">
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>><?php print render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>
