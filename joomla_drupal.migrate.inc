<?php
/**
 * Implementation of hook_migrate_api
 *
 */
function joomla_drupal_migrate_api() {
  $api = array(
    'api' => 2,
    'groups' => array(
      'joomla_ic' => array(
        'title' => t('Joomla 2.5 to Drupal 7.50 Migration')
      ),
    ),
    'migrations' => array(
      'ArticleMigration' => array(
        'class_name' => 'ArticleMigration',
        'group_name' => 'joomla_ic',
        'format_mappings' => array('2' => 'full_html', '1' => 'plain_text', '0' => 'full_html')
      ),
      'UserMigration' => array(
        'class_name' => 'UserMigration',
        'group_name' => 'joomla_ic',
        'format_mappings' => array('2' => 'full_html', '1' => 'plain_text', '0' => 'full_html')
      ),
    ),
  );
  return $api;
}


