ACKNOWLEDGEMENTS

As this is the next evolution of Corresponding Node References,
I would like to say thanks for all the work done over on Corresponding Node
References.

DESCRIPTION

It syncs the entity reference between two entity types which have an entity
reference to each other, so double editing entities is no longer needed. If one
entity has a reference, the other entity also receives a reference to the saved
entity if it is referenced in that entity.

DEPENDENCIES

7.x: Entity Reference

EXAMPLE

Entity type A has an entity reference to entity type B and entity type B has an
entity reference to entity type A. When you create entity X of type A and
reference it to entity Y of type B entity Y will also receive an update in its
entity reference field pointing to entity X.

KNOWN ISSUES

- Support for entity reference fields in field collections is still a work in progress.
  CER has no native support for entities that are wrapped by other entities (i.e.,
  field collections), and implementing this properly will require extensive changes
  to many parts of CER. For this reason, field collection support is on hold until
  a few other major issues in the queue are sorted out. The thread for field collection
  support is http://drupal.org/node/1729666.

- Support for multi-language entities is, at the time of this writing, flaky at best.
  There is a patch to implement better multi-language support, available at
  http://drupal.org/node/1961026. If this patch works well for you, PLEASE post
  in that issue to say that it worked so that the patch can be reviewed by
  the community before being committed into CER.

- If you're updating CER from 1.x to 2.x, you should rebuild your theme registry.
  This is because the reference labels on CER's admin page were made themeable
  in 2.x, so you'll need to make Drupal recognize the new theme hook.

INSTALL

- To install enable the module at admin/build/modules
- Create entity type A
- Create entity type B
- Create a entity reference field on entity type A pointing to entity B
- Create a entity reference field on entity type B pointing to entity A
- Go to the settings page at admin/config/system/cer. 
  Select to enable the corresponding referencing for these node types pointing 
  to each other.
- Create some entities and reference them to each other

MAINTAINER

Questions, comments, etc. should be directed to phenaproxima (djphenaproxima@gmail.com).