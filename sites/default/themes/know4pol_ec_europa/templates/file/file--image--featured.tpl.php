<?php

/**
 * @file
 * Default theme implementation to display a file.
 *
 * Available variables:
 * - $label: the (sanitized) file name of the file.
 * - $content: An array of file items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The file owner's picture from user-picture.tpl.php.
 * - $date: Formatted added date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $timestamp
 *   variable.
 * - $name: Themed username of file owner output from theme_username().
 * - $file_url: Direct URL of the current file.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_file().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - file-entity: The current template type, i.e., "theming hook".
 *   - file-[type]: The current file type. For example, if the file is a
 *     "Image" file it would result in "file-image". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - file-[mimetype]: The current file's MIME type. For exampe, if the file
 *     is a PNG image, it would result in "file-image-png"
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $file: Full file object. Contains data that may not be safe.
 * - $type: File type, i.e. image, audio, video, etc.
 * - $uid: User ID of the file owner.
 * - $timestamp: Time the file was added formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   listings.
 * - $id: Position of the file. Increments each time it's output.
 *
 * File status variables:
 * - $view_mode: View mode, e.g. 'default', 'full', etc.
 * - $page: Flag for the full page state.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the file a corresponding
 * variable is defined, e.g. $file->caption becomes $caption. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language, e.g. $file->caption['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_file_entity()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<div id="<?php print $id; ?>" class="<?php print $classes ?> file--image"<?php print $attributes; ?>>
  <?php
  hide($content['links']);
  ?>

  <?php foreach($content as $key => $value): ?>
    <?php if($key == 'file'): ?>
      <?php
        // Alt and title tags missing, file_preprocess does not exist.
        if(isset($content['file']['#item']['field_file_image_alt_text']['en'][0]['safe_value'])):
          $content['file']['#item']['alt'] = $content['file']['#item']['field_file_image_alt_text']['en'][0]['safe_value'];
        endif;
        if(isset($content['file']['#item']['field_file_image_title_text']['en'][0]['safe_value'])):
          $content['file']['#item']['title'] = $content['file']['#item']['field_file_image_title_text']['en'][0]['safe_value'];
        endif ?>
      <?php print l(render($content[$key]),
        $referencing_entity->field_audiovisual[LANGUAGE_NONE][0]['url'],
        array('html' => TRUE)); ?>
    <?php else: ?>
      <?php print render($content[$key]); ?>
    <?php endif; ?>
  <?php endforeach; ?>

</div>
