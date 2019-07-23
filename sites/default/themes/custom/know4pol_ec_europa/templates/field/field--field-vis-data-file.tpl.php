<?php

/**
 * @file
 * Template for field-vis-data-url.
 */
?>
<div<?php print $atomium['attributes']['wrapper']; ?> style="width:100%">
  <div class="ecl-field__label"><?php print $label ?></div>
  <div class="ecl-field__body">
  <script defer src="//europa.eu/webtools/load.js" type="text/javascript"></script>
    <?php foreach ($items as $delta => $item): ?>
      <div<?php print $atomium['attributes'][$delta]; ?>>
        <?php if ($element['#object']->field_vis_type[LANGUAGE_NONE][0]['value'] == "Highcharts"): ?>
        <div id="chart_container_global" style="background-color: #eeeeee; padding: 1em;">
          <div id="chart_container"></div>
          <div id="chart_data_set" style="text-align: center; padding-top: 1em;"></div>
        </div>
        <script type="application/json">{
          "service": "charts",
          "provider": "highcharts",
          "custom": "<?php print render($items); ?>"
        }</script>
        <?php elseif ($element['#object']->field_vis_type[LANGUAGE_NONE][0]['value'] == "Map"): ?>
        <script type="application/json">{
          "service": "map",
          "version": "2.0",
          "custom": "<?php print render($items); ?>"
        }</script>
        <?php endif; ?>
    <?php endforeach; ?>
  </div>
</div>
