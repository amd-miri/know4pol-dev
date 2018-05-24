/**
 * @file
 * Cacheflush Varnish Tab update JS.
 */

(function ($) {
  /**
   * Update the summary for the cacheflush module varnish vertical tab.
   */
  Drupal.behaviors.vertical_varnish_tabs = {
    attach: function (context) {
      $('fieldset.varnish_tab', context).drupalSetSummary(function (context) {
        var rez = '';
        var inc = 0;
        var row = '';

        var rows = $('#cacheflush-varnish-settings-table tbody tr', context);
        $.each(rows, function (i, value) {
          if ($('input[type="text"]', this).val().trim()) {
            row = Drupal.formatPlural((inc + 1), Drupal.t('row'), Drupal.t('rows'));
            rez = Drupal.t('@type pattern @row defined.', {'@type': (inc + 1), '@row': row});
            inc++;
          }
        });

        if (rez) {
          return Drupal.checkPlain(rez, context);
        }
        return Drupal.t('Nothing selected.');
      });
    }
  };

})(jQuery);
