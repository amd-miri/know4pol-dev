<?php
/**
 * @file
 * Page item.
 */
?>
<?php if (!empty($items)): ?>
<div class="listing__wrapper">
  <ul class="listing listing--teaser">
    <?php foreach($items as $item): ?>
    <li class="listing__item">
      <div class="listing__item__wrapper">
        <?php echo drupal_render(node_view($item, 'newsroom_teaser')); ?>
      </div>
    </li>
    <?php endforeach; ?>
  </ul>
</div>
<?php endif; ?>
