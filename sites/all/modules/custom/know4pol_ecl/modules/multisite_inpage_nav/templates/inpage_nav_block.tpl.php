<?php

/**
 * @file
 * Theme file for inpage nav.
 */
?>
<?php if ($links): ?>
  <nav class="ecl-navigation-inpage">
    <?php if ($title): ?>
      <div class="ecl-navigation-inpage__title"><?php echo $title; ?></div>
    <?php endif; ?>
    <div class="ecl-navigation-inpage__body">
      <div class="ecl-navigation-inpage__trigger" aria-controls="ecl-navigation-inpage-list" aria-expanded="false" id="ecl-navigation-inpage-trigger">&nbsp;</div>
      <ul class="ecl-navigation-inpage__list" aria-hidden="true" aria-labelledby="ecl-navigation-inpage-trigger" id="ecl-navigation-inpage-list">        
          <?php foreach ($links as $item): ?>
            <li class="ecl-navigation-inpage__item">
              <?php print($item); ?>
            </li>
          <?php endforeach; ?>
      </ul>
    </div>
  </nav>
<?php endif; ?>
