<?php

/**
 * @file
 * Contains template file.
 */
?>
<tr>
    <td><?php print $label; ?></td>
    <td<?php print $atomium['attributes']['wrapper']; ?>>
      <?php foreach ($items as $delta => $item) : ?>
          <div<?php print $atomium['attributes'][$delta]; ?>><?php print render($item); ?></div>
      <?php endforeach; ?>
    </td>
</tr>
