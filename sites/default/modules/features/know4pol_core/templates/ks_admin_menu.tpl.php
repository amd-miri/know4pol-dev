<?php

/**
 * @file
 * Contains template file.
 */
?>

<?php if (!empty($variables['items'])): ?>
  <?php foreach ($variables['items'] as $item): ?>
      <div class="element">
        <div class="ecl-dropdown">
          <button class="ecl-button ecl-button--default ecl-expandable__button"
                  aria-controls="<?php print $item['link']['title']; ?>-button-dropdown" aria-expanded="false"
                  id="<?php print $item['link']['title']; ?>-expandable-button"
                  type="button"><?php print $item['link']['title']; ?>
          </button>
          
          <div class="ecl-link-block ecl-dropdown__body" id="<?php print $item['link']['title']; ?>-button-dropdown" 
             aria-labelledby="<?php print $item['link']['title']; ?>-expandable-button" aria-hidden="true">
            <ul class="ecl-link-block__list">
              <?php foreach ($item['below'] as $link): ?>
                <li class="ecl-link-block__item">
                    <?php print l($link['link']['title'], $link['link']['href'],
                      array('attributes' => array('class' => array('ecl-link--standalone', 'ecl-link-block__link')))); ?>
                </li>
              <?php endforeach; ?>
            </ul>
          </div>
        </div>
      </div>
  <?php endforeach; ?>
<?php endif; ?>
