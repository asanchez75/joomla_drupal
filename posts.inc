<?php

class ArticleMigration extends Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->description = t("Migrate articles from Joomla to drupal7");

    $source_fields = array(
      'nid' => t('Node ID'),
    );

    $query = Database::getConnection('default', 'ic_joomla')->select('jos_content','p')
             ->fields('p', array('id', 'created_by', 'title', 'introtext', 'full_text' ,'created', 'alias'));

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('article');

    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                          'description' => t('Node id from old site'),
                          'alias' => 'p',
                         )
        ),
        MigrateDestinationNode::getKeySchema()
    );


    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('title', 'title');
		$this->addFieldMapping('uid', 'created_by')
    		 ->sourceMigration('UserMigration')
    		 ->defaultValue(1);

    $this->addFieldMapping('status')->defaultValue(TRUE);
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('comment')->defaultValue(2);
    $this->addFieldMapping('promote')->defaultValue(1);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('language')
    		->defaultValue('und');

    $this->addFieldMapping('body', 'full_text');
    $this->addFieldMapping('body:summary', 'introtext');
    $this->addFieldMapping('body:format', NULL, FALSE)->defaultValue('full_html');
    $this->addFieldMapping('path', 'alias');
  }
  public function prepareRow($current_row) {
    $current_row->created = strtotime($current_row->created);
    $current_row->changed = strtotime($current_row->modified);
    return TRUE;
  }
}
