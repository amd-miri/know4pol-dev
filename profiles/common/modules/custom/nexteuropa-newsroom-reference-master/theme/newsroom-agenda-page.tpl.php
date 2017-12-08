<?php

/**
 * @file
 * Agenda page.
 */
?>
<div class="<?php echo !$is_block ? 'newsroomAgenda-container' : NULL; ?>">
  <?php if (!empty($items['visible_items']) || !empty($next_event_items['visible_items']) || !empty($past_event_items['visible_items'])): ?>

    <?php if (!empty($items['visible_items'])) : ?>
      <div class="currentDate">
        <?php echo $items['visible_items']; ?>
      </div>
    <?php else: ?>
        <div class="newsroom-message"><?php echo t('No events for current date'); ?></div>
    <?php endif; ?>

    <?php if (!empty($next_event_items['visible_items'])) : ?>
      <div class="furtherDates">
        <h2 class="newsroom_title"><?php echo t('Upcoming'); ?></h2>
        <?php echo $next_event_items['visible_items']; ?>

        <?php if (!empty($next_event_items['invisible_items'])) : ?>
        <div id="display-more-link-<?php echo NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING; ?>" class="newsroom-display-more btn btn-ctn"><?php echo t('Display more upcoming items'); ?></div>
        <div id="display-more-container-<?php echo NexteuropaNewsroomAgenda::AGENDA_TYPE_UPCOMING; ?>" class="newsroom-display-more-container" style="display: none;">
            <?php echo $next_event_items['invisible_items']; ?>
        </div>
        <?php endif; ?>
        <?php if (!empty($next_link)): ?>
            <div class="agendaPagination">
              <?php if (!empty($next_link)): ?>
                  <div class="agenda-next"><?php echo $next_link; ?></div>
              <?php endif; ?>
            </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php if (!empty($past_event_items['visible_items'])) : ?>
      <div class="pastDates">
        <h2 class="newsroom_title"><?php echo t('Past'); ?></h2>
        <?php echo $past_event_items['visible_items']; ?>
        <?php if (!empty($past_event_items['invisible_items'])) : ?>
            <div id="display-more-link-<?php echo NexteuropaNewsroomAgenda::AGENDA_TYPE_PAST; ?>" class="newsroom-display-more btn btn-ctn"><?php echo t('Display more past items'); ?></div>
            <div id="display-more-container-<?php echo NexteuropaNewsroomAgenda::AGENDA_TYPE_PAST; ?>" class="newsroom-display-more-container" style="display: none;">
              <?php echo $past_event_items['invisible_items']; ?>
            </div>
        <?php endif; ?>
        <?php if (!empty($previous_link)): ?>
            <div class="agendaPagination">
              <?php if (!empty($previous_link)): ?>
                  <div class="agenda-previous"><?php echo $previous_link; ?></div>
              <?php endif; ?>
            </div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

  <?php elseif(!$is_block): ?>
    <div class="newsroom-message"><?php echo t('No results'); ?></div>
  <?php endif; ?>
</div>
