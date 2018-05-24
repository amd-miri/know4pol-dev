/**
 * @file
 * Cacheflush Tabs update JS.
 */

(function ($) {
  /**
   * Update the summary for the cacheflush module vertical tab.
   */
  Drupal.behaviors.vertical_tabs = {
    attach: function (context) {
      $('fieldset.original_tabs', context).drupalSetSummary(function (context) {
        var rez = '';
        var inc = 0;

        var inputs = $('input', context);
        var comma = '';
        $.each(inputs, function (i, val) {
          if ($(this).attr('checked')) {
            if (inc === 1) {
              comma = ', ';
            }
            rez = rez + comma + $(this).parent().children('label').html().trim();
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
