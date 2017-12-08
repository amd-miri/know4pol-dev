<?php

/**
 * @file
 * Page item.
 */
  $l = variable_get('newsroom_legacy', 1);
?>

<div class="newsroom-item newsroom-item--teaser<?php if ($l) {echo ' views-row clearfix';} ?>">
  <?php if (!empty($type_title)): ?>
    <div class="newsroom-item__type<?php if ($l) {echo ' views-field views-field-field-newsroom-item-type';} ?>">
      <?php echo !empty($type_url) ? l($type_title, $type_url) : $type_title; ?>
    </div>
  <?php endif; ?>
  <div class="newsroom-item__title<?php if ($l) {echo ' views-field-field-newsroom-item-short-title';} ?>">
    <?php echo l($title, $node_url, ['external' => TRUE]); ?>
  </div>

  <?php if ($image): ?>
  <div class="newsroom-item__img<?php if ($l) {echo ' views-field-field-newsroom-illustrative-img';} ?>">
    <?php echo $image; ?>
  </div>
  <?php endif; ?>

  <?php if (!empty($start_date) || !empty($end_date)): ?>
    <div class="newsroom-item__date <?php if ($l) {echo ' views-field-field-newsroom-item-date';} ?>">
      <?php if (!empty($start_date)): ?>
      <?php if (!empty($end_date)): ?>
      <?php echo t('From'); ?>
      <?php endif; ?>
      <span class="date-display-single" property="dc:date" datatype="xsd:dateTime" content="<?php echo $start_date; ?>"><?php echo $start_date; ?></span>
      <?php endif; ?>
      <?php if (!empty($end_date)): ?>
       <?php echo t('to'); ?>
      <span class="date-display-single" property="dc:date" datatype="xsd:dateTime" content="<?php echo $end_date; ?>"><?php echo $end_date; ?></span>
      <?php endif; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($venue)): ?>
  <div class="newsroom-item__venue<?php if ($l) {echo ' views-field-field-newsroom-item-venue';} ?>">
    <?php echo $venue; ?>
  </div>
  <?php endif; ?>
  <div class="newsroom-item__teaser <?php if ($l) {echo ' views-field-field-newsroom-teaser';} ?>">        
    <?php echo $teaser; ?>
    <?php echo l(t('Read more'), $node_url, ['attributes' => ['class' => ['newsroom-read-more']]]); ?>
  </div>
</div>
