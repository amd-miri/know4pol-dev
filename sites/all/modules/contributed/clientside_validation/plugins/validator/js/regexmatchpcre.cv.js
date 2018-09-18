/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document, Drupal, window) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvFAPIRegexMatchPCRE = {
    attach: function(context) {
      var fn = Drupal.cvHelpers.debounce(function(value, element, param, validator) {
        $.ajax({
          'url': Drupal.settings.basePath + 'clientside_validation/regex-pcre',
          'type': "POST",
          'data': {
            'value': value,
            'param': param
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
              message = response.message || validator.defaultMessage(element, "regexMatchPCRE");
              errors[element.name] = $.isFunction(message) ? message(value) : message;
              validator.invalid[element.name] = true;
              validator.showErrors(errors);
              validator.submitted[element.name] = message;
            }
            validator.stopRequest(element, valid);
          }
        });
      }, 200);
      // Default regular expression support
      var ajaxPCREfn = function(value, element, param) {
        if ( this.optional(element) ) {
          return "dependency-mismatch";
        }
        var validator = this;
        this.startRequest(element);
        fn(value, element, param, validator);
        return 'pending';
      };

      // Regular expression support using XRegExp
      var xregexPCREfn = function(value, element, param) {
        if (window.XRegExp && window.XRegExp.version) {
          try {
            var result = true;
            for (var i in param.expressions) {
              if (!param.expressions.hasOwnProperty(i)) {
                continue;
              }
              var reg = param.expressions[i];
              var delim = reg.lastIndexOf(reg.charAt(0));
              // Only allow supported modifiers
              var modraw = reg.substr(delim + 1) || '';
              var mod = '';
              if (mod !== '') {
                for (var l = 0; l < 6; l++) {
                  if (modraw.indexOf('gimnsx'[l]) !== -1) {
                    mod += 'gimnsx'[l];
                  }
                }
              }
              reg = reg.substring(1, delim);
              if (!(new XRegExp(reg, mod).test(value))) {
                result = false;
                if (param.messages[i].length) {
                  $.extend($.validator.messages, {
                    "regexMatchPCRE": param.messages[i]
                  });
                }
              }
            }
            return this.optional( element ) || result;
          }
          catch (e) {
            return ajaxPCREfn.call(this, value, element, param);
          }
        }
        else {
          return ajaxPCREfn.call(this, value, element, param);
        }
      };
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        // Decide which one to use
        if (Drupal.settings.clientsideValidation.general.usexregxp) {
          $.validator.addMethod("regexMatchPCRE", xregexPCREfn, $.validator.format('The value does not match the expected format.'));
        }
        else {
          $.validator.addMethod("regexMatchPCRE", ajaxPCREfn, $.validator.format('The value does not match the expected format.'));
        }
      });
    }
  };
})(jQuery, document, Drupal, window);
