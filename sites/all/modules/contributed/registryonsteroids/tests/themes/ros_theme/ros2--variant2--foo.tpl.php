<?php

/**
 * @file
 * Template file.
 *
 * @var string[] $callbacks
 *   Process and preprocess callbacks that were called.
 */
$callbacks[] = preg_replace('@^.*/tests/@', '[..]/', __FILE__);
?>
<?php print implode("\n", $callbacks); ?>
