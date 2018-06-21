/**
 * @file
 */

CKEDITOR.dialog.add('ctabuttonDialog', function (editor) {
    return {
        title: 'Call to action',
        minWidth: 400,
        minHeight: 200,
        contents: [
            {
                id: 'tab-basic',
                label: 'Basic Settings',
                elements: [
                    {
                        type: 'text',
                        id: 'txtchng',
                        label: 'Text update',
                        setup: function (element) {
                            this.setValue(element.getText());
                        },
                        commit: function (element) {
                        }
                    },
                    {
                        type: 'text',
                        id: 'enterurl',
                        label: 'Enter URL',

                        setup: function (element) {
                            this.setValue(element.getText());
                        },
                        commit: function (element) {
                        }
                    }
                ]

            }
        ],
        onShow: function () {
            var selection = editor.getSelection();
            var element = selection.getStartElement();
            this.element = element;
            this.setupContent(this.element);
        },

        onOk: function () {
            var textObj = this.getContentElement('tab-basic', 'txtchng');
            var enterurlObj = this.getContentElement('tab-basic', 'enterurl');
            var text = textObj.getValue();
            var enterurl = enterurlObj.getValue();
            this.element.setHtml('<a href="' + enterurl + '" class="ecl-button ecl-button--call ecl-button--caret-right">' + text + '</button>');
            var txt = this.element;
            this.commitContent(txt);
            if (this.insertMode) {
                editor.insertElement(txt);
            }
        }
    };
});
