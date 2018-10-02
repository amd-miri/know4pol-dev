/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvWebformNotEqualTo = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        // Unique values
        $.validator.addMethod("notEqualTo", function(value, element, param) {
          var ret = true;
          $.each(param, function(index, selector) {
            var $target = $(selector);
            $target.unbind(".validate-notEqualTo").bind("blur.validate-notEqualTo", function() {
              $(element).valid();
            });
            ret = ret && ($target.val() !== value);
          });
          return this.optional( element ) || ret;
        }, $.validator.format('Please don\'t enter the same value again.'));
      });
    }
  };
})(jQuery, document);
