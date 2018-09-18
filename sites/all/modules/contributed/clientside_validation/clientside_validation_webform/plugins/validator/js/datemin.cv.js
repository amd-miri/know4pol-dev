/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true*/
/**
 * @file
 * Decimal comma validator.
 */
(function($, document) {
  "use strict";
  //Define a Drupal behaviour with a custom name
  Drupal.behaviors.cvDateMin = {
    attach: function(context) {
      // Add an eventlistener to the document reacting on the
      // 'clientsideValidationAddCustomRules' event.
      $(document).bind('clientsideValidationAddCustomRules', function(event) {
        $.validator.addMethod("datemin", function(value, element, param) {
          //Assume [month], [day], and [year] ??
          var dayelem, monthelem, yearelem, name, $form, element_name;
          $form = $(element).closest('form');
          element_name = $(element).attr('name');
          if (element_name.indexOf('[day]') > 0) {
            dayelem = $(element);
            name = dayelem.attr('name').replace('[day]', '');
            monthelem = $form.find("[name='" + name + "[month]']");
            yearelem = $form.find("[name='" + name + "[year]']");
          }
          else if (element_name.indexOf('[month]') > 0) {
            monthelem = $(element);
            name = monthelem.attr('name').replace('[month]', '');
            dayelem = $form.find("[name='" + name + "[day]']");
            yearelem = $form.find("[name='" + name + "[year]']");
          }
          else if ($(element).attr('name').indexOf('[year]') > 0) {
            yearelem = $(element);
            name = yearelem.attr('name').replace('[year]', '');
            dayelem = $form.find("[name='" + name + "[day]']");
            monthelem = $form.find("[name='" + name + "[month]']");
          }

          if (parseInt(yearelem.val(), 10) < parseInt(param[0], 10)) {
            return this.optional( element ) || false;
          }
          else if (parseInt(yearelem.val(), 10) === parseInt(param[0], 10)) {
            if (parseInt(monthelem.val(), 10) < parseInt(param[1], 10)) {
              return this.optional( element ) || false;
            }
            else if (parseInt(monthelem.val(), 10) === parseInt(param[1], 10)) {
              if (parseInt(dayelem.val(), 10) < parseInt(param[2], 10)) {
                return this.optional( element ) || false;
              }
            }
          }
          yearelem.once('daterange', function() {
            $(this).change(function() {
              $(this).trigger('focusout').trigger('blur');
            });
          }).removeClass('error');
          monthelem.once('daterange', function() {
            $(this).change(function() {
              $(this).trigger('focusout').trigger('blur');
            });
          }).removeClass('error');
          dayelem.once('daterange', function() {
            $(this).change(function() {
              $(this).trigger('focusout').trigger('blur');
            });
          }).removeClass('error');
          return this.optional( element ) || true;
        });
      });
    }
  };
})(jQuery, document);
