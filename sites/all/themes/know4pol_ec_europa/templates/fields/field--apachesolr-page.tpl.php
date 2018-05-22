<?php

/**
 * @file
 * Contains template file.
 */
?>
<?php if($newsroom_type == 'Event'):?>
<?php foreach ($items as $delta => $item) : ?>
  <!-- Default event -->
<div class="ecl-date-block">
  <div class="ecl-date-block__body">
    <span class="ecl-date-block__week-day"><?php echo $event_start_date[0];?></span>
    <span class="ecl-date-block__day"><?php echo $event_start_date[1];?></span>
    <span class="ecl-date-block__month"><?php echo $event_start_date[2];?></span>
  </div>
</div>
    <?php print render($item); ?>
<?php endforeach; ?>
<?php endif; ?>