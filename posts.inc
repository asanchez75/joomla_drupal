<?php

class postMigration extends Migration {
  public function __construct() {
    parent::__construct();

    $this->descriprion = t("Migrate posts from rails to drupal7");

    $source_fields = array(
      'nid' => t('Node ID'),
    );

    $query = db_select('joomla.c7nts_content','p')
             ->fields('p', array('id', 'created_by', 'title', 'introtext', 'created', 'modified'));

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('posts');

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

    $generic_textarea_arguments = MigrateTextFieldHandler::arguments(NULL, 'full_html');
    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('title', 'title');
		$this->addFieldMapping('uid', 'created_by')
    		 ->sourceMigration('user')
    		 ->defaultValue(1);
    $this->addFieldMapping('status')->defaultValue(TRUE);
    $this->addFieldMapping('revision_uid')
				->issueGroup(t('DNM'));
		$this->addFieldMapping('revision')
				->issueGroup(t('DNM'));
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('changed', 'modified');
    $this->addFieldMapping('comment')->defaultValue(2);
    $this->addFieldMapping('promote')->defaultValue(1);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('language')
    		->defaultValue('und');

    $this->addFieldMapping('body_summary', 'introtext')
        ->arguments($generic_textarea_arguments);
    $this->addFieldMapping('path')
    			->issueGroup(t('DNM'));
  }
  public function prepareRow($current_row) {
    $current_row->created = strtotime($current_row->created);
    $current_row->changed = strtotime($current_row->modified);
    return TRUE;
  }
}
