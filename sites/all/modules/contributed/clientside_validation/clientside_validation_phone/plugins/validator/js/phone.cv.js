/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document, Drupal) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvPhone = {
    attach: function(context) {
      var fn = Drupal.cvHelpers.debounce(function(value, element, param, validator) {
        $.ajax({
          'url': Drupal.settings.basePath + 'clientside_validation/phone',
          'type': "POST",
          'data': {
            'value': value,
            'country_code': param
          },
          'dataType': 'json',
          'success': function(response) {
            var valid = response.result === true || response.result === "true",
              errors, message, submitted;

            if (valid) {
              submitted = validator.formSubmitted;
              validator.prepareElement(element);
              validator.formSubmitted = submitted;
              validator.successList.push(element);
              delete validator.invalid[element.name];
              validator.showErrors();
            } else {
              errors = {};
              message = response.message || validator.defaultMessage(element, "phone");
              errors[element.name] = $.isFunction(message) ? message(value) : message;
              validator.invalid[element.name] = true;
              validator.showErrors(errors);
              validator.submitted[element.name] = message;
            }
            validator.stopRequest(element, valid);
          }
        });
      }, 200);
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        // Support for phone
        $.validator.addMethod("phone", function(value, element, param) {
          if ( this.optional(element) ) {
            return "dependency-mismatch";
          }
          var validator = this;
          fn(value, element, param, validator);
          return 'pending';

        }, $.validator.format('Please fill in a valid phone number'));
      });
    }
  };
})(jQuery, document, Drupal);
