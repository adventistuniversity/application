<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 5.
 * 
 */
  
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

function application_form_page5_validate($form, &$form_state) {
  global $user;

  $biographic_sql = "SELECT Student_Fname, HighSchool_Attendance, Statistics_Gender FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));

  if ($a) {
    if (!isset($a['Student_Fname']) || strlen(trim($a['Student_Fname'])) == 0 || strcasecmp(trim($a['Student_Fname']), "null") == 0)
      form_set_error('', t("Please Complete Personal Information Page before submitting your application."));
    if (!isset($a['HighSchool_Attendance']) || !is_numeric($a['HighSchool_Attendance']))
      form_set_error('', t("Please Complete Academic Experience Page before submitting your application."));
    $biographic_sql = "SELECT * FROM {application_Programs} WHERE Student_StudentID = '%s'";
    if (!db_fetch_array(db_query($biographic_sql, $user->uid)))
      form_set_error('', t("Please Complete Academic Plans Page before submitting your application."));
    if (!isset($a['Statistics_Gender']) || strlen(trim($a['Statistics_Gender'])) == 0 || strcasecmp(trim($a['Statistics_Gender']), "null") == 0)
      form_set_error('', t("Please Complete Statistical Data Page before submitting your application."));
  }
}

// Form should redirect to: /application/generalcollegeapplicaion/submitted
function application_form_page5_submit($form, &$form_state) {
  global $user;

  $biographic_sql = "UPDATE {application_Biographic} SET Personal_Statement_Agreement = '%d', Application_Finished = '%s' WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, '1', date("Y-m-d H:i:s"), $user->uid);


  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

  //Fire Application Completed Trigger
  module_invoke_all('application_changed', 'complete', $user);

  drupal_goto('application/generalcollegeapplication/submitted');
}
