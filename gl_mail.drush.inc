<?php

  /**
   * Outgoing mail processing
   */
  
  /** Implements hook_drush_command */
  function gl_mail_drush_command() {
    return array(
      'outgoing_mail' => array(
        'description' => dt('Drush command for processing outgoing mail'),
        'aliases' => array('g3outgoingmail'),
      ),
    );
  }
  
  /** Implements hook_drush_help */
  function gl_mail_drush_help($section) {
    switch ($section){
    case 'drush:outgoing_mail':
        return dt('Processes outgoing mail.');
    }
  }
  
  /* Drush command to process outgoing mail */
  function drush_gl_mail_outgoing_mail() {
    // Read batches from the queue
    $batches = db_query('SELECT * FROM {gl_mail_batch}');
    foreach ($batches as $batch) {
      $dispatcher = unserialize($batch->data);
      
      // Read jobs related to the batch
      $jobs = db_query('SELECT * FROM {gl_mail_job} j WHERE j.bid = :bid',
          array(':bid' => $batch->bid))->fetchAll();
      
      $emails = array();
      foreach ($jobs as $job) {
        $emails[] = unserialize($job->data);
      }
      
      $dispatcher->dispatch_multiple($emails, FALSE); // send the e-mail now
      
      db_delete('gl_mail_job')->condition('bid', $batch->bid)->execute();
      db_delete('gl_mail_batch')->condition('bid', $batch->bid)->execute();
    }
  }
  