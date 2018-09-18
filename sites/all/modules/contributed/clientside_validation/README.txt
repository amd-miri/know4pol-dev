DESCRIPTION
===========
  This module adds clientside validation for all forms and webforms using
  jquery.validate.js.

INSTALLATION
============
1.  Download and extract the jquery.validate plugin under sites/all/libraries so
    that the jquery.validate.js file can be found under
    sites/all/libraries/jquery.validate/dist/jquery.validate.js

2.  Enable the module and its dependencies as usual. For more detailed
    instructions see
    https://www.drupal.org/documentation/install/modules-themes/modules-7


STATUS
======
  * Validation is added to all forms and webforms (only tested with version 3).
  * The error messages are displayed the same way as without this module, in a
    div above the form.
  * The error messages use the same css classes as drupal does out of the box,
    so you only have to theme it once.
  * Supports the following conditions: Fields that
      - are required
      - have a maximum length
      - must have one of specified extensions
      - must be one of the allowed values
      - can only contain max x elements (checkboxes, multiple selects)
      - must contain minimum x elements (checkboxes, multiple selects)
      - must be greater than a minimum value
      - must be smaller than a maximum value
      - must be a number
      - must be a decimal
      - must equal an other field
      - can not equal an other field
      - must equal a specific value
      - must be an ean number
      - must match a POSIX regex
      - must match a PCRE regex
      - must be a valid e-mail address
      - must be a valid url
      - must be alpha (FAPI validation)
      - must be alphanumeric (FAPI validation)
      - must be valid IPv4 (FAPI validation)
      - must be "alpha dash" (FAPI validation)
    Note: The FAPI validation rules come down to matching a PCRE regex
  * CCK: textfield, textarea, decimal, float, integer, file and image
  * Supports multiple forms on one page
  * Added support for Webform Validation
  * Added support for FAPI Validation
  * D7: Added support for Field Validation
  * Added support for Vertical Tabs (for D6: Vertical Tabs)
  * Supports most of CCK Date
  * Added an option to enclose the field name in quotes (defaults to nothing)
  * Added an option to validate all tabs or only the visible one (defaults to
    all tabs)
  * Added an option to specify on which forms to validate all fields (including
    those hidden) and on which forms only to validate the visible fields
    (defaults to only visible)
  * Added an option to specify on which forms to add Clientside Validation
    (defaults to all forms)
  * Added an option to specify whether or not to use the minified version of
    jquery.validate.js
  * Checkboxes are working
  * Now using jquery.validate 1.8
  * Supports multi page webforms

USAGE
=====
  The only thing this module will do is translate validation rules defined in
  PHP to javascript counter parts, if you mark a field as required it will
  create a javascript rule that checks the field on submit. This means no real
  configuration is needed. You can however configure the settings if you want.

AUTHOR
======
  The author can be contacted for paid customizations of this module as well as
  Drupal consulting and development.
