<?php

/**
 * @file
 * Service list page.
 */
global $user;
?>
<div class="newsroom-service-page">
  <div class="newsroom-service-widget">
    <?php if (user_is_logged_in()): ?>
      <h2><?php echo t('Your e-mail'); ?></h2>
       <div class="middle-step">
        <?php echo $user->mail; ?>
      </div>
    <?php else: ?>
      <h2>
         <?php echo t('Your e-mail'); ?>
      </h2>
      <div class="middle-step">
        <input type="text" class="newsroom-service-email" id="newsroom-service-email" />
        <div class="newsroom-service-email-description">
          <span><?php echo t('or'); ?></span> <?php echo l(t('login'), 'user/login'); ?> <?php echo t('to manage your subscriptions.'); ?>
        </div>
      </div>
    <?php endif; ?>

    <h2><?php echo t('Subscribe to newsletters'); ?></h2>
  </div>

  <?php echo $central_items; ?>
  <?php echo $basic_items; ?>    

  <?php if (!empty($privacy_text)): ?>
    <h2><?php echo t('Privacy Statement'); ?></h2>
    <?php echo $privacy_text; ?>
  <?php endif; ?>
</div>
