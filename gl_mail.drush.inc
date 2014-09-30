<?php
  
  require_once DRUPAL_ROOT . '/sites/all/modules/g3/g3core/g3core.utils.inc';

  /**
   * Incoming mail handling for the site using MimeMail
   */

  // These are postfix-specfic errors
  define('EX_SOFTWARE', 70);
  define('EX_NOUSER', 67);
  define('EX_NOPERM', 77);
  define('EX_UNAVAILABLE', 69);
  
  /** Implements hook_drush_command */
  function gl_mail_drush_command() {
    return array(
      'incoming_mail' => array(
        'description' => dt('Drush command for handling incoming mail'),
        'aliases' => array('g3incomingmail'),
      ),
    );
  }
  
  /** Implements hook_drush_help */
  function gl_mail_drush_help($section) {
    switch ($section){
    case 'drush:incoming_mail':
        return dt('Handles incoming mail. cat email | drush g3incomingmail');
    }
  }
  
  function drush_gl_mail_incoming_mail() {
    watchdog('gl_mail', 'called');
    
    error_reporting(0); // Disable errors so they don't make it to bounces
    
    $raw = stream_get_contents(STDIN);  // read encoded raw e-mail
    $raw = base64_decode($raw);         // decode e-mail
    module_load_include('inc', 'mimemail', 'includes/mimemail.incoming');
    $parsed = mimemail_parse($raw);     // parse e-mail into array
    
    // If the e-mail is from our own domain, there is an erroneous loop
    $domain = g3core_get_domain();
    $from = $email['headers']['From'];
    $reply_to = $email['headers']['Reply-To'];
    if (stristr($from, "@{$domain}") ||
        stristr($reply_to, "@{$domain}")) {
      watchdog('gl_mail', '1');
      return; // Don't bounce nor reply
    }

    // Send to registered mail handlers
    $hook = 'incoming_mail';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        watchdog('gl_mail', '2');
        
        $result = call_user_func_array($function, array(&$parsed, $raw));
        switch ($result) {
        case TRUE:
          return;   // handled
          break;
        case FALSE:
          continue; // doesn't handle this e-mail or just made modifications
          break;
        case MAIL_ERROR_USER_NOT_FOUND:
          exit(EX_NOUSER);
          break;
        case MAIL_ERROR_PERMISSION_DENIED:
          exit(EX_NOPERM);
          break;
        case MAIL_ERROR_SOFTWARE:
        default:
          exit(EX_SOFTWARE);
          break;
        }
      }
    }

    exit(EX_UNAVAILABLE);
  }
