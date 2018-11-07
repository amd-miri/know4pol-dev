<?php

/**
 * Interface for exporting to a given file format.
 */
interface TMGMTFileFormatInterface {

  /**
   * Return the file content for the job data.
   *
   * @param $job
   *   The translation job object to be exported.
   *
   * @return
   *   String with the file content.
   */
  function export(TMGMTJob $job);

  /**
   * Validates that the given file is valid and can be imported.
   *
   * @todo this function should NOT return a job. We need a import processor
   *   instance instead to deal with the import context.
   *
   * @param string $imported_file
   *   File path to the file to be imported.
   *
   * @return TMGMTJob
   *   Returns the corresponding translation job entity if the import file is
   *   valid, FALSE otherwise.
   */
  public function validateImport($imported_file);

  /**
   * Converts an exported file content back to the translated data.
   *
   * @return
   *   Translated data array.
   */
  function import($imported_file);
}
