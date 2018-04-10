<?php

/**
 * @file
 * Agenda items.
 */
?>
<?php if (!empty($items)): ?>
<div class="listing__wrapper">
    <ul class="listing listing--agenda listing--column-left">
        <li>
            <div class="listing__item__wrapper newsroom-agenda-items">
                <div class="listing__column-second">
                    <?php echo $date; ?>
                </div>
                <div class="listing__column-main">
                  <?php foreach ($items as $item): ?>

                    <?php if (empty($type_id)): ?>
                    <h2><?php echo $item['title']; ?></h2>
                    <?php endif; ?>

                    <?php if (!empty($item['visible_output'])): ?>
                    <?php echo $item['visible_output']; ?>
                    <?php endif; ?>

                    <?php if (!empty($item['invisible_output'])): ?>
                    <?php echo $item['invisible_output']; ?>
                    <?php endif; ?>

                  <?php endforeach; ?>
                </div>
            </div>
        </li>
    </ul>
</div>
<?php endif; ?>
