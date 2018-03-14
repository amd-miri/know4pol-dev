<?php

/**
 * @file
 * Default theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: An ID for the block, unique within each module.
 * - $block->region: The block region embedding the current block.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - block: The current template type, i.e., "theming hook".
 *   - block-[module]: The module generating the block. For example, the user
 *     module is responsible for handling the default user navigation block. In
 *     that case the class would be 'block-user'.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Helper variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 * - $block_html_id: A valid HTML ID and guaranteed unique.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<section<?php print $atomium['attributes']['wrapper']; ?>>
  <?php print render($title_prefix); ?>
  <?php if (isset($solr) && $solr['result_count'] > 0): ?>
    <?php if (!empty($title)): ?>
    <?php endif; ?>
      
    <?php print render($title_prefix); ?> 
    <?php if ($solr['result_count'] > 1): ?>
      <h2 class="ecl-heading ecl-heading--h2 ecl-u-d-none ecl-u-d-lg-block" <?php print $atomium['attributes']['title']; ?>>
        <?php print t('Search results'); ?>
        (<?php print $solr['result_count']; ?>)
      </h2>
      <?php if ($solr['max_page'] > 1): ?>
        <h3 class="ecl-heading ecl-heading--h3">
          <?php print t('Showing results'); ?>
          <?php print $solr['result_start']; ?> to 
          <?php print $solr['result_end']; ?>
        </h3>
      <?php endif; ?>
    <?php else: ?>
      <h2 class="ecl-heading ecl-heading--h2 ecl-u-d-none ecl-u-d-lg-block" <?php print $atomium['attributes']['title']; ?>>
        <?php print t('Search result'); ?>
      </h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    
    <?php if (isset($solr['facets'])): ?>
      <div class="ecl-u-d-flex ecl-u-align-items-center ecl-u-flex-wrap">
        <?php foreach ($solr['facets'] as $item): ?>
        <div class="ecl-tag ecl-tag--facet-close ecl-u-mv-xxxs">
          <span class="ecl-tag__label"><?php print $item['facet']['label']; ?></span>
          <?php foreach ($item['values'] as $tag): ?>
            <a href="?<?php print $tag['removed_url']; ?>">
              <button class="ecl-button ecl-button--facet-close ecl-tag__item" type="button">
                <?php print render($tag['name']); ?>
              </button>
            </a>
          <?php endforeach; ?>
        </div>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>
    
  <?php else : ?>
    <h2 class="ecl-heading ecl-heading--h2 ecl-u-d-none ecl-u-d-lg-block" <?php print $atomium['attributes']['title']; ?>>
      <?php print render($title); ?>
    </h2>
    <?php print render($title_suffix); ?>
    <?php if (!empty($content)): ?>
      <div<?php print $atomium['attributes']['content']; ?>>
        <?php print render($content); ?>
      </div>
    <?php endif; ?>

  <?php endif; ?>
    
</section>