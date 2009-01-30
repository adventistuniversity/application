<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 3.
 * 
 */
require_once('sonis_sql.inc');
require_once('CFsoap.php');

function application_form_page3($form_state) {
  $form = array();
  _application_form_page3_load_defaults($form_state);
  ahah_helper_register($form, $form_state);

  // Page 3
  // Educational Experience - Plans for Study at FHCHS
  $form['Plans for Study'] = array(
      '#type' => 'fieldset',
      '#title' => t('Plans for Study at FHCHS'),
      '#description' => "Please select the year, term, department and programs you would like to apply for.",
      '#prefix' => '<div id="plans-for-study-wrapper"><p>The following degrees will require proof of a certificate, diploma, or Associate degree in addition to proof of professional licensure before admission may be granted.</p>
	<ul>
	<li>B.S. Diagnostic Medical Sonography</li>
	<li>B.S. Nursing</li>
	<li>B.S. Radiologic Sciences</li>
	<li>Certificate in Advanced Imaging Modalities (CT/MRI)</li>
	<li>Certificate in Diagnostic Medical Sonography</li>
	<li>Certificate in Nuclear Medicine Technology</li>
	<li>M.S. Nurse Anesthesia</li>
	</ul>
	<p>If you do not have a prior degree in a related field or the required licensure, please check that you would like to pursue the A.S. degree in your desired field of study.</p>', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
  $form['Plans for Study']['yearofinterest'] = array(
      '#type' => 'select',
      '#title' => t('School Year'),
      '#default_value' => $form_state['values']['yearofinterest'],
      '#options' => _application_query_to_form_array("select top 3 * from pretty_years order by year desc", TRUE),
      '#required' => TRUE,
  );
  $form['Plans for Study']['termofinterest'] = array(
      '#type' => 'select',
      '#title' => t('Start Term'),
      '#default_value' => $form_state['values']['termofinterest'],
      '#options' => _application_query_to_form_array("select semester, sm_desc from semester where disabled = 0 order by semester asc", TRUE),
      '#required' => TRUE,
  );
  $form['Plans for Study']['department1'] = array(
      '#type' => 'select',
      '#title' => t('First Department Choice'),
      '#default_value' => $form_state['values']['department1'],
      '#options' => _application_query_to_form_array("select dept_cod, dept_txt from dept where disabled = 0 and dept_cod <> '". $form_state['values']['department2'] ."' order by dept_txt asc", TRUE),
      '#required' => TRUE,
      '#ahah' => array(
       'path' => ahah_helper_path(array('Plans for Study')),
       'wrapper' => 'plans-for-study-wrapper',
       'method' => 'replace',
       'event' => 'change',
       'effect' => 'fade',
      ),
    '#required' => TRUE,
  );
  $form['Plans for Study']['update_department1'] = array(
    '#type' => 'submit',
    '#value' => t('First Department Choice'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if ($form_state['values']['department1'] != "") {
    $form['Plans for Study']['programs1'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Programs'),
        '#default_value' => $form_state['values']['programs1'],
        '#options' => _application_query_to_form_array("select program.prg_cod, program.prg_txt from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $form_state['values']['department1'] ."' order by prg_txt asc", FALSE),
        '#required' => FALSE,
    );
  }
  $form['Plans for Study']['department2'] = array(
      '#type' => 'select',
      '#title' => t('Second Department Choice'),
    '#description' => t('The second department choice is optional.'),
      '#default_value' => $form_state['values']['department2'],
      '#options' => _application_query_to_form_array("select dept_cod, dept_txt from dept where disabled = 0 and dept_cod <> '". $form_state['values']['department1'] ."' order by dept_txt asc", TRUE),
      '#ahah' => array(
       'path' => ahah_helper_path(array('Plans for Study')),
       'wrapper' => 'plans-for-study-wrapper',
       'method' => 'replace',
       'event' => 'change',
       'effect' => 'fade',
      ),
      '#required' => FALSE,
  );
  $form['Plans for Study']['update_department2'] = array(
    '#type' => 'submit',
    '#value' => t('Second Department Choice'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if ($form_state['values']['department2'] != "" && $form_state['values']['department2'] != $form_state['values']['department1']) {
    $form['Plans for Study']['programs2'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Programs'),
        '#default_value' => $form_state['values']['programs2'],
        '#options' => _application_query_to_form_array("select program.prg_cod, program.prg_txt from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $form_state['values']['department2'] ."' order by prg_txt asc", FALSE),
        '#required' => FALSE,
    );
  }
  $form['Submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Continue'),
  );

  return ($form);

}

function application_form_page3_submit($form, &$form_state) {
  global $user;

  // delete old programs
  $programs_delete_sql = "DELETE FROM {application_Programs} WHERE Student_StudentID = '%s'";
  db_query($programs_delete_sql, $user->uid);


  $picks = $picks .  "You will be considered for: ";
   
  foreach ($form_state['values']['programs1'] as $key => $value) {
      
    if ($value != '0') {
      $picks = $picks ."$key, ";
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department, Program)VALUES('%s', '%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department1'], $key);
    }
    // else {
     // // $picks = $picks . "$key Not Picked, ";
    // }    
  }

  if ($form_state['values']['department2'] != '') {
    foreach ($form_state['values']['programs2'] as $key => $value) {
    if ($value != '0') {
      $picks = $picks ."$key, ";
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department, Program)VALUES('%s', '%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department2'], $key);
    }
    // else {
     // // $picks = $picks . "$key Not Picked, ";
    // }    
    }
  }
 //print_r($form_state);
//drupal_set_message(t('Thank you for selecting some programs. %programs programs', array('%programs' => $picks)));
  drupal_set_message(t('Thank you for indicating your academic plans.'));
drupal_goto('application/generalcollegeapplication4');
}

function _application_form_page3_load_defaults(&$form_state) {
  if(sizeof($_POST)) {
  }
  else {
    global $user;

    $programs_sql = "SELECT Program_Applicaiton_ID, Student_StudentID, Year, Term, Department, Program FROM {application_Programs} WHERE Student_StudentID = '%s' ORDER BY Department";
    $result= db_query($programs_sql, $user->uid);
    // set a department variable so when it changes we can start populating the second programs array
    $loop = '1';

    $i = 0;
    while ($a = db_fetch_array($result)) {

      if($i == 0) {
        $form_state['values']['yearofinterest']                   = $a ['Year'];
        $form_state['values']['termofinterest']                   = $a ['Term'];
        $form_state['values']['department1']                      = $a ['Department'];
        // set a flag to show if were working with department1 or department2
        $department = $a['Department'];
        // get the list of programs for the first department
        $selectionboxes = _application_query_to_form_array("select program.prg_cod, '0' from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $a['Department'] ."' order by prg_txt asc", FALSE);
      }
      if($department != $a['Department'] && $a['Department'] != ''){
        $form_state['values']['department2']                = $a['Department'];
        $department = $a['Department'];
        // get the new list of programs for department2
        $selectionboxes1 = $selectionboxes;
        $selectionboxes = _application_query_to_form_array("select program.prg_cod, '0' from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $a['Department'] ."' order by prg_txt asc", FALSE);
        $loop = '2';
      }
      // make 'program' . $loop array
      if (array_key_exists($a['Program'],$selectionboxes)) {
        // set key
        $selectionboxes[$a['Program']] = $a['Program'];
      }
      $i++;
    }
     //print('<br>');
    if($loop == '2') {
      $form_state['values']['programs1'] = $selectionboxes1;    
      $form_state['values']['programs2'] = $selectionboxes;
    }
    if($loop == '1') {
      $form_state['values']['programs1'] = $selectionboxes;   
    }
  }
}
