/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true, XRegExp:true*/
/**
 * File:        clientside_validation.js
 * Version:     7.x-1.x
 * Description: Add clientside validation rules
 * Author:      Attiks
 * Language:    Javascript
 * Project:     clientside_validation
 * @module clientside_validation
 */


(/** @lends Drupal */function($, Drupal) {
  /**
   * Drupal.behaviors.clientsideValidation.
   *
   * Attach clientside validation to the page or rebind the rules in case of AJAX calls.
   * @extends Drupal.behaviors
   * @fires clientsideValidationAddCustomRules
   * @fires clientsideValidationInitialized
   */
  "use strict";
  Drupal.behaviors.clientsideValidation = {
    attach: function(context) {
      if (typeof (Drupal.settings.clientsideValidation.forms) === 'undefined') {
        return;
      }
      /**
       * Allow other modules to add more rules.
       * @event clientsideValidationAddCustomRules
       * @name clientsideValidationAddCustomRules
       * @memberof Drupal.clientsideValidation
       */
      jQuery.event.trigger('clientsideValidationAddCustomRules');
      // disable class and attribute rules defined by jquery.validate
      $.validator.classRules = function() {
        return {};
      };
      $.validator.attributeRules = function() {
        return {};
      };
      for (var i in Drupal.settings.clientsideValidation.forms) {
        if (Drupal.settings.clientsideValidation.forms.hasOwnProperty(i)) {
          var init = false;
          if (!Drupal.cvInstances[i]) {
            Drupal.cvInstances[i] = new Drupal.clientsideValidation(Drupal.settings.clientsideValidation.forms[i], i);
            init = true;
          }
          else if ($(context).find('#' + i).length || $(context).is('#' + i)) {
            Drupal.cvInstances[i].settings = Drupal.settings.clientsideValidation.forms[i];
            Drupal.cvInstances[i].bindForm();
            init = true;
          }
          if (init) {
            /**
             * Let other modules know we are ready.
             * @event clientsideValidationInitialized
             * @name clientsideValidationInitialized
             * @memberof Drupal.clientsideValidation
             */
            $.event.trigger('clientsideValidationInitialized', [Drupal.cvInstances[i]]);
          }
        }
      }
    }
  };

  Drupal.cvInstances = {};
  Drupal.cvHelpers = {
    debounce: function(func, wait, immediate) {
      var timeout, args, context, timestamp, result;

      var later = function() {
        var last = new Date().getTime() - timestamp;

        if (last < wait && last > 0) {
          timeout = setTimeout(later, wait - last);
        } else {
          timeout = null;
          if (!immediate) {
            result = func.apply(context, args);
            if (!timeout)
              context = args = null;
          }
        }
      };

      return function() {
        context = this;
        args = arguments;
        timestamp = new Date().getTime();
        var callNow = immediate && !timeout;
        if (!timeout) {
          timeout = setTimeout(later, wait);
        }
        if (callNow) {
          result = func.apply(context, args);
          context = args = null;
        }

        return result;
      };
    }
  };

  /**
   * Drupal.clientsideValidation.
   * This module adds clientside validation for all forms and webforms using jquery.validate
   * Don't forget to read the README
   *
   * @class Drupal.clientsideValidation
   * @see https://github.com/jzaefferer/jquery-validation
   */
  Drupal.clientsideValidation = function(settings, form_id) {
    var self = this;
    if (typeof window.time !== 'undefined') {
      // activate by setting clientside_validation_add_js_timing
      self.time = window.time;
    }
    else {
      self.time = {
        start: function() {
        },
        stop: function() {
        },
        report: function() {
        }
      };
    }
    self.time.start('1. clientsideValidation');

    /**
     * prefix to use
     * @memberof Drupal.clientsideValidation
     * @type string
     * @readonly
     * @private
     */
    self.prefix = 'clientsidevalidation-';

    /**
     * form id of the form this validator is for
     * @memberof Drupal.clientsideValidation
     * @type string
     * @readonly
     * @private
     */
    self.form_id = form_id;

    /**
     * the form this validator is for
     * @memberof Drupal.clientsideValidation
     * @type jQuery object
     * @readonly
     * @private
     */
    self.$form = $('#' + self.form_id);

    /**
     * local copy of settings
     * @memberof Drupal.clientsideValidation
     * @type array
     * @readonly
     * @private
     */
    self.settings = settings;

    /**
     * The jQuery validator
     * @memberof Drupal.clientsideValidation
     * @type array
     * @readonly
     */
    self.validator = {};

    /**
     * bind all rules to the form
     * @see Drupal.clientsideValidation.prototype.bindForm
     */
    self.bindForm();
    self.time.stop('1. clientsideValidation');
    self.time.report();
  };

  /**
   * findVerticalTab helper.
   * @memberof Drupal.clientsideValidation
   * @private
   */
  Drupal.clientsideValidation.prototype.findVerticalTab = function($element) {

    // Check for the vertical tabs fieldset and the verticalTab data
    var $fieldset = $element.parents('fieldset.vertical-tabs-pane');
    if (($fieldset.size() > 0) && (typeof ($fieldset.data('verticalTab')) !== 'undefined')) {
      var $tab = $($fieldset.data('verticalTab').item[0]).find('a');
      if ($tab.size()) {
        return $tab;
      }
    }

    // Return null by default
    return null;
  };

  /**
   * findHorizontalTab helper.
   * @memberof Drupal.clientsideValidation
   * @private
   */
  Drupal.clientsideValidation.prototype.findHorizontalTab = function($element) {
    // Check for the vertical tabs fieldset and the verticalTab data
    var $fieldset = $element.parents('fieldset.horizontal-tabs-pane');
    if (($fieldset.size() > 0) && (typeof ($fieldset.data('horizontalTab')) !== 'undefined')) {
      var $tab = $($fieldset.data('horizontalTab').item[0]).find('a');
      if ($tab.size()) {
        return $tab;
      }
    }

    // Return null by default
    return null;
  };

  /**
   * Bind all forms.
   * @memberof Drupal.clientsideValidation
   * @public
   */
  Drupal.clientsideValidation.prototype.bindForm = function() {
    var self = this;
    if (typeof (self.settings) === 'undefined' || self.$form.length < 1) {
      return;
    }
    self.time.start('2. bindForm');
    var errorel = self.prefix + self.form_id + '-errors';
    // Remove any existing validation stuff
    if (self.validator) {
      // Doesn't work :: $('#' + f).rules('remove');
      var form = self.$form.get(0);
      if (typeof (form) !== 'undefined') {
        $.removeData(form, 'validator');
      }
    }

    // Add basic settings
    // todo: find cleaner fix
    // ugly fix for nodes in colorbox
    if (typeof self.$form.validate === 'function') {
      var validate_options = {
        errorClass: 'error',
        messages: self.settings.messages,
        groups: self.settings.groups,
        errorElement: self.settings.general.errorElement,
        unhighlight: function(element, errorClass, validClass) {
          var $tab;
          var $element = $(element);
          // Default behavior
          $element.removeClass(errorClass).addClass(validClass);

          // Sort the classes out for the tabs - we only want to remove the
          // highlight if there are no inputs with errors...
          var $fieldset = $element.parents('fieldset.vertical-tabs-pane');
          if ($fieldset.size() && $fieldset.find('.' + errorClass).not('label').size() === 0) {
            $tab = self.findVerticalTab($element);
            if ($tab) {
              $tab.removeClass(errorClass).addClass(validClass);
            }
          }

          // Same for horizontal tabs
          $fieldset = $element.parents('fieldset.horizontal-tabs-pane');
          if ($fieldset.size() && $fieldset.find('.' + errorClass).not('label').size() === 0) {
            $tab = self.findHorizontalTab($element);
            if ($tab) {
              $tab.removeClass(errorClass).addClass(validClass);
            }
          }
        },
        highlight: function(element, errorClass, validClass) {
          var $element = $(element);
          // Default behavior
          $element.addClass(errorClass).removeClass(validClass);

          // Sort the classes out for the tabs
          var $tab = self.findVerticalTab($element);
          if ($tab) {
            $tab.addClass(errorClass).removeClass(validClass);
          }
          $tab = self.findHorizontalTab($element);
          if ($tab) {
            $tab.addClass(errorClass).removeClass(validClass);
          }
        },
        invalidHandler: function(form, validator) {
          var $tab;
          if (validator.errorList.length > 0) {
            // Check if any of the errors are in the selected tab
            var errors_in_selected = false;
            for (var i = 0; i < validator.errorList.length; i++) {
              $tab = self.findVerticalTab($(validator.errorList[i].element));
              if ($tab && $tab.parent().hasClass('selected')) {
                errors_in_selected = true;
                break;
              }
            }

            // Only focus the first tab with errors if the selected tab doesn't have
            // errors itself. We shouldn't hide a tab that contains errors!
            if (!errors_in_selected) {
              $tab = self.findVerticalTab($(validator.errorList[0].element));
              if ($tab) {
                $tab.click();
              }
            }

            // Same for vertical tabs
            // Check if any of the errors are in the selected tab
            errors_in_selected = false;
            for (i = 0; i < validator.errorList.length; i++) {
              $tab = self.findHorizontalTab($(validator.errorList[i].element));
              if ($tab && $tab.parent().hasClass('selected')) {
                errors_in_selected = true;
                break;
              }
            }

            // Only focus the first tab with errors if the selected tab doesn't have
            // errors itself. We shouldn't hide a tab that contains errors!
            if (!errors_in_selected) {
              $tab = self.findHorizontalTab($(validator.errorList[0].element));
              if ($tab) {
                $tab.click();
              }
            }
            if (self.settings.general.scrollTo) {
              if (!$('html, body').hasClass('cv-scrolling')) {
                var x;
                var $errorel = $("#" + errorel);
                if ($errorel.length) {
                  $errorel.show();
                  x = $errorel.offset().top - $errorel.height() - 100; // provides buffer in viewport
                }
                else {
                  $errorel = $(validator.errorList[0].element);
                  x = $errorel.offset().top - $errorel.height() - 100;
                }
                $('html, body').addClass('cv-scrolling').animate(
                  {scrollTop: x},
                {
                  duration: self.settings.general.scrollSpeed,
                  complete: function() {
                    $('html, body').removeClass('cv-scrolling')
                  }
                }
                );
                $('.wysiwyg-toggle-wrapper a').each(function() {
                  var $self = $(this);
                  $self.click();
                  $self.click();
                });
              }
            }

            /**
             * Notify that the form contains errors.
             * @event clientsideValidationFormHasErrors
             * @name clientsideValidationFormHasErrors
             * @memberof Drupal.clientsideValidation
             */
            jQuery.event.trigger('clientsideValidationFormHasErrors', [form.target]);
          }
        }
      };

      switch (parseInt(self.settings.errorPlacement, 10)) {
        case 0: // CLIENTSIDE_VALIDATION_JQUERY_SELECTOR
          var $errorcontainer = $(self.settings.errorJquerySelector);
          if ($errorcontainer.length) {
            if (!$errorcontainer.find('#' + errorel).length) {
              $('<div id="' + errorel + '" class="messages error clientside-error"><ul></ul></div>').prependTo($errorcontainer).hide();
            }
          }
          else if (!$('#' + errorel).length) {
            $('<div id="' + errorel + '" class="messages error clientside-error"><ul></ul></div>').insertBefore(self.$form).hide();
          }
          validate_options.errorContainer = '#' + errorel;
          validate_options.errorLabelContainer = '#' + errorel + ' ul';
          validate_options.wrapper = 'li';
          break;
        case 1: // CLIENTSIDE_VALIDATION_TOP_OF_FORM
          if (!$('#' + errorel).length) {
            $('<div id="' + errorel + '" class="messages error clientside-error"><ul></ul></div>').insertBefore(self.$form).hide();
          }
          validate_options.errorContainer = '#' + errorel;
          validate_options.errorLabelContainer = '#' + errorel + ' ul';
          validate_options.wrapper = 'li';
          break;
        case 2: // CLIENTSIDE_VALIDATION_BEFORE_LABEL
          validate_options.errorPlacement = function(error, $element) {
            var parents;
            if ($element.is(":radio")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertBefore(parents.find("label").first());
              }
              else {
                parents = $element.parents('.form-radios').prev('label');
                if (!parents.length) {
                  parents = 'label[for="' + $element.attr('id') + '"]';
                }
                error.insertBefore(parents);
              }
            }
            else if ($element.is(":checkbox")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertBefore(parents.find("label").first());
              }
              else {
                parents = $element.parents('.form-radios').prev('label');
                if (!parents.length) {
                  parents = 'label[for="' + $element.attr('id') + '"]';
                }
                error.insertBefore(parents);
              }
            }
            else {
              error.insertBefore('label[for="' + $element.attr('id') + '"]');
            }
          };
          break;
        case 3: // CLIENTSIDE_VALIDATION_AFTER_LABEL
          validate_options.errorPlacement = function(error, $element) {
            var parents;
            if ($element.is(":radio")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertAfter(parents.find("label").first());
              }
              else {
                parents = $element.parents('.form-radios').prev('label');
                if (!parents.length) {
                  parents = 'label[for="' + $element.attr('id') + '"]';
                }
                error.insertAfter(parents);
              }
            }
            else if ($element.is(":checkbox")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertAfter(parents.find("label").first());
              }
              else {
                parents = $element.parents('.form-checkboxes').prev('label');
                if (!parents.length) {
                  parents = 'label[for="' + $element.attr('id') + '"]';
                }
                error.insertAfter(parents);
              }
            }
            else {
              error.insertAfter('label[for="' + $element.attr('id') + '"]');
            }
          };
          break;
        case 4: // CLIENTSIDE_VALIDATION_BEFORE_INPUT
          validate_options.errorPlacement = function(error, $element) {
            error.insertBefore($element);
          };
          break;
        case 5: // CLIENTSIDE_VALIDATION_AFTER_INPUT
          validate_options.errorPlacement = function(error, $element) {
            var parents;
            if ($element.is(":radio")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertAfter(parents);
              }
              else {
                parents = $element.parents('.form-radios');
                if (!parents.length) {
                  parents = $element;
                }
                error.insertAfter(parents);
              }
            }
            else if ($element.is(":checkbox")) {
              parents = $element.parents(".form-type-checkbox-tree");
              if (parents.length) {
                error.insertAfter(parents);
              }
              else {
                parents = $element.parents('.form-checkboxes');
                if (!parents.length) {
                  parents = $element;
                }
                error.insertAfter(parents);
              }
            }
            else if ($element.next('div.grippie').length) {
              error.insertAfter($element.next('div.grippie'));
            } else {
              error.insertAfter($element);
            }
          };
          break;
        case 6: // CLIENTSIDE_VALIDATION_TOP_OF_FIRST_FORM
          var $errorcontainer = $('div.messages.error');
          if ($errorcontainer.length) {
            if ($errorcontainer.attr('id').length) {
              errorel = $('div.messages.error').attr('id');
            }
            else {
              $errorcontainer.attr('id', errorel);
            }
          }
          else if (!$('#' + errorel).length) {
            $('<div id="' + errorel + '" class="messages error clientside-error"><ul></ul></div>').insertBefore(self.$form).hide();
          }
          validate_options.errorContainer = '#' + errorel;
          validate_options.errorLabelContainer = '#' + errorel + ' ul';
          validate_options.wrapper = 'li';
          break;
        case 7: // CLIENTSIDE_VALIDATION_CUSTOM_ERROR_FUNCTION
          validate_options.errorPlacement = function(error, element) {
            var func = self.settings.customErrorFunction;
            self[func](error, element);
          };
          break;
      }

      if (!self.settings.includeHidden) {
        validate_options.ignore = ':input:hidden';
      }
      else {
        validate_options.ignore = '';
      }
      if (self.settings.general.validateTabs) {
        if ($('.vertical-tabs-pane input').length) {
          validate_options.ignore += ' :not(.vertical-tabs-pane :input, .horizontal-tabs-pane :input)';
        }
      }
      else {
        validate_options.ignore += ', .horizontal-tab-hidden :input';
      }
      //Since we can only give boolean false to onsubmit, onfocusout and onkeyup, we need
      //a lot of if's (boolean true can not be passed to these properties).
      if (!Boolean(parseInt(self.settings.general.validateOnSubmit, 10))) {
        validate_options.onsubmit = false;
      }
      if (!Boolean(parseInt(self.settings.general.validateOnBlur, 10))) {
        validate_options.onfocusout = false;
      }
      if (Boolean(parseInt(self.settings.general.validateOnBlurAlways, 10))) {
        validate_options.onfocusout = function(element) {
          if (!this.checkable(element)) {
            this.element(element);
          }
        };
      }
      if (!Boolean(parseInt(self.settings.general.validateOnKeyUp, 10))) {
        validate_options.onkeyup = false;
      }
      // Only apply this setting if errorplacement is set to the top of the form
      if (parseInt(self.settings.general.showMessages, 10) > 0 && parseInt(self.settings.errorPlacement, 10) === 1) {
        var showMessages = parseInt(self.settings.general.showMessages, 10);
        // Show only last message
        if (showMessages === 2) {
          validate_options.showErrors = function() {
            var validator = this;
            var allErrors = validator.errors();
            var i;

            validator.toHide = allErrors;
            $(':input.' + validator.settings.errorClass).removeClass(validator.settings.errorClass);
            for (i = validator.errorList.length - 1; validator.errorList[i]; i++) {
              var error = validator.errorList[i];
              validator.settings.highlight && validator.settings.highlight.call(validator, error.element, validator.settings.errorClass, validator.settings.validClass);
              validator.showLabel(error.element, error.message);
            }
            if (validator.errorList.length) {
              validator.toShow = validator.toShow.add(validator.containers);
            }
            if (validator.settings.success) {
              for (i = 0; validator.successList[i]; i++) {
                this.showLabel(validator.successList[i]);
              }
            }
            if (validator.settings.unhighlight) {
              var elements;
              for (i = 0, elements = validator.validElements(); elements[i]; i++) {
                validator.settings.unhighlight.call(validator, elements[i], validator.settings.errorClass, validator.settings.validClass);
              }
            }
            validator.toHide = validator.toHide.not(validator.toShow);
            validator.hideErrors();
            validator.addWrapper(validator.toShow).show();
          };
        }
        // Show only first message
        else if (showMessages === 1) {
          validate_options.showErrors = function() {
            var validator = this;
            var allErrors = validator.errors();
            var i;
            var elements;
            if (validator.settings.unhighlight) {
              var firstErrorElement = validator.clean($(allErrors[0]).attr('for'));
              //for attr points to name or id
              if (typeof firstErrorElement === 'undefined') {
                firstErrorElement = validator.clean('#' + $(allErrors[0]).attr('for'));
              }
              for (i = 0, elements = validator.elements().not($(firstErrorElement)); elements[i]; i++) {
                this.settings.unhighlight.call(validator, elements[i], validator.settings.errorClass, validator.settings.validClass);
              }
            }

            for (i = 0; validator.errorList[i] && i < 1; i++) {
              var error = validator.errorList[i];
              validator.settings.highlight && validator.settings.highlight.call(validator, error.element, validator.settings.errorClass, validator.settings.validClass);
              validator.showLabel(error.element, error.message);
            }
            if (validator.errorList.length) {
              validator.toShow = this.toShow.add(validator.containers);
            }
            if (validator.settings.success) {
              for (i = 0; validator.successList[i]; i++) {
                validator.showLabel(validator.successList[i]);
              }
            }
            if (validator.settings.unhighlight) {
              for (i = 0, elements = validator.validElements(); elements[i]; i++) {
                validator.settings.unhighlight.call(validator, elements[i], validator.settings.errorClass, validator.settings.validClass);
              }
            }

            validator.toHide = validator.toHide.not(validator.toShow);
            validator.hideErrors();
            validator.addWrapper(validator.toShow).show();
            allErrors = validator.errors();
            allErrors.splice(0, 1);
            validator.toHide = allErrors;
            validator.hideErrors();
          };
        }
      }
      /**
       * Let other modules alter the validation options for this form.
       * @event clientsideValidationAddCustomOptions
       * @name clientsideValidationAddCustomOptions
       * @memberof Drupal.clientsideValidation
       */
      $.event.trigger('clientsideValidationAddCustomOptions', [validate_options, self]);
      self.validator = self.$form.validate(validate_options);

      // Disable HTML5 validation
      if (!Boolean(parseInt(self.settings.general.disableHtml5Validation, 10))) {
        self.$form.removeAttr('novalidate');
      }
      else {
        self.$form.attr('novalidate', 'novalidate');
      }
      // Bind all rules
      self.bindRules();

    }
    self.time.stop('2. bindForms');
  };

  /**
   * Bind all rules.
   * @memberof Drupal.clientsideValidation
   */
  Drupal.clientsideValidation.prototype.bindRules = function() {
    var self = this;
    self.time.start('3. bindRules');
    var hideErrordiv = function() {
      //wait just one milisecond until the error div is updated
      window.setTimeout(function() {
        var visibles = 0;
        // @TODO: check settings
        $(".clientside-error ul li").each(function() {
          if ($(this).is(':visible')) {
            visibles++;
          }
          else {
            $(this).remove();
          }
        });
        if (visibles < 1) {
          $(".clientside-error").hide();
        }
      }, 1);
    };

    if ('rules' in self.settings) {
      self.time.start('rules');
      // Make sure we are working with the copy of rules object.
      var rules = $.extend(true, {}, self.settings.rules);
      // :input can be slow, see http://jsperf.com/input-vs-input/2
      self.$form.find('input, textarea, select').each(function(idx, elem) {
        var rule = rules[elem.name];
        if (rule) {
          var $elem = $(elem);
          $elem.rules("add", rule);
          $elem.change(hideErrordiv);
        }
      });
      self.time.stop('rules');
    }
    self.time.stop('3. bindRules');
  };

  /**
   * Add extra rules.
   * @memberof Drupal.clientsideValidation
   */
  Drupal.clientsideValidation.prototype.addExtraRules = function() {
    var self = this;
    // EAN code
    $.validator.addMethod("validEAN", function(value, element) {
      if (this.optional(element) && value === '') {
        return this.optional(element);
      }
      else {
        if (value.length > 13) {
          return false;
        }
        else if (value.length !== 13) {
          value = '0000000000000'.substr(0, 13 - value.length).concat(value);
        }
        if (value === '0000000000000') {
          return false;
        }
        if (isNaN(parseInt(value, 10)) || parseInt(value, 10) === 0) {
          return false;
        }
        var runningTotal = 0;
        for (var c = 0; c < 12; c++) {
          if (c % 2 === 0) {
            runningTotal += 3 * parseInt(value.substr(c, 1), 10);
          }
          else {
            runningTotal += parseInt(value.substr(c, 1), 10);
          }
        }
        var rem = runningTotal % 10;
        if (rem !== 0) {
          rem = 10 - rem;
        }

        return rem === parseInt(value.substr(12, 1), 10);

      }
    }, jQuery.validator.format('Not a valid EAN number.'));




  };

  Drupal.behaviors.ZZZClientsideValidation = {
    attach: function() {
      function changeAjax(ajax_el) {
        var origBeforeSubmit = Drupal.ajax[ajax_el].options.beforeSubmit;
        Drupal.ajax[ajax_el].options.beforeSubmit = function(form_values, element, options) {
          var ret = origBeforeSubmit(form_values, element, options);
          // If this function didn't return anything, just set the return value to true.
          // If it did return something, allow it to prevent submit if necessary.
          if (typeof ret === 'undefined') {
            ret = true;
          }
          var id = element.is('form') ? element.attr('id') : element.closest('form').attr('id');
          if (id && Drupal.cvInstances[id] && Drupal.cvInstances[id].validator && Drupal.cvInstances[id].validator.form) {
            Drupal.cvInstances[id].validator.onsubmit = false;
            ret = ret && Drupal.cvInstances[id].validator.form();
            if (!ret) {
              Drupal.ajax[ajax_el].ajaxing = false;
            }
          }
          return ret;
        };
      }
      // Set validation for ctools modal forms
      for (var ajax_el in Drupal.ajax) {
        if (Drupal.ajax.hasOwnProperty(ajax_el) && typeof Drupal.ajax[ajax_el] !== 'undefined') {
          var $ajax_el = $(Drupal.ajax[ajax_el].element);
          var ajax_form = $ajax_el.is('form') ? $ajax_el.attr('id') : $ajax_el.closest('form').attr('id');
          var change_ajax = true;
          if (typeof Drupal.cvInstances[ajax_form] !== 'undefined') {
            change_ajax = Boolean(parseInt(Drupal.cvInstances[ajax_form].settings.general.validateBeforeAjax, 10));
          }
          if (!$ajax_el.hasClass('cancel') && change_ajax) {
            changeAjax(ajax_el);
          }
        }
      }
    }
  };
})(jQuery, Drupal);
