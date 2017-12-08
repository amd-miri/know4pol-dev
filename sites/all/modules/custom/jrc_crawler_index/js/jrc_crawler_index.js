/**
 * @file
 * Js file for the crawler.
 */

(function ($) {
  Drupal.behaviors.jrcCrawlerIndex = {
    attach: function (context, settings) {
      // Add link to first page, normally not linked because first page already shows items list.
      $(".pager-current.first").wrapInner("<a href='IDOLindexation?page=0' />").removeClass("pager-current");
      $("li.pager-item a").each(function () {
        var first = $(this).text();
        // Override default link for first page when on other pages.
        if (first == '1') {
          $(this).attr("href", "IDOLindexation?page=0");
        };
      });
    }
  }
})(jQuery);
