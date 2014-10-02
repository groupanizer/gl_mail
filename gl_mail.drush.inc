<?php
  
  // module_load_include('inc', 'g3core', 'g3core.utils'); TODO: Why error in Drush???
  require_once DRUPAL_ROOT . '/sites/all/modules/g3/g3core/g3core.utils.inc';
  
  /**
   * Implements hook_drush_command()
   */
  function gl_mail_drush_command() {
    return array(
      'handle_incoming_mail' => array(
        'description' => dt('Handles incoming mail. cat email | drush g3mail'),
        'aliases' => array('g3mail'),
        'bootstrap' => DRUSH_BOOTSTRAP_MAX,
      ),
    );
  }
  
  /**
   * Implements hook_drush_help()
   */
  function gl_mail_drush_help($section) {
    if ($section == 'drush:handle_incoming_mail') {
      return dt('Handles incoming mail.' .
          ' E-mail must be piped in and base64 encoded');
    }
  }
  
  /* Callback for handle_incoming_mail drush command */
  function drush_gl_mail_handle_incoming_mail() {
    print('WORKING');
    watchdog('gl_mail', 'WORKING');
  }
