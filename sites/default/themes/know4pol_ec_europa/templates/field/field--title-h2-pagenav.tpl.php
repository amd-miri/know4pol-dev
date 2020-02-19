<?php

/**
 * @file
 * Contains template file.
 */
?>

<h2 class="ecl-heading ecl-heading--h2" id="<?php print $html_id; ?>" <?php
    if(isset($anchor_text)):
      ?>anchor="<?php print $anchor_text; ?>"<?php
    endif;
      ?>><?php print $label; ?></h2>
<div<?php print $atomium['attributes']['wrapper']; ?>>
  <div class="ecl-field__body">
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>><?php print render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>
