<?php

/**
 * @file
 * Template for the File content type.
 */
?>
<div class="content">
<!-- Translations -->
<section class="ecl-file ecl-file--translation">
  <div class="ecl-file__body">
    <div class="ecl-row">
      <div class=" ecl-col ecl-col-md-8">
        <span class="ecl-icon <?php print $variables['elements']['#node']->file_type_css; ?> ecl-file__icon"></span>
        <div class="ecl-file__metadata">
          <div class="ecl-file__title"><?php print check_plain($variables['elements']['#node']->title); ?></div>
          <div class="ecl-file__info">
            <span class="ecl-file__language"><?php print filter_xss($variables['elements']['language']['#markup']); ?></span>
            <?php
              if($variables['elements']['#node']->file_link['info']) {
                print $variables['elements']['#node']->file_link['info'];
              }
            ?>
          </div>
        </div>
      </div>
      <div class="ecl-col-12 ecl-col-md-4">
        <?php if($variables['elements']['#node']->file_link): ?>
          <a href="<?php print $variables['elements']['#node']->file_link['link']; ?>">
              <button class="ecl-button ecl-button--default ecl-button--block ecl-button--file ecl-file__download" type="button">
            <?php print t('Download'); ?>
            <?php if($variables['elements']['#node']->file_link['info']): ?>
              <span class="ecl-u-sr-only"><?php print $variables['elements']['#node']->file_link['info']; ?></span>
            <?php endif; ?>
            </button>
          </a>
        <?php else: ?>
          <button class="ecl-button ecl-button--default ecl-button--block ecl-button--file" type="button"><?php print t('Unavailable'); ?></button>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <?php if (count($variables['translations']->data)): ?>
  <div class="ecl-file__translations">
    <button class="ecl-button ecl-button--secondary ecl-button--file ecl-file__translations-toggle" aria-controls="translations-expand" aria-expanded="false" id="translations-expand-button" type="button" title="Click to see translations">
      <?php print t('Available languages') . '(' . count($variables['translations']->data) . ')'; ?>
    </button>
    <div aria-hidden="true" aria-labelledby="translations-expand-button" id="translations-expand">
      <ul class="ecl-file__translations-list">
        <?php foreach($variables['translations']->data as $f): ?>
        <li class="ecl-file__translations-item">
          <div class="ecl-file__translations-metadata">
            <span class="ecl-file__translations-title"><?php print check_plain($f->title) ?></span>
            <?php if($f->file_link['info']): ?>
              <div class="ecl-file__translations-info"><?php print $f->file_link['info']; ?></div>
            <?php endif; ?>
          </div>
          <?php if($f->file_link): ?>
            <a href="<?php print $f->file_link['link']; ?>">
              <button class="ecl-button ecl-button--secondary ecl-button--file ecl-file__translations-download" type="button">
              <?php print t('Download'); ?>
              <?php if($f->file_link['info']): ?>
                <span class="ecl-u-sr-only"><?php print $f->file_link['info']; ?></span>
              <?php endif; ?>
              </button>
            </a>
          <?php else: ?>
            <button class="ecl-button ecl-button--secondary ecl-button--file" type="button"><?php print t('Unavailable'); ?></button>
          <?php endif; ?>
        </li>
        <?php endforeach; ?>
      </ul>
    </div>
  </div>
  <?php endif; ?>
</section>
</div>
