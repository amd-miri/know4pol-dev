<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>

<div<?php print $atomium['attributes']['wrapper']; ?>>
  <div class="ecl-field__label"><?php print $label ?></div>
  <div class="ecl-field__body">
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>>
      <?php if ($item['#element']['v_type'] == "Tableau"): ?>
        <div class='tableauPlaceholder' style='width: 100%; height: 724px;'>
          <object class='tableauViz' width='100%' height='724' style='display:none;'>
            <param name='host_url' value='<?php print $item['#element']['thost']; ?>' /> 
            <param name='site_root' value='<?php print $item['#element']['troot']; ?>' />
            <param name='name' value='<?php print $item['#element']['tname']; ?>' />
            <param name='embed_code_version' value='3' /> 
            <param name='tabs' value='no' />
            <param name='toolbar' value='yes' />
            <param name='showAppBanner' value='false' />
          </object>
        </div>
        <?php elseif ($item['#element']['v_type'] == "Highcharts"): ?>
        <div id="chart_container_global" style="background-color: #eeeeee; padding: 1em;">
          <div id="chart_container"></div>
          <div id="chart_data_set" style="text-align: center; padding-top: 1em;"></div>
        </div>
        <script type="application/json">{ 
          "service": "charts",
          "provider": "highcharts",
          "custom": "<?php print $item['#element']['url']; ?>"
        }</script>
        <script defer src="//europa.eu/webtools/load.js" type="text/javascript"></script>
        <?php endif; ?>
    <?php endforeach; ?>
  </div>
</div>
