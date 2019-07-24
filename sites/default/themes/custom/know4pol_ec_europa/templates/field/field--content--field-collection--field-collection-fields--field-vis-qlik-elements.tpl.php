<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>
<div<?php print $atomium['attributes']['wrapper']; ?> style="width:100%">
  <div class="ecl-field__label"><?php print $label ?></div>
  <div class="ecl-field__body">
    <?php print $html_layout; ?>
  </div>
   <script>
      var config = {
             host: 'qap-datam.jrc.ec.europa.eu',
             prefix: '/qap/',
             port: 443,
             isSecure: true
      }

      config.identity = Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);
      var baserUrl = (config.isSecure ? 'https' : 'http') + '://' + config.host + config.prefix;
      require.config( {
                     baseUrl: baserUrl + 'resources'
              } );
              
      require( ["js/qlik"], function( qlik ) {
         qlik.setOnError( function(err) {console.log(err); alert(err.message); });
                     
      var app = qlik.openApp("<?php print $element['#object']->field_vis_qlik_app_id[LANGUAGE_NONE][0]['value'] ?>", config);
       
      <?php foreach ($items as $delta => $item): ?>
        app.getObject("<?php print $item['html_id']; ?>", 
                      "<?php print $item['id']; ?>" 
                      <?php if(isset($item['option'])): ?>, <?php print $item['option']; ?><?php
                      endif; ?>
                     ); 
      <?php endforeach; ?>
      });
   </script>
</div>
