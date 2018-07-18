# Registry On Steroids "Alter"

This module modifies render arrays in multiple Drupal places so that `$element['#theme']` refers to a hook variant instead of a base hook.

We alter the render arrays to dynamically replace e.g. `'#theme' => 'node'` by `'#theme' => 'node__article__teaser'` based on the value that we found in the render array, e.g. node type, entity bundle and entity view mode.

By default, Drupal calculate and set `$variables['theme_hook_suggestions']` during preprocess callbacks.
Those callbacks are either added through a preprocess callback and/or either calculated using the `$element['#theme']` value.

Example:
- [template_preprocess_node()](https://api.drupal.org/api/drupal/modules%21node%21node.module/function/template_preprocess_node/7.x)
- [template_preprocess_entity()](http://www.drupalcontrib.org/api/drupal/contributions%21entity%21theme%21entity.theme.inc/function/template_preprocess_entity/7)
- [ds_entity_variables()](http://www.drupalcontrib.org/api/drupal/contributions%21ds%21ds.module/function/ds_entity_variables/7)

When updating and extending the value of `$element['#theme']`, Drupal will automatically update the `$variables['theme_hook_suggestions']` accordingly.

Without "_registryonsteroids_alter_", we would still get some or all of the template suggestions, depending which other modules are installed.
