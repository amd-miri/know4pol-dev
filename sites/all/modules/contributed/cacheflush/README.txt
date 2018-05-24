-----------------------------------------------------------------------------
FEATURES
-----------------------------------------------------------------------------

The fine granularity of control over cache tables and function makes this 
module the ultimate tool to clear the Drupal caches.

It ships with a predefined set of actions, but it's biggest strength lays 
in it's configuration, where one can build any number of custom presets to 
fit almost any need on both development and production environments.
It is suitable for any role, starting from developers to administrators or 
editors. Access to each preset can be limited by permissions.

It allows mixing core and contrib cache tables and/or functions with low 
level custom rules to always clear just what's necessary, reducing precious 
development time.
Using this module minimizes time spent waiting for all the caches to be 
cleared when you a just need to recognize a new template file, for ex.

3.x

Also starting from version 3.x we are supporting clearing of the memcache and
varnish cache.

Functionalities
 * Configurable cache clear
 * UI for advanced cache clear using 'cache_clear_all()'
 * Clear on cron call
 * Clear on rule call
 * Drush support
 * UI for Varnish cache
 * UI for Memcache cache

Integration

It fully integrates with the Drupal 7 core admin menu, also with the popular
Administration Menu module and the Commerce Kickstart 2.

How to use

* download the module and place it under 'sites/all/modules/contrib' 
  folder with Drush use: drush dl cacheflush
* enable the module from the modules page: 'admin/build/modules'
* configure the setting at the bottom of the page under 
  'admin/structure/cacheflush'


-----------------------------------------------------------------------------
DRUSH SUPPORT
-----------------------------------------------------------------------------

The cacheflush drush submodule offers support to clear cache using the preset 
via drush.

E.g : 'drush cf 1'   (where 1 = to id of entity)
To list options: 'drush cf'

-----------------------------------------------------------------------------
CONTACT
-----------------------------------------------------------------------------

Current maintainer:
* Csaba Balint (balintcsaba) - https://www.drupal.org/u/balintcsaba

-----------------------------------------------------------------------------
CREDITS
-----------------------------------------------------------------------------

This project has been sponsored by:
* REEA
  Long or short, tough or easy, the time spent in our pit-stop will always end
    with a project delivered on time.
  It will always work just like you desired and will drive your product in the
    direction you imagined. Then you will know you were right to stop at a
    single place for all your needs.
  We aren't looking to other teams for magic formulas – quite the opposite. 
    We are being asked for quick and creative solutions. We don't scout for the
    best crew members – we've already hired them. We're not saying we invented 
    the wheel – however we know how to make it spin the fastest.
  We are not just a few. Our "box" is not the biggest one, but all 150 of us are
    in the same place. Thus a problem doesn't travel thousands of kilometres for
    a solution.
  Our experience and expertise offers us an impressive tool-kit that we can use 
    to offer you the best solution. If something is missing from our inventory, 
    we are numerous and good enough to invent that specific something that only 
    you need.
  Don’t trust us just because we know how to spin the words. Try us. Take us for
    a test drive.
