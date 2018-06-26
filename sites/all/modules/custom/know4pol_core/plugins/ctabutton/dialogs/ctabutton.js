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
                id: 'tab-external',
                label: 'External Links',
                elements: [
                    {
                        type: 'text',
                        id: 'txtchng',
                        label: 'Link Text',
                        setup: function (element) {
                            this.setValue(element.getText());
                        },
                        commit: function (element) {
                        }
                    },
                    {
                        type: 'select',
                        id: 'protocol',
                        label: 'Protocol',
                        items: [['http://'], ['https://']],

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
//
//            {
//                id: 'tab-internal',
//                label: 'Internal Links',
//                elements: [
//                    {
//                        type: 'text',
//                        id: 'txtchng',
//                        label: 'Link Text',
//                        setup: function (element) {
//                            this.setValue(element.getText());
//                        },
//                        commit: function (element) {
//                        }
//                    },
//                    {
//                        type: 'text',
//                        id: 'enterurl',
//                        label: 'Internal Link',
//
//                        setup: function (element) {
//                            this.setValue(element.getText());
//                        },
//                        commit: function (element) {
//                        }
//                    }
//                ]
//
//            },
//            {
//                id: 'tab-mail',
//                label: 'Mail Link',
//                elements: [
//                    {
//                        type: 'text',
//                        id: 'txtchng',
//                        label: 'Mail Text',
//                        setup: function (element) {
//                            this.setValue(element.getText());
//                        },
//                        commit: function (element) {
//                        }
//                    },
//                    {
//                        type: 'mail',
//                        id: 'enteremail',
//                        label: 'Enter Email',
//
//                        setup: function (element) {
//                            this.setValue(element.getText());
//                        },
//                        commit: function (element) {
//                        }
//                    }
//                ]
//
//
//            }
        ],
        onShow: function () {
            var selection = editor.getSelection();
            var element = selection.getStartElement();
            this.element = element;
            this.setupContent(this.element);


        },

        onOk: function () {
            var textObj = this.getContentElement('tab-external', 'txtchng');
            var enterurlObj = this.getContentElement('tab-external', 'enterurl');
            var protocolObj = this.getContentElement('tab-external', 'protocol');
            var text = textObj.getValue();
            var enterurl = enterurlObj.getValue();
            var protocol = protocolObj.getValue();
            this.element.setHtml('<a href="' + protocol + '' + enterurl + '" class="ecl-button ecl-button--call ecl-button--caret-right">' + text + '</button>');
            var txt = this.element;
            this.commitContent(txt);
            if (this.insertMode) {
                editor.insertElement(txt);
            }

            var range = editor.createRange();
            range.moveToPosition(range.root, CKEDITOR.POSITION_BEFORE_END);
            editor.getSelection().selectRanges([range]);
        }
    };
});
