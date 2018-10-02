/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvFieldValidationRegexMatch = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        $.validator.addMethod("regexMatch", function(value, element, param) {
          if (this.optional(element) && value === '') {
            return this.optional(element);
          }
          else {
            var regexp = new RegExp(param);
            return regexp.test(value);
          }
        }, $.validator.format('The value does not match the expected format.'));
      });
    }
  };
})(jQuery, document);
