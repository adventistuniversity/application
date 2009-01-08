<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 5.
 * 
 */
  require_once('CFsoap.php');
  require_once('sonis_sql.inc');
  
function application_form_page5($form_state) {
  $form = array();
  ahah_helper_register($form, $form_state);
  
    $form['Personal Statement'] = array(
      '#type' => 'fieldset',
      '#title' => t('Personal Statement'),
      '#description' => "",
      '#prefix' => '<div id="Personal-Statement-study-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
  $form['Personal Statement']['Iagree'] = array(
        '#prefix' => '<p>I certify that to the best of my knowledge the statements made in this application form and all subsequent forms are correct. I also understand that withholding information or giving false information on any part of my application form may make me ineligible for admission or may later subject me to dismissal.</p><p>By submitting this application, I agree to abide by the policies and regulations of the College.</p>',
      '#type' => 'submit',
      '#value' => t('I Agree, Submit Application'),
      '#required' => TRUE,
  );
  
  return ($form);

}
// Form should redirect to: /application/generalcollegeapplicaion/submitted
function application_form_page5_submit($form, &$form_state) {
  global $user;

  $biographic_sql = "UPDATE {application_Biographic} SET Personal_Statement_Agreement = '%d'WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, '1', $user->uid);

drupal_goto('application/generalcollegeapplication/submitted');
}
