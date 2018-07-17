[![Build Status](https://travis-ci.org/drupol/registryonsteroids.svg?branch=7.x-1.x)](https://travis-ci.org/drupol/registryonsteroids)

# Registry On Steroids

Registry On Steroids(ROS) discovers and adds additional theme preprocess/process functions for theme hook variants, if `theme()` is called with a variant name. E.g. for `theme('node__article__teaser', ..)`, it will call functions like `MYTHEME_preprocess_node__article__teaser()` and `MYTHEME_preprocess_node__article()` in addition to `MYTHEME_preprocess_node()`.

Without this module, only the process/preprocess functions of the base hook will be called when a theme hook variant is executed. E.g. for `theme('node__article__teaser')`, only the preprocess and process functions for `'node'` are called. See [#2563445](https://www.drupal.org/node/2563445) in the issue queue for Drupal 7.

The module only has an effect if the theme hook is called with a variant hook name. It does not work for theme hook suggestions added to the `$variables` array.

## Background: Theme hook variants

A "theme hook variant" is a specialized version of a base theme hook, with a suffix like "__$x", that is executed instead of the base hook in specific cases.

Based on such theme hook variants, it might execute a specific template `node--article--teaser.tpl.php`, if such a template exists in the active theme or in a module. Otherwise it will fall back to the parent or base template, e.g. `node--article.tpl.php` or `node.tpl.php`. Or, for theme functions, it might execute `THEMENAME_menu_tree__main_menu()` instead of the base function `THEMENAME_menu_tree()` or `theme_menu_tree()`.

Drupal 7 has 4 ways of invoking theme hook variants:
1. The `theme()` function can be called with an array of theme hooks, instead of a single theme hook, e.g. `theme(array('node__article__teaser', 'node__article', 'node'), ..)`.
2. The `theme()` function can be called with a hook name containing double underscores, e.g. `theme('node__article__teaser')`. Drupal will try different substrings of the specified hook until it finds an existing registered theme hook variant.
3. The `theme()` function can be called with theme hook suggestions in the `$variables` array, e.g. `theme('node', $variables)` with `$variables['theme_hook_suggestions'] === array('node__article__teaser', 'node__article')`.
4. After the `theme()` function is called, possibly with just the base hook `'node'`, preprocess functions can register an array of theme hook names or theme hook variant names in `$variables['theme_hook_suggestions']`. Later, these suggestions will be used to determine which template should be rendered, or which theme function should be executed.

The last is currently the most common way to invoke theme hook variants in Drupal 7.

In the theme registry, a theme hook variant is an entry with an `$info['base hook']` setting, pointing to another theme hook. E.g. the entry for `'node__article__teaser'`, if it exists, would have `$registry['node__article__teaser']['base hook'] === 'node'`.

The base theme hooks themselves, e.g. `'node'`, do not have a `'base hook'` setting.

## Background: (Pre)process functions

Before calling the theme function or including the template, `theme()` will execute a series of preprocess and process functions registered for this theme hook. The functions are discovered based on their function name in a clearly defined order, but this array can be modified by modules with `[hook_theme_registry_alter()](https://api.drupal.org/api/drupal/modules%21system%21system.api.php/function/hook_theme_registry_alter/7.x)`.

E.g. for `theme('node', ..)`, all existing functions like `template_preprocess_node()`, `MYMODULE_preprocess_node()` or `MYTHEME_preprocess_node()` will be executed.

Some modules use `hook_theme_registry_alter()` to register additional functions for specific theme hooks, e.g. [Display Suite](https://drupal.org/project/ds) registers a function `ds_entity_variables()` as a preprocessor for all entity theme hooks.

When calling a theme hook variant like `theme('node__article__teaser', ..)`, only the base hook preprocess functions like `MYTHEME_preprocess_node()` are executed. Variant preprocess functions like `MYTHEME_preprocess_node__article__teaser()` are not discovered and not called.

The variant preprocess functions used to work (more or less) in Drupal 6, so this could be seen as a regression in Drupal 7.

## This module

This module modifies the theme registry in the following way:
- Entries for base hooks are not changed.
- Existing entries for variants, e.g. if a template like `node--article--teaser.tpl.php` was discovered, are modified so that variant-specific preprocess and process functions are called in addition to those of the base hook. Functions that were added by contrib modules, like `ds_entity_variables` added by Display Suite, are preserved as if the module had added the function on the variant itself.
- New variant entries are created for discovered preprocess/process functions where an entry does not exist yet. E.g. if a preprocess function `MYTHEME_preprocess_node__webform__full` is found, then a new entry for `$registry['node__webform__full']` and `$registry['node__webform']` will be created, even if no template like `node--webform--full.tpl.php` or `node--webform.tpl.php` exists.
- Provides a configuration form where you can enable or disable the `theme_debug` option available [since Drupal 7.33](https://www.drupal.org/node/223440#theme-debug).
- Provides an option to enable the rebuild of the registry at each page load.

## Submodule "registryonsteroids_alter"

This module modifies render arrays in multiple Drupal places so that `$element['#theme']` refers to a hook variant instead of a base hook.

We alter the render arrays to dynamically replace e.g. `'#theme' => 'node'` by `'#theme' => 'node__article__teaser'` based on the value that we found in the render array, e.g. node type, entity bundle and entity view mode.

By default, Drupal calculate and set `$variables['theme_hook_suggestions']` during preprocess callbacks.
Those callbacks are either added through a preprocess callback and/or either calculated using the `$element['#theme']` value.

E.g:
- [template_preprocess_node()](https://api.drupal.org/api/drupal/modules%21node%21node.module/function/template_preprocess_node/7.x)
- [template_preprocess_entity()](http://www.drupalcontrib.org/api/drupal/contributions%21entity%21theme%21entity.theme.inc/function/template_preprocess_entity/7)
- [ds_entity_variables()](http://www.drupalcontrib.org/api/drupal/contributions%21ds%21ds.module/function/ds_entity_variables/7)

When updating and extending the value of `$element['#theme']`, Drupal will automatically update the `$variables['theme_hook_suggestions']` accordingly.

Without "_registryonsteroids_alter_", we would still get some or all of the template suggestions, depending which other modules are installed.

# Installation

- Manually: download the module with required dependencies
- Composer: `composer require drupal/registryonsteroids`
- Drush: `drush en registryonsteroids`

# Dependencies

- [xautoload](https://www.drupal.org/project/xautoload)
- If the contrib module "[Alternatives](https://www.drupal.org/project/alternatives)" is available, the user is able to choose between the [xautoload](https://www.drupal.org/project/xautoload) or [registry_autoload](https://www.drupal.org/project/registry_autoload) PHP class loading suite.

# More details

When it comes to rendering a theme hook, through [a render array](https://www.drupal.org/docs/7/api/render-arrays/render-arrays-overview) or [the theme function](https://api.drupal.org/api/drupal/includes!theme.inc/function/theme/7.x), the Drupal's 7 default behavior is to run a set of callbacks for preprocessing and a set of callbacks to be processed in [a particular order](https://api.drupal.org/api/drupal/includes!theme.inc/function/theme/7.x).

E.g. You're using the Bartik core theme and you want to render a `node` using some new variants based on the bundle name and its view mode so you would be able to use specific template suggestion.

Instead of using `theme('node', [...]);`, you will be able to use added variant of the `node` theme hook like: `theme('node__page__full', [...]);`.

Then, in your theme or module, you create a preprocess function: `[HOOK]_preprocess_node__page__full(&$variables, $hook);` to only alter variables of that specific theme hook variation.

When rendering your node, Drupal will run the preprocess callbacks in the following order:

* [template_preprocess()](https://api.drupal.org/api/drupal/includes%21theme.inc/function/template_preprocess/7.x)
* [template_preprocess_node()](https://api.drupal.org/api/drupal/modules%21node%21node.module/function/template_preprocess_node/7.x)
* [bartik_preprocess_node()](https://api.drupal.org/api/drupal/themes%21bartik%21template.php/function/bartik_preprocess_node/7.x)

Once those preprocess are executed, Drupal will try to render the theme hook.
The theme hook `node__page__full` does not exist per se, so Drupal will try to render its first parent theme hook: `node__page`, but in our case, it does not exist either.
So Drupal will continue and iterate until a valid theme hook is found, in this case: `node`, the very base hook.

It seems that by default, Drupal never executes any variant theme (pre)processors.
It only ever executes the (pre)processors callbacks from the very base hook, in this case, it is a `node`.

This module updates this default behavior and let Drupal use "_intermediary_" or "_derivative_" preprocess/process callbacks.

An issue is open on drupal.org to fix this behavior, see [#2563445](https://www.drupal.org/node/2563445).
            
# Steps to reproduce the issue locally:

* Use admin theme `seven`.
* Disable the module `registryonsteroids` and `registryonsteroids_alter`.
* Enable contrib `devel` module.

* Add functions to `themes/seven/template.php`:

```php
function seven_preprocess_node(array &$vars) {
  dpm(__FUNCTION__);
}

function seven_preprocess_node__page(array &$vars) {
  dpm(__FUNCTION__);
}

function seven_preprocess_node__page__full(array &$vars) {
  dpm(__FUNCTION__);
}
```

* Clear the cache to rebuild the theme registry and let Drupal detect the new functions.

* Create a node of type page and remember its node id.

* Run this test code in `/devel/php`:
```php
$node = node_load(1); //  (1 is the node id of the node you just created)
dpm($node, '$node');
$element = node_view($node);
dpm($element);
$element['#theme'] = 'node__page__full';
drupal_render($element);
```

* Enable module `registryonsteroids`
             
* Run the same test code and see the differences.
             
# History

The code of this module comes from [Atomium](https://www.drupal.org/project/atomium), a Drupal 7 base theme that implements all of this in a theme.
Started as a proof of concept, the idea behind this module is to remove from Atomium the code that alters the theme registry and make it available for anyone through a module so every Drupal 7 site is able to enjoy these enhancements.

Then the idea of the module has been shared with [Andreas Hennings](https://www.drupal.org/u/donquixote) who rewrote the algorithm and made it even more consistent using object-oriented programming.

# Issues to follow

This module is watching issues on drupal.org. Once these issues are fixed, we'll be able to update this module and hopefully deprecate it at a certain point.

* [#1119364](https://www.drupal.org/node/1119364)
* [#1545964](https://www.drupal.org/node/1545964)
* [#2563445](https://www.drupal.org/node/2563445)

Feel free to test patches from these issues and give your feedback so we can move them forward.

# Tests

To run the tests locally:

* `git clone https://github.com/drupol/registryonsteroids.git`
* `composer install`

Then if you want to modify the default settings of the Drupal installation, please copy the file `runner.yml.dist` into `runner.yml` and update that file accordingly to your configuration.

* `./vendor/bin/run drupal:site-install`

At this point, the Drupal installation will be in the `build` directory.

To run the test properly, you must make sure that a web server is started on this directory.

Run this command in a new terminal: `cd build; ../vendor/bin/drush rs`

Then, you are able to run the tests:

* `./vendor/bin/grumphp run`

# Authors

* [Andreas Hennings](https://www.drupal.org/u/donquixote)
* [Pol Dellaiera](http://drupal.org/u/pol)

# Contributors

* [Mark Carver](https://www.drupal.org/u/markcarver)
* [Robert Czarny](https://www.drupal.org/u/netlooker)
