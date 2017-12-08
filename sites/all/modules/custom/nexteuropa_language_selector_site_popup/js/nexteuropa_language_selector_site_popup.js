/**
 * @file
 * JS file for accessibility tabs.
 */

(function ($) {
  // Fix for accessibility issue, when user reach the close tab,
  // (using the keyboard tab), it should then move to first language selection.
  Drupal.behaviors.splash_accessibility = {
    attach: function (context) {
      var $firstLanguage = (".splash-page__btn-language:first");
      var $closeButton = (".splash-page__btn-close");
      var $lastLanguage = (".splash-page__btn-language:last");
      $('.splash-page--overlay').keydown(function (e) {
        // Moving tab only.
        if (!e.shiftKey && $($closeButton).is(":focus") && (e.which || e.keyCode) == 9) {
            e.preventDefault();
            $($firstLanguage).focus();
        }
        // Moving shift + tab until the close button.
        if (e.shiftKey &&    $($firstLanguage).is(":focus") && (e.which || e.keyCode) == 9) {
            e.preventDefault();
            $($closeButton).focus();
            // Force to stop, otherwise it will go to the last lang tab,
            // when pressing tab + shit.
            return false;
        }
        // Move tab to last lang when pressing tab + shit.
        if (e.shiftKey && $($closeButton).is(":focus") && (e.which || e.keyCode) == 9) {
            e.preventDefault();
            $($lastLanguage).focus();
        }
      });
    }
  }
})(jQuery);
