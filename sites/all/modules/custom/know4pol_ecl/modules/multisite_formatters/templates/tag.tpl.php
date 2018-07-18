<?php

/**
 * @file
 * Contains the template file of the card component.
 *
 * Available variables:
 * - $url: string which contains an url.
 * - $label: string which contains a label.
 */
?>

<div class="ecl-tag ecl-tag--facet">
  <?php if (isset($group_label)): ?>
    <span class="ecl-tag__label"><?php print($group_label); ?></span>
  <?php endif; ?>
  <?php foreach($items as $key => $item): ?>
    <?php if (isset($item['url'])): ?>
      <a class="ecl-tag__item" href="<?php print $item['url'] ?>"><?php print $item['label'] ?></a>
    <?php else: ?>
      <span class="ecl-tag__item"><?php print $item['label'] ?></span>
    <?php endif ?>
  <?php endforeach; ?>
</div>