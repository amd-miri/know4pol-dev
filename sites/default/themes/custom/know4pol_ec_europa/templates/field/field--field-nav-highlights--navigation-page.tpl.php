<?php

/**
 * @file
 * Contains template file.
 */
?>
<!-- Three columns listing -->
<ul class="ecl-listing ecl-listing--three-columns ecl-listing--highlights">
  <?php foreach ($items as $delta => $item) : ?>
    <li class="ecl-list-item ecl-list-item--highlight">
       <?php print render($item); ?>
    </li>
  <?php endforeach; ?>
</ul>
