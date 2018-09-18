/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document, Drupal) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvElementsMinMax = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        /**
         * HTML5 specific rules.
         * @name _bindHTML5Rules
         * @memberof Drupal.clientsideValidation
         * @method
         * @private
         */
        function _getMultiplier(a, b, c) {
          var inta = Number(parseInt(a, 10));
          var mula = a.toString().length - inta.toString().length - 1;

          var intb = parseInt(b, 10);
          var mulb = b.toString().length - intb.toString().length - 1;

          var intc = parseInt(c, 10);
          var mulc = c.toString().length - intc.toString().length - 1;

          var multiplier = Math.pow(10, Math.max(mulc, Math.max(mula, mulb)));
          return (multiplier > 1) ? multiplier : 1;
        }

        $.validator.addMethod("Html5Min", function(value, element, param) {
          var min = param.min;
          var step = param.step;
          var multiplier = _getMultiplier(value, min, step);

          value = parseInt(parseFloat(value) * multiplier, 10);
          min = parseInt(parseFloat(min) * multiplier, 10);

          var mismatch = 0;
          if (param.step !== 'any') {
            step = parseInt(parseFloat(param.step) * multiplier, 10);
            mismatch = (value - min) % step;
          }
          return this.optional(element) || (mismatch === 0 && value >= min);
        }, $.validator.format('Value must be greater than {0} with steps of {1}.'));

        $.validator.addMethod("Html5Max", function(value, element, param) {
          //param[0] = max, param[1] = step;
          var max = param.max;
          var step = param.step;
          var multiplier = _getMultiplier(value, max, step);

          value = parseInt(parseFloat(value) * multiplier, 10);
          max = parseInt(parseFloat(max) * multiplier, 10);

          var mismatch = 0;
          if (param.step !== 'any') {
            step = parseInt(parseFloat(param.step) * multiplier, 10);
            mismatch = (max - value) % step;
          }
          return this.optional(element) || (mismatch === 0 && value <= max);
        }, $.validator.format('Value must be smaller than {0} and must be dividable by {1}.'));

      });
    }
  };
})(jQuery, document, Drupal);
