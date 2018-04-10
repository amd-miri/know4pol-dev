Module: Suggestion
Author: bkelly bill@williamakelly.com

CONTENTS OF THIS FILE
====================
  * Description
  * Requirements
  * Installation


Description
===========
The suggestion module provides autocomplete suggestions for search fields.

The suggestions are sourced 3 ways:
  1. Content suggestions are parsed from node titles of selected content types.

  2. Priority suggestions are added via the admin interface and take priority
     over all other suggestions.

  3. Surfer suggestions are added when a form is submitted. This organically
     grows and prioritizes the suggestions.

  * For a full description of the module, visit the project page:
    https://drupal.org/project/suggestion

  * To submit bug reports and feature suggestions, or to track changes:
    https://drupal.org/project/issues/suggestion


Requirements
============
  * Drupal 7.x
  * Node
  * Block


Installation
============
  1. Copy the 'suggestion' directory in to your Drupal modules directory.

  2. Enable the module.

  3. Flush the cache.

  4. Go to /admin/config/suggestion and configure the suggestion settings.

  5. After configuration has been saved, index suggestions.


MAINTAINERS
===========
Current maintainers:
  * Bill Kelly (bkelly) - https://drupal.org/user/265918
