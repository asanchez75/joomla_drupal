<?php

  class UserMigration extends Migration {

   public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->description = t('Migrate rails Users');

    $source_fields = array(
      'id' => t('User ID'),
    );

    $query = Database::getConnection('default', 'ic_joomla')->select('jos_users', 'u')
              ->fields('u', array('id', 'username', 'email', 'password', 'registerDate'))
              ->condition('u.id', array(1), "NOT IN");

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationUser();

    $this->map  = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'  => 'int',
          'unsigned'  => TRUE,
          'not null'  => TRUE,
          'description' => t('User id from old site'),
          'alias' => 'u',
          )
         ),
      MigrateDestinationUser::getKeySchema()
      );


    $this->addFieldMapping('name', 'username')->dedupe('users', 'name');
    $this->addFieldMapping('mail', 'email')->dedupe('users', 'mail');
    $this->addFieldMapping('pass', 'password');
    $this->addFieldMapping('language')->defaultValue('und');
    $this->addFieldMapping('theme')->defaultValue('');
    $this->addFieldMapping('created', 'registerDate');
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('picture')->defaultValue(0);

  }

  public function complete($entity, stdClass $row) {
    $pass = $entity->pass;
    $uid = $entity->uid;
    db_update('users')
      ->fields(array(
        'pass' => $pass,
      ))
      ->condition('uid', $uid)
      ->execute();
  }

  public function prepareRow($current_row) {
    $current_row->created = strtotime($current_row->registerDate);
    return TRUE;
  }
}
