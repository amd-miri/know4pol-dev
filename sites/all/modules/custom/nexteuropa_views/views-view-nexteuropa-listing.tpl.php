<?php

/**
 * @file
 * View template to display a news carousel.
 *
 * @ingroup views_templates
 */
?>
<div class="listing__wrapper<?php print $listing_columns . $listing_wrapper_modifier; ?>">
  <?php foreach ($columns as $column): ?>
    <ul class="listing<?php print (isset($ds_view_mode) ? $ds_view_mode : '') . $listing_modifier; ?>">
    <?php foreach ($column as $row): ?>
      <li class="listing__item<?php print $listing_item_modifier; ?>">
        <?php print $row; ?>
      </li>
    <?php endforeach; ?>
    </ul>
  <?php endforeach; ?>
</div>
