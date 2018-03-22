/**
 * Facet Api Search.
 */
(function ($) {
  /**
   * Facet API Search namespace definition.
   * @type {{}|*}
   */
  Drupal.facetapi_search = Drupal.facetapi_search || {};

  /**
   * Facet API Search storage.
   * @type {{}|*}
   */
  Drupal.facetapi_search.storage = Drupal.facetapi_search.storage || {};

  /**
   *  Facet Api Search behavior.
   */
  Drupal.behaviors.facetapi_search = {
    attach: function (context, settings) {
      $('.facet-search-input', context).once().on('keyup', function () {
        var key = $(this).val(),
          id = $(this).attr('id'),
          $facets = $('ul.facetapi-' + id + ' li', context);

        if (!Drupal.facetapi_search.storage[id] || (Drupal.facetapi_search.storage[id] == undefined)) {
          Drupal.facetapi_search.storage[id] = $('ul.facetapi-' + id + ' li:visible', context).length;
        }

        if ($.trim(key).length) {
          $facets.each(function () {
            var $self = $(this),
              str = $self.find('a').ignore('span').text(),
              patt = new RegExp(escapeRegExp(key), 'i'),
              res = patt.test(str);

            if (res) {
              $self.show();
            }
            else {
              $self.hide();
            }
          });
        }
        else {
          $facets.hide();
          $facets.each(function (i) {
            if (i < Drupal.facetapi_search.storage[id]) {
              $(this).show();
            }
            else {
              Drupal.facetapi_search.storage[id] = false;
              return false;
            }
          });
        }
      });
    }
  };

  /**
   * Escape string for regex usage.
   *
   * @param str
   * @returns {*}
   */
  function escapeRegExp(str) {
    return str.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
  }

  /**
   * Ignore micro-plugin.
   *
   * Ignores from element the specified selector.
   *
   * @param sel
   * @returns {*|number}
   */
  $.fn.ignore = function (sel) {
    return this.clone().children(sel || ">*").remove().end();
  };
})(jQuery);
