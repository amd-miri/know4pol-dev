/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function ($, document) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvFieldValidationOneOf = {
    attach: function (context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event){
        // One of the values
        $.validator.addMethod("oneOf", function(value, element, param) {
          for (var p in param.values) {
            if (param.values[p] === value && param.caseSensitive) {
              return this.optional( element ) || !param.negate;
            }
            else if (param.values[p].toLowerCase() === value.toLowerCase() && !param.caseSensitive) {
              return this.optional( element ) || !param.negate;
            }
          }
          return this.optional( element ) || param.negate;
        }, $.validator.format(''));
      });
    }
  };
})(jQuery, document);
