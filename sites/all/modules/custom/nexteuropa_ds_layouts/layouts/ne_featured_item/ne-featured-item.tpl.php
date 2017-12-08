<?php

/**
 * @file
 * Display suite layout for the component Featured item in Featured view mode.
 */
?>

<div <?php print $layout_attributes; ?> class="<?php print $classes; ?>">
  <?php if (isset($title_suffix['contextual_links'])) : ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <?php if (!isset($hidelink) || (isset($hidelink) && $hidelink == FALSE)) : ?>
  <a href="<?php print $node_url; ?>" class="listing__item-link">
    <?php endif; ?>

    <div class="featured-item">
      <?php if (!empty($featured_image)) : ?>
        <div class="featured-item__image">
          <?php print $featured_image; ?>
        </div>
      <?php endif; ?>
      <section class="featured-item__content">
        <?php if (!empty($meta)) { ?>
          <div class="meta meta--header">
            <?php print $meta; ?>
          </div>
        <?php } ?>
        <?php print $main; ?>
      </section>
    </div>

    <?php if (!isset($hidelink) || (isset($hidelink) && $hidelink == FALSE)) : ?>
  </a>
<?php endif; ?>
</div>

<?php if (!empty($drupal_render_children)) : ?>
  <?php print $drupal_render_children; ?>
<?php endif; ?>
