<?php

/**
 * @file
 * Contains template file.
 */
?>

<?php if (!empty($variables['items'])): ?>
  <ul class="ecl-listing ecl-listing--three-columns">
  <?php foreach ($variables['items'] as $item): ?>
      <li class="ecl-list-item ecl-list-item--three-columns">
          <div class="ecl-list-item__body">
              <h3 class="ecl-list-item__title ecl-heading ecl-heading--h3"><?php print $item['title']; ?></h3>
              <?php print $item['content']; ?>
          </div>
      </li>
  <?php endforeach; ?>
 </ul>
<?php endif; ?>
