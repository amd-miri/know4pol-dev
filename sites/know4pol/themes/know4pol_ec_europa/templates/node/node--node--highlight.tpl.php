<?php

/**
 * @file
 * Template for the Highlight content type.
 */
?>

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>

<a href="<?php print $content['field_hig_link']['#items'][0]['url']; ?>" class="ecl-link ecl-list-item__link">
  <div class="ecl-u-sr-only"><?php print t('List item: @title', array('title' => $title)); ?></div>

  <div class="ecl-list-item__primary">
   <?php print render($content['field_hig_image']); ?>
  </div>
  <div class="ecl-list-item__body">
    <div class="ecl-list-item__meta">
      <div class="ecl-meta ecl-meta--highlight">
      </div>
    </div>
    <h3 class="ecl-list-item__title ecl-heading ecl-heading--h3"><?php print $title; ?></h3>
    <p class="ecl-list-item__detail ecl-paragraph">
    </p>
    <div class="ecl-list-item__action"></div>
  </div>

</a>
