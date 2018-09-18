/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvFieldValidationSelectExact = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $.validator.addMethod("exactlength", function(value, element, param) {
        return this.optional( element ) || ($.validator.methods.min.call(this, value, element, param)
        && $.validator.methods.max.call(this, value, element, param));
      });
    }
  };
})(jQuery, document);
