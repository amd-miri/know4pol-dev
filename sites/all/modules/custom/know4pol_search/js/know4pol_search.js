/**
 * @file
 * JS file for the Topics and countries browsers.
 */

(function ($) {
  Drupal.behaviors.know4pol4SearchBrowser = {
    attach: function (context, settings) {
      $("button#topic_button").click(function () {
        if ($(this).html() == 'Topics ▲') {
          $(this).html('Topics ▼');
          $("#countries-dropdown-list").slideUp();
          $("button#country_button").html('Countries ▼');
          $("#topics-dropdown-list").slideUp();
        }
        else {
          $(this).html('Topics ▲');
          $("#topics-dropdown-list").slideDown();
          $("button#country_button").html('Countries ▼');
          $("#countries-dropdown-list").slideUp();
        }
      });
      $("button#country_button").click(function () {
        if ($(this).html() == 'Countries ▲') {
          $(this).html('Countries ▼');
          $("#topics-dropdown-list").slideUp();
          $("button#topic_button").html('Topics ▼');
          $("#countries-dropdown-list").slideUp();
        }
        else {
          $(this).html('Countries ▲');
          $("#countries-dropdown-list").slideDown();
          $("button#topic_button").html('Topics ▼');
          $("#topics-dropdown-list").slideUp();
        }
      });
    }
  };
}(jQuery));
