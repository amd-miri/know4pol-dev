<?php

/**
 * @file
 * Template for the File content type.
 */
?>

<iframe
  src="<?php print($variables['field_ext_url'][0]['url']); ?>"
  height="<?php print($variables['field_frame_height'][0]['value']); ?>"
  width="<?php print($variables['field_frame_width'][0]['value']); ?>"
  style="border:none;">
</iframe>
