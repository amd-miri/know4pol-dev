/**
 * @file
 * JS file for Qlik visualisation via QAP.
 */

var config = {
  host: 'qlik-sense.jrc.ec.europa.eu',
  prefix: '/qap/',
  port: 443,
  isSecure: true
}

config.identity = Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);
var baserUrl = (config.isSecure ? 'https' : 'http') + '://' + config.host + config.prefix;
require.config({
  baseUrl: baserUrl + 'resources'
});

require(['js/qlik'], function (qlik) {
  qlik.setOnError(function (err) {console.log(err); alert(err.message); });

  var app = qlik.openApp(Drupal.settings.know4pol.qapid, config);
  for (i = 0; i < Drupal.settings.know4pol.items.length; i++) {
    app.getObject(
      Drupal.settings.know4pol.items[i].html_id,
      Drupal.settings.know4pol.items[i].id,
      Drupal.settings.know4pol.items[i].option
    );
  }
});
