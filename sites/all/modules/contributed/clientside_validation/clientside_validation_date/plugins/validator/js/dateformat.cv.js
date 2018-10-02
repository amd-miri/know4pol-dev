/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document, Drupal) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvDateDateFormat = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        $.validator.addMethod("dateFormat", function(value, element, param) {
          try {
            var parts = value.split(param.splitter);
            var expectedpartscount = 0;
            var day = parseInt(parts[param.daypos], 10);

            var month = parseInt(parts[param.monthpos], 10);
            if (isNaN(month)) {
              var date_parts = param.format.split(param.splitter);
              var full_idx = date_parts.indexOf("F");
              var abbr_idx = date_parts.indexOf("M");
              var mopos = Math.max(full_idx, abbr_idx);
              if (parseInt(mopos) > -1) {
                param.monthpos = mopos;
                date = new Date(parts[param.monthpos] + " 1, 2000");
                month = date.getMonth();
              }
              else {
                if (typeof Drupal.settings.clientsideValidation.general.months[parts[param.monthpos]] !== 'undefined') {
                  month = Drupal.settings.clientsideValidation.general.months[parts[param.monthpos]];
                }
                else {
                  month = new Date(parts[param.monthpos] + " 1, 2000");
                  month = month.getMonth();
                }
              }
            }
            else {
              month--;
            }

            var year = parseInt(parts[param.yearpos], 10);
            var date = new Date();
            var result = true;
            if (param.daypos !== false && parts[param.daypos].toString().length !== parts[param.daypos].length) {
              result = false;
            }
            if (param.monthpos !== false && parts[param.monthpos].toString().length !== parts[param.monthpos].length) {
              result = false;
            }
            if (param.yearpos !== false && parts[param.yearpos].toString().length !== parts[param.yearpos].length) {
              result = false;
            }
            if (param.yearpos !== false) {
              expectedpartscount++;
              date.setFullYear(year);
              if (year !== date.getFullYear()) {
                result = false;
              }
            }
            if (param.monthpos !== false) {
              expectedpartscount++;
              date.setMonth(month, 1);
              if (month !== date.getMonth()) {
                result = false;
              }
            }
            if (param.daypos !== false) {
              expectedpartscount++;
              date.setDate(day);
              if (day !== date.getDate()) {
                result = false;
              }
            }
            if (expectedpartscount !== parts.length) {
              result = false;
            }
            return this.optional(element) || result;
          } catch (e) {
            return this.optional(element) || false;
          }
        }, $.validator.format('The date is not in a valid format'));
      });
    }
  };
})(jQuery, document, Drupal);
