<?php

/**
 * @file
 * Contains template file.
 */
?>
<label for="<?php print $label['element']['#id']; ?>" class="ecl-search-form__textfield-wrapper">
  <span class="ecl-u-sr-only"><?php print t('Search this website'); ?></span>
  <?php print $element['#children']; ?>
</label>
