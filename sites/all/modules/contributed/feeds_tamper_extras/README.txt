CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommended modules
 * Installation
 * Configuration
 * Troubleshooting
 * FAQ
 * Maintainers

INTRODUCTION
------------

The Feeds Tamper Extras module provides some Feeds Tamper plugins and an automatic Feeds generator / destroyer for
exported importers and tampers

  * For a full description of the module, visit the project page:
    https://drupal.org/project/feeds_tamper_extras

  * To submit bug reports and feature suggestions, or to track changes:
    https://drupal.org/project/issues/feeds_tamper_extras

REQUIREMENTS
------------

This module requires the following modules:

 * Feeds (https://drupal.org/project/feeds)
 * Feeds Tamper (https://drupal.org/project/feeds_tamper)

INSTALLATION
------------

Install as you would normally install a contributed Drupal module. See:
https://drupal.org/documentation/install/modules-themes/modules-7 for further information.

CONFIGURATION
-------------

The Feeds Tamper plugins are configured through Feeds Tamper.

The auto-generate feature is enabled by implementing hook_feeds_tamper_extras_importdir. Any .importer.export files in the provided directory(ies) will automatically instantiate the importers and any .tamper.export files will automatically instantiate those tamper export files. The export files should not have the commonly seen <?php> opening tag but should be straight copies of the export definitions provided by Feeds and Feeds Tamper.

Any importers and tampers defined in a module will be automatically created when the module is enabled and automatically destroyed when the module is disabled. Any changes made must be re-exported before they get destroyed and lost.

MAINTAINERS
-----------

Current maintainers:
 * Hugh Kern (geru) - https://drupal.org/user/2778683

