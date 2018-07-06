/**
 * @file
 * CKEDITOR plugin file.
 */

(function ($) {
  CKEDITOR.plugins.add('dt_headings', {
    icons: 'dt_headings',
    requires: 'dialog',
    init: function (editor) {
      // Register a command with CKEditor to launch the dialog box.
      editor.addCommand('dt_headings_insert', new CKEDITOR.dialogCommand('dt_headings'));

      // Add a button to the CKeditor that executes a CKeditor command.
      editor.ui.addButton('dt_headings', {
        label: Drupal.t('Headings, with some DT specifics'),
        command: 'dt_headings_insert',
        icon: this.path + 'images/dt_headings.png'
      });

      CKEDITOR.dialog.add('dt_headings', this.path + 'dialogs/dt_headings.js');
    }
  });
})(jQuery);
