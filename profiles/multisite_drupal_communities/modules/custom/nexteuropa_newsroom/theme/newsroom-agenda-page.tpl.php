<?php

/**
 * @file
 * Agenda page.
 */
?>
<div class="<?php echo !$is_block ? 'newsroomAgenda-container' : NULL; ?>">
  <?php if (!empty($filter_form)): ?>
    <div class="newsroomAgenda-filterForm">
      <h3><?php echo t('filter by'); ?></h3>
      <?php echo $filter_form; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($items) || !empty($next_event_items)): ?>
    <?php if (!empty($items)) : ?>
      <div class="currentDate">
        <?php echo $items; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($next_event_items)) : ?>
      <div class="furtherDates">
        <h4 class="newsroom_title"><?php echo t('Upcoming'); ?></h4>
        <?php echo $next_event_items; ?>
      </div>
    <?php endif; ?>
    <?php if (!empty($navigation['previous']) || !empty($navigation['next'])): ?>
      <div class="agendaPagination">
        <?php if (!empty($navigation['previous'])): ?>
          <div class="agenda-previous"><?php echo $navigation['previous']; ?></div>
        <?php endif; ?>

        <div class="date-form">
          <?php echo $date_form; ?>
        </div>

        <?php if (!empty($navigation['next'])): ?>
          <div class="agenda-next"><?php echo $navigation['next']; ?></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>
  <?php elseif(!$is_block): ?>
    <div class="no-result"><?php echo t("No results"); ?></div>
  <?php endif; ?>
</div>
