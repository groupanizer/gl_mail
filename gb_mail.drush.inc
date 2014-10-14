<?php
  
  // module_load_include('inc', 'g3core', 'g3core.utils'); TODO: Why error in Drush???
  
  /**
   * Implements hook_drush_command()
   */
  function gb_mail_drush_command() {
    return array(
      'incoming_mail' => array(
        'description' => dt('Handles incoming mail.'),
        'aliases' => array('g3mail'),
      ),
    );
  }
  
  /**
   * Implements hook_drush_help()
   */
  function gb_mail_drush_help($section) {
    if ($section == 'drush:incoming_mail') {
      return dt('Handles incoming mail.' .
          ' E-mail must be piped in and base64 encoded');
    }
  }
  
  /* Callback for handle_incoming_mail drush command */
  function drush_gb_mail_incoming_mail() {
    watchdog('gb_mail', 'WORKING');
  }
