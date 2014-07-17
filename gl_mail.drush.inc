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
        return dt('Handles incoming mail. cat email | drush g3incoming');
    }
  }
  
  /** Deprecated */
  function _parse_email_for_body($email) {
    /** If a boundary is present then mimemail has failed in its parsing
     *  and ['html'] contains the conents of the e-mail that lay between the
     *  the multipart/mixed boundary. 
     * 
     *  @todo Why does it fail? Multiple boundaries?
     */
    $matches = array();
    $body = $email['html'];
    
    if (preg_match("/Content-Type: multipart\/alternative;[\s]+boundary=\"?" . 
        "([\w'()+,\-.\/\?=:]+)\"?\r?\n/ms", $body, $matches)) {
      $boundary = $matches[1];
      preg_match_all("/Content-Type: text\/(html|plain); [\w\"\-=]+\s?\s". 
          "(Content-Transfer-Encoding: [\w\"\-]+\s?\s)?\s?\s(.*?)\s" . 
          "\-{2,}{$boundary}/ms", $body, $matches);
      $keys = $matches[1];
      $text = $matches[3];
      // Concatenate like parts
      $types = array_unique($keys);
      foreach ($types as $type) {
        foreach ($keys as $index => $key) {
          if ($key === $type) {
            $textparts[$key] .= $text[$index];
          }
        }
      }
      
      $body = isset($textparts['html']) ? 
          $textparts['html'] : $textparts['plain'];
    } else {
      $body = $email['html']; // mimemail parsed the e-mail properly
    }
    
    return $body;
  }
  
  /** @todo check multi email */
  /** @todo send multi email, in spreadsheet/requirements*/
  function drush_gl_mail_incoming_mail() {
    error_reporting(0); // Disable errors so they don't make it to bounces
    
    if (variable_get('gl_mail_incoming_disabled', FALSE)) {
      exit(EX_UNAVAILABLE);
    }
    
    module_load_include('inc', 'mimemail', 'includes/mimemail.incoming');
    
    $email = stream_get_contents(STDIN);            // read encoded raw e-mail
    $email = base64_decode($email);                 // decode e-mail
    $email = mimemail_parse($email);                // parse e-mail into array
    // $email['html'] = _parse_email_for_body($email); // re-parse to fix bugs
    
    $log = variable_get('gl_mail_logging_enabled', FALSE);
    if ($log) { watchdog('gl_mail', 'Incoming e-mail: ' . print_r($email, TRUE)); }
    
    // Send to registered mail handlers
    $hook = 'incoming_mail';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        $result = call_user_func_array($function, array(&$email));
        switch ($result) {
        case TRUE:
          return;   // handled
          break;
        case FALSE:
          continue; // doesn't handle this e-mail or just made modifications
          break;
        case MAIL_ERROR_USER_NOT_FOUND:
          if ($log) { watchdog('gl_mail', 'Error: User not found'); }
          exit(EX_NOUSER);
          break;
        case MAIL_ERROR_PERMISSION_DENIED:
          if ($log) { watchdog('gl_mail', 'Error: Permission denied'); }
          exit(EX_NOPERM);
          break;
        case MAIL_ERROR_SOFTWARE:
        default:
          if ($log) { watchdog('gl_mail', 'Error: Software error'); }
          exit(EX_SOFTWARE);
          break;
        }
      }
    }

    exit(EX_UNAVAILABLE);
  }
