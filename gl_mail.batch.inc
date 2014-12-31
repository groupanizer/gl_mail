<?php

  /** Callback called by e-mail batch operation */
  function _gl_mail_dispatch($dispatcher, $slice, &$context) {
    foreach ($slice as $email) {
      $result = $dispatcher->dispatch($email);
      // Include 'dispatcher' in the result because we need it later
      $context['results'][] = array('dispatcher' => $dispatcher, 
          'email' => $email, 'result' => $result,);
    }
  }
  
  /** Callback called at the end of the e-mail batch operation */
  function _gl_mail_dispatch_finished($success, $results, $operations) {
    $dispatcher = $results[0]['dispatcher'];
    if ($success) {
      // Include file if present
      if ($dispatcher->file) {
        require_once $dispatcher->file;
      }
      // Call finished callback if present
      if ($dispatcher->finished) {
        // Remove 'dispatcher' element
        array_walk($results, function ($item, $key) {
          unset($item['dispatcher']);
        });
        call_user_func($dispatcher->finished, $results);
      }
    } else {
      // An error occurred.
      // $operations contains the operations that remained unprocessed.
      $error_operation = reset($operations);
      $message = t('An error occurred while processing %error_operation with' .
          'arguments: @arguments', array(
          '%error_operation' => $error_operation[0], 
          '@arguments' => print_r($error_operation[1], TRUE)));
      watchdog('gl_mail', $message);
      drupal_set_message($message, 'error');
    }
  }
