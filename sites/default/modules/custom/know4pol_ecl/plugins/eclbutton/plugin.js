/**
 * @file
 */

(function ($) {
  CKEDITOR.plugins.add('eclbutton', {
    icons: 'eclbutton',
    init: function (editor) {
      editor.addCommand('eclbutton', new CKEDITOR.dialogCommand('eclbuttonDialog'));
        editor.ui.addButton('eclbutton', {
          label: 'ECL Button',
          command: 'eclbutton',
          toolbar: 'eclbutton'
        });
        if (editor.contextMenu) {
          editor.addMenuGroup('eclbuttonGroup');
          editor.addMenuItem('eclbuttonItem', {
            label: 'Change link',
            icon: this.path + 'icons/eclbutton.png',
            command: 'eclbutton',
            group: 'eclbuttonGroup'
        });
        editor.contextMenu.addListener(function (element) {
          if (element.getAscendant('eclbutton', true)) {
            return { abbrItem: CKEDITOR.TRISTATE_OFF };
          }
        });
      }
    CKEDITOR.dialog.add('eclbuttonDialog', this.path + 'dialogs/eclbutton.js');
    }
  });
})(jQuery);
