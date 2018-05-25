<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>
<!-- Default event -->
<div class="ecl-date-block
  <?php if (isset($ecl_date['type'])): ?>
    <?php print ' ecl-date-block--' . $ecl_date['type']; ?> 
  <?php endif; ?>">
  <div class="ecl-date-block__body">
    <?php if(!(isset($ecl_date['type']) && $ecl_date['type'] == 'past')): ?>
      <span class="ecl-date-block__week-day"><?php print $ecl_date['weekday'];?></span>
    <?php endif; ?>
    <span class="ecl-date-block__day"><?php print $ecl_date['day'];?></span>
    <span class="ecl-date-block__month"><?php print $ecl_date['month'];?></span>
    <?php if(isset($ecl_date['next_year']) || (isset($ecl_date['type']) && $ecl_date['type'] == 'past')): ?>
      <span class="ecl-date-block__year"><?php print $ecl_date['year'];?></span>
    <?php endif; ?>
  </div>
</div>
