<?php
/**
 * @file
 * This is the api documentation for clientside validation hooks.
 */

/**
 * Some modules allow users to define extra validation rules defined in a hook.
 * (e.g hook_webform_validation_validators()). To support these custom rules,
 * you must implement a ctools plugin.
 *
 * Just implement hook_ctools_plugin_directory so Clientside Validation knows
 * where to find the plugins. There are a lot of good examples in the
 * clientside_validation_forms module. All plugin classes must extend the
 * ClientsideValidationValidator class provided by the Clientside Validation
 * module.
 */
function hook_ctools_plugin_directory($module, $plugin) {
  if ($module == 'clientside_validation') {
    return 'plugins/' . $plugin;
  }
}
