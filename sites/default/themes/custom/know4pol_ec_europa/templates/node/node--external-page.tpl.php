<?php

/**
 * @file
 * Template for the File content type.
 */
?>

<div>
  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <iframe
    src="<?php print($variables['field_ext_url'][0]['url']); ?>"
    height="<?php print($variables['field_frame_height'][0]['value']); ?>"
    width="<?php print($variables['field_frame_width'][0]['value']); ?>"
    style="border:none;">
  </iframe>
</div>
