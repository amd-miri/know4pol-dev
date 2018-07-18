<?php

/**
 * @file
 * Theme template file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function ros_theme_preprocess_ros2(&$variables, $hook) {
  $variables['callbacks'][] = __FUNCTION__;
}

/**
 * Implements hook_preprocess_hook().
 */
function ros_theme_preprocess_ros2__variant1(&$variables, $hook) {
  $variables['callbacks'][] = __FUNCTION__;
}

/**
 * Implements hook_process_hook().
 */
function ros_theme_process_ros2__variant2__foo(&$variables, $hook) {
  $variables['callbacks'][] = __FUNCTION__;
}

/**
 * Implements hook_preprocess_hook().
 */
function ros_theme_preprocess_ros4(&$variables, $hook) {
  $variables['callbacks'][] = __FUNCTION__;
}

/**
 * Implements hook_preprocess_hook().
 */
function ros_theme_preprocess_ros4__foo(&$variables, $hook) {
  $variables['callbacks'][] = __FUNCTION__;
}
