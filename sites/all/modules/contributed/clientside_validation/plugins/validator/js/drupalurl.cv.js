/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document, Drupal) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvCoreDrupalUrl = {
    attach: function(context) {
      var fn = Drupal.cvHelpers.debounce(function(value, element, param, validator) {
        $.ajax({
          'url': Drupal.settings.basePath + 'clientside_validation/drupalURL',
          'type': "POST",
          'data': {
            'value': value
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
              message = response.message || validator.defaultMessage(element, "drupalURL");
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
        // Support for Drupal urls.
        $.validator.addMethod("drupalURL", function(value, element, param) {
          if ($.validator.methods.url2.call(this, value, element)) {
            return this.optional(element) || true;
          }
          if (param.absolute === true) {
            return this.optional(element) || false;
          }
          if ( this.optional(element) ) {
            return "dependency-mismatch";
          }
          var validator = this;
          fn(value, element, param, validator);
          return 'pending';
        }, $.validator.format('Please fill in a valid url'));
      });
    }
  };
})(jQuery, document, Drupal);
