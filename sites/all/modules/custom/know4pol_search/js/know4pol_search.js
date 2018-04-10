/**
 * @file
 * JS file for the Topic browser.
 */

(function ($) {
  Drupal.behaviors.know4pol4SearchTopicBrowser = {
    attach: function (context, settings) {
      $("button#topic_button").click(function () {
        if ($(this).html() == 'Topics ▲') {
          $(this).html('Topics ▼');
          $("#country-dropdown-list").slideUp();
          $("#topic-dropdown-list").slideUp();
        }
        else {
          $(this).html('Topics ▲');
          $("#topic-dropdown-list").slideDown();
          $("#country-dropdown-list").slideUp();
        }
      });
    }
  };
}(jQuery));
