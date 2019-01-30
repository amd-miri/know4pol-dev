<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php $i = 0; ?>
<?php foreach ($rows as $id => $row): ?>
    <?php print $row; ?>
    <?php if(++$i < count($rows)): ?>
      ,
    <?php endif; ?>
<?php endforeach; ?>
