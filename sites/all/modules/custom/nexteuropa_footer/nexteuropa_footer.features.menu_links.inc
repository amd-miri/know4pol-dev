<?php
/**
 * @file
 * nexteuropa_footer.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function nexteuropa_footer_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-nexteuropa-inst-links_eu-institutions:https://europa.eu/european-union/about-eu/institutions-bodies_en.
  $menu_links['menu-nexteuropa-inst-links_eu-institutions:https://europa.eu/european-union/about-eu/institutions-bodies'] = array(
    'menu_name' => 'menu-nexteuropa-inst-links',
    'link_path' => 'https://europa.eu/european-union/about-eu/institutions-bodies',
    'router_path' => '',
    'link_title' => 'EU institutions',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-inst-links_eu-institutions:https://europa.eu/european-union/about-eu/institutions-bodies',
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -45,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: menu-nexteuropa-inst-links_european-union:https://europa.eu/.
  $menu_links['menu-nexteuropa-inst-links_european-union:https://europa.eu/european-union/index'] = array(
    'menu_name' => 'menu-nexteuropa-inst-links',
    'link_path' => 'https://europa.eu/european-union/index',
    'router_path' => '',
    'link_title' => 'European Union',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-inst-links_european-union:https://europa.eu/european-union/index',
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -44,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-service-links_about-the-commissions-new-web-presence:https://ec.europa.eu/info/about-commissions-new-web-presence.
  $menu_links['menu-nexteuropa-service-links_about-the-commissions-new-web-presence:https://ec.europa.eu/info/about-commissions-new-web-presence'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'https://ec.europa.eu/info/about-commissions-new-web-presence',
    'router_path' => '',
    'link_title' => 'About the Commission\'s new web presence',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
      'identifier' => 'menu-nexteuropa-service-links_about-the-commissions-new-web-presence:https://ec.europa.eu/info/about-commissions-new-web-presence',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-service-links_contact:https://ec.europa.eu/info/contact.
  $menu_links['menu-nexteuropa-service-links_contact:https://ec.europa.eu/info/contact'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'https://ec.europa.eu/info/contact',
    'router_path' => '',
    'link_title' => 'Contact',
    'options' => array(
      'title' => 'http://ec.europa.eu/info/contact',
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-service-links_contact:https://ec.europa.eu/info/contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 21,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-service-links_cookies:https://ec.europa.eu/info/cookies_en.
  $menu_links['menu-nexteuropa-service-links_cookies:https://ec.europa.eu/info/cookies'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'https://ec.europa.eu/info/cookies',
    'router_path' => '',
    'link_title' => 'Cookies',
    'options' => array(
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-service-links_cookies:https://ec.europa.eu/info/cookies',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-service-links_europa-analytics:https://webanalytics.ec.europa.eu.
  $menu_links['menu-nexteuropa-service-links_europa-analytics:https://webanalytics.ec.europa.eu'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'https://webanalytics.ec.europa.eu',
    'router_path' => '',
    'link_title' => 'Europa Analytics',
    'options' => array(
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-service-links_europa-analytics:https://webanalytics.ec.europa.eu',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 25,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-service-links_legal-notice:https://ec.europa.eu/info/legal-notice_en.
  $menu_links['menu-nexteuropa-service-links_legal-notice:https://ec.europa.eu/info/legal-notice'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'https://ec.europa.eu/info/legal-notice',
    'router_path' => '',
    'link_title' => 'Legal notice',
    'options' => array(
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-service-links_legal-notice:https://ec.europa.eu/info/legal-notice',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -34,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: menu-nexteuropa-service-links_resources-for-partners:http://ec.europa.eu/info/resources-partners_en.
  $menu_links['menu-nexteuropa-service-links_resources-for-partners:http://ec.europa.eu/info/resources-partners'] = array(
    'menu_name' => 'menu-nexteuropa-service-links',
    'link_path' => 'http://ec.europa.eu/info/resources-partners',
    'router_path' => '',
    'link_title' => 'Resources for partners',
    'options' => array(
      'alter' => TRUE,
      'identifier' => 'menu-nexteuropa-service-links_resources-for-partners:http://ec.europa.eu/info/resources-partners',
      'menu_token_link_uuid' => '',
      'attributes' => array(
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'data-remove-class' => 0,
      ),
      'item_attributes' => array(
        'data-image' => '',
        'data-display-title' => 1,
        'data-hide-children' => 0,
        'id' => '',
        'class' => '',
        'data-remove-class' => 0,
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-social-media_facebook:https://www.facebook.com/EuropeanCommission.
  $menu_links['menu-nexteuropa-social-media_facebook:https://www.facebook.com/EuropeanCommission'] = array(
    'menu_name' => 'menu-nexteuropa-social-media',
    'link_path' => 'https://www.facebook.com/EuropeanCommission',
    'router_path' => '',
    'link_title' => 'Facebook',
    'options' => array(
      'identifier' => 'menu-nexteuropa-social-media_facebook:https://www.facebook.com/EuropeanCommission',
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => 1,
        'class' => array(
          0 => 'icon',
          1 => 'icon--facebook',
          2 => 'footer__icon--facebook',
          3 => 'footer__icon--social',
        ),
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: menu-nexteuropa-social-media_other-social-media:http://ec.europa.eu/dgs/communication/services/journalist/social-media_en.htm.
  $menu_links['menu-nexteuropa-social-media_other-social-media:http://ec.europa.eu/dgs/communication/services/journalist/social-media_en.htm'] = array(
    'menu_name' => 'menu-nexteuropa-social-media',
    'link_path' => 'http://ec.europa.eu/dgs/communication/services/journalist/social-media_en.htm',
    'router_path' => '',
    'link_title' => 'Other social media',
    'options' => array(
      'attributes' => array(
        'data-display-title' => 1,
        'data-remove-class' => 0,
      ),
      'identifier' => 'menu-nexteuropa-social-media_other-social-media:http://ec.europa.eu/dgs/communication/services/journalist/social-media_en.htm',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: menu-nexteuropa-social-media_twitter:https://twitter.com/eu_commission.
  $menu_links['menu-nexteuropa-social-media_twitter:https://twitter.com/eu_commission'] = array(
    'menu_name' => 'menu-nexteuropa-social-media',
    'link_path' => 'https://twitter.com/eu_commission',
    'router_path' => '',
    'link_title' => 'Twitter',
    'options' => array(
      'identifier' => 'menu-nexteuropa-social-media_twitter:https://twitter.com/eu_commission',
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => 1,
        'class' => array(
          0 => 'icon',
          1 => 'icon--twitter',
          2 => 'footer__icon--twitter',
          3 => 'footer__icon--social',
        ),
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-site-links_commission-and-its-priorities:https://ec.europa.eu/commission/index.
  $menu_links['menu-nexteuropa-site-links_commission-and-its-priorities:https://ec.europa.eu/commission/index'] = array(
    'menu_name' => 'menu-nexteuropa-site-links',
    'link_path' => 'https://ec.europa.eu/commission/index',
    'router_path' => '',
    'link_title' => 'Commission and it\'s priorities',
    'options' => array(
      'identifier' => 'menu-nexteuropa-site-links_commission-and-its-priorities:https://ec.europa.eu/commission/index',
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => 1,
        'name' => 'political',
        'class' => '',
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Exported menu link: menu-nexteuropa-site-links_policies-information-and-services:https://ec.europa.eu/info/index.
  $menu_links['menu-nexteuropa-site-links_policies-information-and-services:https://ec.europa.eu/info/index'] = array(
    'menu_name' => 'menu-nexteuropa-site-links',
    'link_path' => 'https://ec.europa.eu/info/index',
    'router_path' => '',
    'link_title' => 'Policies, information and services',
    'options' => array(
      'identifier' => 'menu-nexteuropa-site-links_policies-information-and-services:https://ec.europa.eu/info/index',
      'alter' => TRUE,
      'attributes' => array(
        'data-display-title' => 1,
        'name' => 'informational',
        'data-remove-class' => 0,
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => 1,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Commission and it\'s priorities');
  t('About the Commission\'s new web presence');
  t('Contact');
  t('Cookies');
  t('Resources for partners');
  t('Europa Analytics');
  t('European Union');
  t('European Commission');
  t('Policies, information and services');
  t('Facebook');
  t('Twitter');
  t('Other social media');

  return $menu_links;
}
