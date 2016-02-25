<?php

/**
 * Implements hook_drush_command().
 */
function kw_seeds_drush_command() {
  $items = array();

  $items['kw-seed'] = array(
    'description' => 'Run a seed.',
    'arguments' => array(
      'seed' => dt('The seed you want to run'),
    ),
    'drupal dependencies' => array('kw_seeds'),
  );

  return $items;
}

/**
 * Implements drush_COMMAND() for kw-manifests.
 */
function drush_kw_seeds_kw_seed($seed = NULL) {
  $seeds = kw_seeds_info();

  if ($seed && !isset($seeds[$seed])) {
    return drush_set_error(dt("'!seed' is not a valid seed.", array('!seed' => $seed)));
  }

  if ($seed) {
    drush_op($seeds[$seed]);
  }
  else {
    $seed = drush_choice($seeds, 'Enter a number to choose which seed to run.', '!key');
    if ($seed !== FALSE) {
      drush_op($seeds[$seed]);
    }
  } 

  if ($seeds !== FALSE) {
    drush_log(dt("'!seed' seed ran.", array('!seed' => $seed)), 'success');
  }
}