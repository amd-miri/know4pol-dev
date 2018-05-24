/**
 * @file
 * Cacheflush Memcache Tab update JS.
 */

(function ($) {
  /**
   * Update the summary for the cacheflush module memcache vertical tab.
   */
  Drupal.behaviors.vertical_memcache_tabs = {
    attach: function (context) {
      $('fieldset.memcache_tab', context).drupalSetSummary(function (context) {
        var rez = '';
        var inc = 0;
        var row = '';

        var rows = $('#cacheflush-memcache-settings-table tbody tr', context);
        $.each(rows, function (i, value) {
          if ($('input[type="text"]', this).val().trim() && $('select', this).val() != 0) {
            row = Drupal.formatPlural((inc + 1), Drupal.t('row'), Drupal.t('rows'));
            rez = Drupal.t('@type custom @row defined.', {'@type': (inc + 1), '@row': row});
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
