<?php

/**
 * @file
 * Agenda items.
 */
  $l = variable_get('newsroom_legacy', 1);
?>
<?php if (!empty($items)): ?>
  <div class="date-row">
    <?php echo $date; ?>
    <div class="date-events">
        <?php foreach ($items as $item): ?>
          <div class="newsroom-item newsroom-item--agenda<?php if ($l) {echo ' views-row clearfix';} ?>">
            <span class="newsroom-item__type<?php if ($l) {echo ' newsroom_type';} ?>"><?php echo $item->name; ?>: </span>
            <div class="newsroom-item__title<?php if ($l) {echo ' newsroom_title';} ?>">
              <?php $prefix = $item->new ? '<span class="itemFlag flagHot newItem">New</span> ' : NULL; ?>
              <?php echo l($prefix . $item->title, $item->url, ['html' => TRUE, 'absolute' => TRUE]); ?>
            </div>
            <div class="newsroom-item__date<?php if ($l) {echo ' newsroom_item_metadata';} ?>">
              <?php echo t('From @start_date', ['@start_date' => $item->prepared_start_date]); ?>
              <?php if (!empty($item->end_date)): ?>
                 <?php echo t('to @end_date', ['@end_date' => $item->prepared_end_date]); ?>
              <?php endif; ?>
            </div>
          </div>
        <?php endforeach; ?>
    </div>
  </div>
<?php endif; ?>
