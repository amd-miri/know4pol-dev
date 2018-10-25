<?php

/**
 * @file
 * Contains template file.
 */
?>
<ul class="ecl-listing ecl-listing--three-columns ecl-list-fix">
  <?php foreach ($items as $delta => $item) : ?>
    <li class="ecl-list-item ecl-list-item--three-columns">
        <div class="list-content">
          <?php print render($item); ?>
        </div>
    </li>
  <?php endforeach; ?>
</ul>
