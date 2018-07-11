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
          // Change CSS of both buttons.
          $(this).css("background-color", "white");
          $(this).css("color", "#004494");
          $("button#country_button").css("background-color", "white");
          $("button#country_button").css("color", "#004494");
        }
        else {
          $(this).html('Topics ▲');
          $("#topics-dropdown-list").slideDown();
          $("button#country_button").html('Countries ▼');
          $("#countries-dropdown-list").slideUp();
          // Change CSS of both buttons.
          $(this).css("background-color", "#004494");
          $(this).css("color", "white");
          $("button#country_button").css("background-color", "white");
          $("button#country_button").css("color", "#004494");
        }
      });
      $("button#country_button").click(function () {
        if ($(this).html() == 'Countries ▲') {
          $(this).html('Countries ▼');
          $("#topics-dropdown-list").slideUp();
          $("button#topic_button").html('Topics ▼');
          $("#countries-dropdown-list").slideUp();
          // Change CSS of both buttons.
          $(this).css("background-color", "white");
          $(this).css("color", "#004494");
          $("button#topic_button").css("background-color", "white");
          $("button#topic_button").css("color", "#004494");
        }
        else {
          $(this).html('Countries ▲');
          $("#countries-dropdown-list").slideDown();
          $("button#topic_button").html('Topics ▼');
          $("#topics-dropdown-list").slideUp();
          // Change CSS of both buttons.
          $(this).css("background-color", "#004494");
          $(this).css("color", "white");
          $("button#topic_button").css("background-color", "white");
          $("button#topic_button").css("color", "#004494");
        }
      });
    }
  };
}(jQuery));
