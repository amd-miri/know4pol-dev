/**
 * @file
 */

(function ($) {
  CKEDITOR.plugins.add('ctabutton', {
    icons: 'ctabutton',
    init: function (editor) {
      editor.addCommand('ctabutton', new CKEDITOR.dialogCommand('ctabuttonDialog'));
        editor.ui.addButton('ctabutton', {
          label: 'Call to action',
          command: 'ctabutton',
          toolbar: 'ctabutton'
        });
        if (editor.contextMenu) {
          editor.addMenuGroup('ctabuttonGroup');
          editor.addMenuItem('ctabuttonItem', {
            label: 'Change link',
            icon: this.path + 'icons/ctabutton.png',
            command: 'ctabutton',
            group: 'ctabuttonGroup'
        });
        editor.contextMenu.addListener(function (element) {
          if (element.getAscendant('ctabutton', true)) {
            return { abbrItem: CKEDITOR.TRISTATE_OFF };
          }
        });
      }
    CKEDITOR.dialog.add('ctabuttonDialog', this.path + 'dialogs/ctabutton.js');
    }
  });
})(jQuery);
