/**
 * @file
 */
CKEDITOR.dialog.add('eclexpandableDialog', function(editor) {
  return {
    title: 'ECL Expandable',
    minWidth: 400,
    minHeight: 150,
    contents: [{
      id: 'tab1',
      label: 'Settings',
      elements: [{
          type: 'select',
          id: 'type',
          label: 'Expandable Type',
          items: [
            ['Button', ' button'],
            ['Link', ''],
          ],
          'default': ' button',
        }, {
          type: 'text',
          id: 'strLabel',
          label: 'Label*',
          validate: CKEDITOR.dialog.validate.notEmpty(
            "Label should be provided")
        },
        /* not implemented in current ECL v0 {
                     type: 'text',
                     id: 'strLabelClose',
                     label: 'Label when opened',
                    }, */
        {
          type: 'checkbox',
          id: 'blnOpened',
          label: 'Expanded by default',
        },
      ]
    }],
    onOk: function() {
      var selection = editor.getSelection();
      var container = new CKEDITOR.dom.element('p');
      container.appendText('[expandable title="' + this.getValueOf('tab1',
          'strLabel') + '"' +
        this.getValueOf('tab1', 'type') +
        (this.getValueOf('tab1', 'blnOpened') ? " opened" : "") +
        ']');
      var range;
      // No selection or range or range is empty ?
      if (selection == null ||
        (range = selection.getRanges()[0]) == null ||
        range.startOffset == range.endOffset) {
          var p = new CKEDITOR.dom.element('p');
          p.appendTo(container);
      } else {
        var fragment = range.extractContents();
        fragment.appendTo(container);
      }
      container.appendText('[/expandable]');
      editor.insertElement(container);
    }
  };
});