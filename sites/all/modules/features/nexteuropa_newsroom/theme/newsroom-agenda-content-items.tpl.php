<?php

/**
 * @file
 * Agenda content items.
 */
?>
<?php if (!empty($items)): ?>
    <?php if (!empty($agenda_type)): ?>
        <div id="display-more-link-<?php echo $agenda_type; ?>-<?php echo $type_id; ?>" class="newsroom-display-more btn btn-ctn"><?php echo t('Display more'); ?></div>
        <div id="display-more-container-<?php echo $agenda_type; ?>-<?php echo $type_id; ?>" class="newsroom-display-more-container" style="display: none;">
    <?php endif; ?>
    <div class="listing__column-main">
        <div class="listing__wrapper">
            <ul class="listing listing--no-border">
                <?php foreach ($items as $item): ?>
                    <div class="meta">
                        <span class="meta__item">
                            <?php if (!empty($item->end_date) && $item->end_date != $item->start_date): ?>
                                <?php echo t('From @start_date', ['@start_date' => $item->prepared_start_date]); ?>
                                <?php echo t('to @end_date', ['@end_date' => $item->prepared_end_date]); ?>
                            <?php else: ?>
                                <?php echo $item->prepared_start_date; ?>
                            <?php endif; ?>
                        </span>
                    </div>
                    <h3 class="listing__title">
                    <?php $title_text = check_plain($item->title); ?>
                    <?php echo l($title_text, $item->url, [
                      'html' => TRUE,
                      'absolute' => TRUE,
                    ]); ?>
                    </h3>
                <?php endforeach; ?>
            </ul>
        </div>
    </div>
    <?php if (!empty($agenda_type)): ?>
        </div>
    <?php endif; ?>
<?php endif; ?>
