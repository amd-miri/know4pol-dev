/**
* @file
* Organic Groups field javascript file.
*
* Contains code to automatically create machine name for new fields.
* Helps user in adding existing fields, clearing manual creation of new fields.
*/

(function ($) {
    Drupal.behaviors.ogFieldEditName = {
      attach: function (context, settings) {
        $("#edit-new-field-name").keyup(function () {
            $("#edit-new-field-machine-name").val(this.value);

            var replace = $('#edit-new-field-name').val();
            replace = replace.toLowerCase().replace(/ /g, '_');
            $('#edit-new-field-machine-name').val(replace);

            $("#edit-existing-fieldname").val("");
            $('#edit-select-existing').val('_none');
        });
      }
    };

    Drupal.behaviors.ogFieldAddExisting = {
      attach: function (context, settings) {
        $("#edit-select-existing").change(function () {
          var field = $("#edit-select-existing option[value='" + this.value + "']").text();
          var fieldName = field.match(/\((.*)\)/);
          if (fieldName != "" || fieldName != null) {
            if (!$("#edit-existing-fieldname").val()) {
              $("#edit-existing-fieldname").val(fieldName[1]);
            }
          }
          else {
            $("#edit-existing-fieldname").val("");
          }
          $("#edit-new-field-name").val("");
          $("#edit-new-field-machine-name").val("");
        });

        $("#edit-existing-fieldname").keydown(function () {
            $("#edit-new-field-machine-name").val("");
            $("#edit-new-field-name").val("");
        });
      }
    };

  })(jQuery);
