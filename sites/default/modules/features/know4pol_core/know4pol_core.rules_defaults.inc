<?php

/**
 * @file
 * know4pol_core.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function know4pol_core_default_rules_configuration() {
  $items = array();
  $items['rules_autopublish_imported_content'] = entity_import('rules_config', '{ "rules_autopublish_imported_content" : {
      "LABEL" : "Autopublish imported content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "feeds" ],
      "ON" : {
        "feeds_import_bioeconomy_datasets_import" : [],
        "feeds_import_kcmd_datasets_import" : [],
        "feeds_import_kcmd_dgs_import" : [],
        "feeds_import_kcmd_keyword_import" : [],
        "feeds_import_kcmd_networks_import" : [],
        "feeds_import_kcmd_other_organisation_import" : [],
        "feeds_import_kcmd_project_import" : [],
        "feeds_import_kcmd_stakeholders_import" : [],
        "feeds_import_kcmd_web_portals_import" : [],
        "feeds_import_pubsy_import" : [],
        "feeds_import_pubsy_update_specific_date" : [],
        "feeds_import_pubsy_update" : [],
        "feeds_import_jrc_datasets_import" : []
      },
      "DO" : [ { "node_publish" : { "node" : [ "node" ] } } ]
    }
  }');
  $items['rules_redirection_online_ressource'] = entity_import('rules_config', '{ "rules_redirection_online_ressource" : {
      "LABEL" : "Redirection online ressource",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--online_resource" : { "bundle" : "online_resource" } },
      "IF" : [
        { "data_is" : { "data" : [ "view-mode" ], "value" : "full" } },
        { "node_is_published" : { "node" : [ "node" ] } },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "2" : "2" } }
          }
        },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_url" } },
        { "NOT data_is_empty" : { "data" : [ "node:field-url:url" ] } }
      ],
      "DO" : [ { "redirect" : { "url" : [ "node:field-url:url" ] } } ]
    }
  }');
  $items['rules_site_message_for_logged_in_users'] = entity_import('rules_config', '{ "rules_site_message_for_logged_in_users" : {
      "LABEL" : "Site message for logged in users",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "system" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "2" : "2" } }
          }
        },
        { "data_is" : { "data" : [ "view-mode" ], "value" : "full" } }
      ],
      "DO" : [ { "component_rules_site_messages" : { "thenode" : [ "node" ] } } ]
    }
  }');
  $items['rules_site_messages'] = entity_import('rules_config', '{ "rules_site_messages" : {
      "LABEL" : "Site messages",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "thenode" : { "label" : "Node viewed", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "thenode" ],
                  "type" : { "value" : { "publication" : "publication" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_pub_dc_rel_ispartofseries" } },
              { "NOT data_is_empty" : { "data" : [ "thenode:field-pub-dc-rel-ispartofseries" ] } }
            ],
            "DO" : [
              { "drupal_message" : { "message" : "This is a PUBSY publication, when viewed by other users, it will redirect to the full page of the PUBSY publication outside K4P" } }
            ],
            "LABEL" : "Pubsy publication redirect"
          }
        },
        { "RULE" : {
            "IF" : [
              { "AND" : [
                  { "entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_legacy_link" } },
                  { "NOT data_is_empty" : { "data" : [ "thenode:field-legacy-link:url" ] } },
                  { "OR" : [
                      { "NOT entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_is_legacy_link" } },
                      { "AND" : [
                          { "entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_is_legacy_link" } },
                          { "data_is" : { "data" : [ "thenode:field-is-legacy-link" ], "value" : "1" } }
                        ]
                      }
                    ]
                  }
                ]
              }
            ],
            "DO" : [
              { "drupal_message" : { "message" : "This content has a legacy link set. When viewed by non connected users, it will redirect to: [thenode:field-legacy-link:url]" } }
            ],
            "LABEL" : "Content has legacy link activated"
          }
        },
        { "RULE" : {
            "IF" : [
              { "entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_internal_note" } },
              { "NOT data_is_empty" : { "data" : [ "thenode:field-internal-note" ] } }
            ],
            "DO" : [
              { "drupal_message" : { "message" : "Internal note on this content: \\u0022[thenode:field-internal-note]\\u0022" } }
            ],
            "LABEL" : "Internal note display"
          }
        },
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "thenode" ],
                  "type" : { "value" : { "projects_activities" : "projects_activities" } }
                }
              },
              { "data_is" : { "data" : [ "thenode:field-redirect-to-cordis-project" ], "value" : "1" } },
              { "NOT data_is_empty" : { "data" : [ "thenode:field-cordis-project-id" ] } }
            ],
            "DO" : [
              { "drupal_message" : { "message" : "This content has a redirection to Cordis project page set. When viewed by non connected users, it will do the redirection." } }
            ],
            "LABEL" : "Cordis redirection on projects has been enabled"
          }
        },
        { "RULE" : {
            "IF" : [
              { "node_is_of_type" : {
                  "node" : [ "thenode" ],
                  "type" : { "value" : { "online_resource" : "online_resource" } }
                }
              },
              { "entity_has_field" : { "entity" : [ "thenode" ], "field" : "field_url" } },
              { "NOT data_is_empty" : { "data" : [ "thenode:field-url:url" ] } }
            ],
            "DO" : [
              { "drupal_message" : { "message" : "When viewed by other users, this page will redirect to [thenode:field-url:url]" } }
            ],
            "LABEL" : "Online ressource"
          }
        }
      ]
    }
  }');
  return $items;
}
