/**
 * @file
 */

(function ($) {
  CKEDITOR.plugins.add('eclexpandable', {
    icons: 'eclexpandable',

    init: function (editor) {
      /* Command */
      editor.addCommand('eclexpandable', new CKEDITOR.dialogCommand('eclexpandableDialog'));

      /* Button */
        editor.ui.addButton('eclexpandable', {
          label: 'Insert ECL expandable',
          command: 'eclexpandable',
          toolbar: 'eclexpandable'
        });

      /* Dialog */
    CKEDITOR.dialog.add('eclexpandableDialog', this.path + 'dialogs/eclexpandable.js');
    }

  });
})(jQuery);
