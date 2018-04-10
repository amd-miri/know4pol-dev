<?php

/**
 * @file
 * Contains template file.
 */
?>

<?php if (!empty($variables['items'])): ?>
  <ul class="ecl-link-block__list">
  <?php foreach ($variables['items'] as $item): ?>
      <li class="ecl-link-block__item">
      <?php print $item['data']; ?>
    </li>
  <?php endforeach; ?>
 </ul>
<?php endif; ?>
