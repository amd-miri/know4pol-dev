<?php

/**
 * @file
 * Contains template file.
 */
?>
<footer class="ecl-footer">
  <?php if ($footer_left || $footer_middle || $footer_right): ?>
  <div class="ecl-footer__site-identity">
    <div class="ecl-container">
      <div class="ecl-row">
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_left); ?>
        </div>
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_middle); ?>
            
            <p class="ecl-footer__label">Follow us:</p>
            
            <ul class="ecl-footer__menu ecl-list--inline ecl-footer__social-links">
            <li class="ecl-footer__menu-item">
 
                <a class="ecl-link ecl-footer__link" href="<?php print 'http://'. $twitter;?>"><span class="ecl-icon ecl-icon--twitter ecl-footer__social-icon"></span>Twitter</a>
            </li>
            <li class="ecl-footer__menu-item">
 
              <a class="ecl-link ecl-link--external ecl-footer__link" href="<?php print 'http://'. $blog;?>">Other social media</a>
            </li>
          </ul>
            
        </div>
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_right); ?>
            <a class="ecl-footer__link ecl-link ecl-link--inverted" href="<?php print $about_page; ?>"> <?php if(isset($group_title)){ print 'About'. $group_title;} ?></a>
        </div>
      </div>
    </div>
  </div>
  <?php endif; ?>

  <div class="ecl-footer__site-corporate">
    <div class="ecl-container">
      <div class="ecl-row">
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_corporate_left); ?>
        </div>
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_corporate_middle); ?>
        </div>
        <div class="ecl-col-sm ecl-footer__column">
          <?php print render($footer_corporate_right); ?>
        </div>
      </div>
    </div>
  </div>

  <div class="ecl-footer__ec">
    <div class="ecl-container">
      <div class="ecl-row">
        <div class="ecl-col-sm">
          <?php print render($footer_ec); ?>
        </div>
      </div>
    </div>
  </div>
</footer>
