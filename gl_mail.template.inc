<?php

  /**
   * Guidelines for the e-mail engine that gb_maillist (and others) will use
   */
   
  /**
   * Interface to define a standard e-mail (not mime)
   * 
   * @todo will we ever need this?
   * 
   * @api
   */
  interface IEmail {
    /** 
     * Consturctor 
     *
     * @param string $key the key to use for this e-mail.
     * @param array $variables data to be passed to the template files which
     *        are keyed by $key.
     */
    public function __construct($key, $variables);
    
    /** getter for 'readonly' variables */
    public function __get($property);
    
    /** isset for 'readonly' variables */
    public function __isset($property);
    
    /**
     * This method adds a header to the e-mail.
     * 
     * @param string $header the header to set.
     * @param string $value the value to set the header to.
     */
    public function add_header($header, $value);
    
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
     * This method adds the body to the e-mail.
     * 
     * @param string $body the body of the e-mail.
     */
    public function set_body($body);
  }
  
  /**
   * Interface to generate and represent a multipart mime e-mail.
   * 
   * To be implemeneted by the mailing engine.
   * 
   * @api
   */
  interface IMultipartMimeEmail extends IEmail {    
    /**
     * This method sets the alt plaintext body of the e-mail.
     *  
     * @param string $body the alt plaintext body of the e-mail.
     */
    public function set_alt_body($body);
    
    /**
     * This method adds an attachment to the e-mail.
     * 
     * @param string $filename the file's path.
     * @param string $filemime the file's mimetype, e.g. application/pdf
     */
    public function add_attachment($filename, $filemime);
  }

  /**
   * Interface to dispatch (send) e-mail.
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
     * @param string $finished a callback to receieve the results of dispatching
     * @param string $file the file the finished callback resides in
     */
    public function __construct($sender, $bounces, $finished, $file);
    
    /**
     * This method dispatches an e-mail.
     * 
     * @param IEmail $email the e-mail to dispatch
     * 
     * @return boolean
     */
    public function dispatch(IEmail $email);
    
    /**
     * This method dispatches a group of e-mail (in batch if necessary).
     * 
     * @param array $emails an array of IEmail objects to dispatch.
     * @param boolean $batch whether or not to dispatch in the background
     * 
     * @return nothing
     */
    public function dispatch_multiple(array $emails, $background);
  }
  