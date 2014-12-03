<?php

  /**
   * Guidelines for the email engine that gb_maillist (and others) will use
   */
   
  /**
   * Interface to define a standard email (not mime)
   * 
   * @todo will we ever need this?
   * 
   * @api
   */
  interface IEmail {}
  
  /**
   * Interface to generate and represent a multipart mime email.
   * 
   * To be implemeneted by the mailing engine.
   * 
   * @api
   */
  interface IMultipartMimeEmail extends IEmail {    
    /**
     * This method sets the paths for the e-mail.
     * 
     * @param string $to the e-mail address to deliver to.
     * @param string $from the e-mail address where it's coming from
     * @param string $reply_to the e-mail the recipient should reply to.
     */
    public function set_paths($to, $from, $reply_to);
    
    /**
     * This method sets the subject of the e-mail.
     * 
     * @param string $subject the subject.
     */
    public function set_subject($subject);
    
    /**
     * This method sets the main body of the e-mail. HTML & Plaintext.
     * 
     * @param string $body the body of the e-mail.
     * @param boolean $plain is the body plaintext?
     */
    public function set_main_body($body, $plain);
    
    /**
     * This method adds an alternative text mime part to the e-mail.
     * 
     * @param string $body the alternative text body.
     */
    public function set_alt_body($alt_body);
    
    /**
     * This method adds an additional body to the body array
     * 
     * @param string $body the body to add.
     */
    public function add_additional_body($body); 
    
    /**
     * This method adds a header to the e-mail.
     * 
     * @param string $header the header to set.
     * @param string $value the value to set the header to.
     */
    public function add_header($header, $value);
    
    /**
     * This method adds an attachment to the e-mail.
     * 
     * @param string $filename the file's path.
     * @param string $filemime the file's mimetype, e.g. application/pdf
     */
    public function add_attachment($filename, $filemime);
    
    /** getter for 'readonly' variables */
    public function __get($property);
    
    /** isset for 'readonly' variables */
    public function __isset($property);
    
    /** 
     * Consturctor 
     *
     * @param string $key the key to use for this e-mail.
     * @param array $variables data to be passed to the template files which
     *        are keyed by $key.
     */
    public function __construct($key, $variables);
  }

  /**
   * Interface to dispatch (send) email.
   * 
   * To be implementing by the mailing engine.
   * 
   * @api
   */
  interface IEmailDispatcher {
    /**
     * Constructor for the dispatcher.
     * 
     * @param string $sender the address of the sender of this e-mail.
     * @param string $bounces the address bounces and errors should go to.
     * @param boolean $send whether or not to actually send the e-mail.
     */
    public function __construct($sender, $bounces, $send);
    
    /**
     * This method dispatches an email.
     * 
     * @param IEmail $email the email to dispatch
     * 
     * @return boolean
     */
    public function dispatch(IEmail $email);
    
    /**
     * This method dispatches a group of email in batch.
     * 
     * @param array $emails an array of IEmail objects to dispatch.
     * @param boolean $send whether to actually send the e-mail
     * 
     * @return an array of booleans
     */
    public function dispatch_batch(array $emails);
  }
  