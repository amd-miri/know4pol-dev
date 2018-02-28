<?php

/**
 * @file
 * Documentation of Beancount Feeds hooks.
 */

/** Feeds Plus creates Feeds importers and associated tampers automatically
 * when enabled, and deletes them when disabled.
 *
 * Feeds importers and tampers are searched for and found automatically under
 * various root source directories. They must have extensions "importer.export"
 * and "tamper.export", respectively.
 *
 * Unlike PHP include files, the ".export" files are raw PHP code as exported
 * when using the associated export functionality and DO NOT include the leading
 * '<?php' tag of ordinary include files.
 *
 * .export files are found under root directories exposed by the
 * hook_feeds_tamper_extras_importdir() hook
 * 
 * Feeds_Plus also includes three Plus tamper plugins:
 * - PHP Plus which deals with multi-input and handles NULL return values
 * - Rewrite Plus which deals with multi-input and handles NULL return values
 * - Property by Property which performs database fetches
 *
 * @{
 */

/**
 * Example of a feeds_tamper_extras import directory hook that needs to be
 * implemented to make the .export files under that directory discoverable by
 * feeds_tamper_extras. The hook simply identifies a root directory having .export
 * files to be automatically found and imported into Feeds. The directory will
 * be searched
 *
 * This directory will be found when feeds_tamper_extras is enabled and all the
 * feeds importers and tampers in it will be instantiated. Likewise, they will
 * all be destroyed when feeds_tamper_extras is disabled.
 *
 * WARNING: This means that if you have a feed importer or tamper that has been
 * generated this way, and you modify that feed, you MUST export your changes
 * manually and save them before disabling this module or ALL OF YOUR CHANGES
 * WILL BE LOST.
 */


/**
 * Implements hook_feeds_tamper_extras_importdir()
 * Any importer or tamper below the ./importers directory will be found and
 * automatically created on enable and deleted on disable.
 * Importers must be named *.importer.export
 * Tampers must be named *.tamper.export
 * Importers and tampers MUST BE THE EXACT CODE exported by Feeds or 
 * Feeds_tamper and DO NOT INCLUDE a leading <?php tag
 */
function module_feeds_tamper_extras_importdir() {
  return __DIR__ . '/importers';
}


