<?php

/**
 * @file
 * Contains template file.
 */
?>

<?php foreach ($items as $delta => $item): ?>
    <?php print render($item); ?>
<?php endforeach; ?>
