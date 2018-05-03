<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>



<div<?php print $atomium['attributes']['wrapper']; ?> style="width:100%">
  <div class="ecl-field__label"><?php print $label ?></div>
  <div class="ecl-field__body">
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>>
      <?php if ($item['#element']['v_type'] == "Tableau"): ?>
        <div class='tableauPlaceholder' style='width: 100%; height: 1024px;'>
          <object class='tableauViz' width='100%' height='1024' style='display:none;'>
            <?php foreach ($item['#element']['param'] as $pname => $pvalue): ?>
              <param name='<?php print $pname ?>' value='<?php print $pvalue ?>' />
            <?php endforeach; ?>
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
