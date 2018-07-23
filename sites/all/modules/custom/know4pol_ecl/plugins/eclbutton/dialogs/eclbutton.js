/**
 * @file
 */

CKEDITOR.dialog.add('eclbuttonDialog', function (editor) {
  // Global variables to identify the protocol and produce array of URL values.
  var protocolelements;
  var protocol_type;
  return {
    title: 'ECL Button',
    minWidth: 400,
    minHeight: 200,
    contents: [
      {
        id: 'tab-external',
        label: 'External Links',
        elements: [
           {
            type: 'select',
            id: 'buttontype',
            label: 'Button Type',
            items: [['Default','ecl-button ecl-button--default'],['Primary','ecl-button ecl-button--primary'],['Call To Action','ecl-button ecl-button--call ecl-button--caret-right']],
            'default': 'ecl-button ecl-button--default',
            setup: function (element) {
            },
            commit: function (element) {}
          },
          {
             type : 'html',
             html : '<div id="ecl-button-text">The default button is used for important links on the page.</div>',
             setup: function (element) {   
                 jQuery( "#cke_65_select" ).change(function() {
                    if (jQuery( "#cke_65_select" ).val() === 'ecl-button ecl-button--default'){
                        jQuery( "#ecl-button-text" ).text('The default button is used for important links on the page.');   
                    }
                    if (jQuery( "#cke_65_select" ).val() === 'ecl-button ecl-button--primary'){
                         jQuery( "#ecl-button-text" ).text('Used for primary actions in case of forms, to initiate a search query, to apply a filter.');   
                    }
                    if (jQuery( "#cke_65_select" ).val() === 'ecl-button ecl-button--call ecl-button--caret-right'){
                         jQuery( "#ecl-button-text" ).text('Use these buttons sparingly on the most important actions like “Apply for funding” or “Watch live streaming”.');
                    }
                 });
            }
          },
          {
            type: 'text',
            id: 'txtchng',
            label: 'Link Text',
            setup: function (element) {
              this.setValue(element.getText());
            },
            commit: function (element) {
                this.setValue(element.getText());
            }
          },
          {
            type: 'select',
            id: 'protocol',
            label: 'Protocol',
            items: [['<other>','/'],['http://'], ['https://'],['mailto:'],['ftp://'],['news://']],
            'default': '/',
            setup: function (element) {
              var protocol = element.getAttribute("href");
              protocol_type = protocol.split(':');
              if (protocol_type[0] === 'mailto') {
                protocol = protocol.replace(":",":?");
                protocolelements = protocol.split('?');
                this.setValue(protocolelements[0]);
              }
              if (protocol_type[0] === 'https'||protocol_type[0] === 'http'||protocol_type[0] === 'ftp'||protocol_type[0] === 'news') {
                protocol = protocol.replace("://","://?");
                protocolelements = protocol.split('?');
                this.setValue(protocolelements[0]);
              }
              else {
                protocol = protocol.replace("/","/?");
                protocolelements = protocol.split('?');
                this.setValue(protocolelements[0]);
              }
            },
            commit: function (element) {}
          },
          {
            type: 'text',
            id: 'enterurl',
            label: 'Enter URL',
            setup: function (element) {
                this.setValue(protocolelements[1]);
            },
            commit: function (element) {
            }
          }
        ]
      }
    ],
    // Invoked when the dialog is loaded.
    onShow: function () {
      // Get the selection from the editor.
      var selection = editor.getSelection();
      // Get the element at the start of the selection.
      var element = selection.getStartElement();
      // Get the <abbr> element closest to the selection, if it exists.
      if (element) {
        element = element.getAscendant('a', true);
      }
      // Create a new <a> element if it does not exist.
      if (!element || element.getName() != 'a') {
        element = editor.document.createElement('a');
        // Flag the insertion mode for later use.
        this.insertMode = true;
      }
      else {
        this.insertMode = false;
      }
      // Store the reference to the <abbr> element in an internal property, for later use.
      this.element = element;
      // Invoke the setup methods of all dialog window elements, so they can load the element attributes.
      if (!this.insertMode) {
        this.setupContent(this.element);
      }
    },
    onOk: function () {
      var textObj = this.getContentElement('tab-external', 'txtchng');
      var enterurlObj = this.getContentElement('tab-external', 'enterurl');
      var protocolObj = this.getContentElement('tab-external', 'protocol');
      var buttontypeObj = this.getContentElement('tab-external', 'buttontype');
      var text = textObj.getValue();
      var enterurl = enterurlObj.getValue();
      var protocol = protocolObj.getValue();
      var buttontype = buttontypeObj.getValue();
      this.element.setHtml('<a href="' + protocol + '' + enterurl + '" class="' + buttontype + '">' + text + '</a>');
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
