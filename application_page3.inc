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
      '#prefix' => '<div id="plans-for-study-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    
  $years = _application_query_to_form_array("select * from (select top 3 year, year_desc from pretty_years order by year DESC) as a order by year asc", FALSE);
  $terms = _application_query_to_form_array("select semester, sm_desc from semester where disabled = 0 order by semester asc", FALSE);
  $removal = _application_query_to_form_array("select '0', cur_schyr + cur_sem from sysvar", FALSE);
  $yearterms = array('' => '');
  foreach ($years as $yearcode => $prettyyear) {
    foreach ($terms as $termcode => $prettyterm) {
      if ($yearcode . $termcode > $removal[0]) {
        if ($termcode == "10") {
          $yearterms[$yearcode . $termcode] = $prettyterm ." ". substr($prettyyear, 0, 4);
        }
        else {
          $yearterms[$yearcode . $termcode] = $prettyterm ." ". substr($prettyyear, 5, 4);
        }
      }
    }
  }
  $form['Plans for Study']['yearandtermofinterest'] = array(
      '#type' => 'select',
      '#title' => t('School Year and Term'),
      '#default_value' => $form_state['values']['yearandtermofinterest'],
      '#options' => $yearterms,
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
        '#options' => _application_query_to_form_array("select program.prg_cod, CASE WHEN program.memo is null or program.memo LIKE '' THEN rtrim(program.prg_txt) ELSE rtrim(program.prg_txt) + '<br /><span class=\"label-memo\">' + CAST(program.memo as varchar(8000)) + '</span></label>' END from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $form_state['values']['department1'] ."' order by prg_txt asc", FALSE),
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
        '#options' => _application_query_to_form_array("select program.prg_cod, CASE WHEN program.memo is null or program.memo LIKE '' THEN rtrim(program.prg_txt) ELSE rtrim(program.prg_txt) + '<br /><span class=\"label-memo\">' + CAST(program.memo as varchar(8000)) + '</span></label>' END from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $form_state['values']['department2'] ."' order by prg_txt asc", FALSE),
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
  $form_state['values']['yearofinterest'] = substr($form_state['values']['yearandtermofinterest'], 0, 6);
  $form_state['values']['termofinterest'] = substr($form_state['values']['yearandtermofinterest'], 6, 2);

  // delete old programs
  $programs_delete_sql = "DELETE FROM {application_Programs} WHERE Student_StudentID = '%s'";
  db_query($programs_delete_sql, $user->uid);


  $picks = $picks .  "You will be considered for: ";
   
  $i = 0;
  foreach ($form_state['values']['programs1'] as $key => $value) {
    if ($value != '0') {
      $i++;
      $picks = $picks ."$key, ";
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department, Program)VALUES('%s', '%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department1'], $key);
    }
    // else {
     // // $picks = $picks . "$key Not Picked, ";
    // }    
  }
  if ($i == 0) {
    $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department)VALUES('%s', '%s', '%s', '%s')";
    db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department1']);
  }

  if ($form_state['values']['department2'] != '') {
    $i = 0;
    foreach ($form_state['values']['programs2'] as $key => $value) {
    if ($value != '0') {
      $i++;
      $picks = $picks ."$key, ";
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department, Program)VALUES('%s', '%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department2'], $key);
    }
    // else {
     // // $picks = $picks . "$key Not Picked, ";
    // }    
    }
    if ($i == 0) {
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Department)VALUES('%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['department2']);
    }
  }
 //print_r($form_state);

  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

//drupal_set_message(t('Thank you for selecting some programs. %programs programs', array('%programs' => $picks)));
  drupal_set_message(t('Thank you for indicating your academic plans.'));
  drupal_goto('application/generalcollegeapplication4');
}

function _application_form_page3_load_defaults(&$form_state) {
  if (sizeof($_POST)) {
  }
  else {
    global $user;

    $programs_sql = "SELECT Program_Applicaiton_ID, Student_StudentID, Year, Term, Department, Program FROM {application_Programs} WHERE Student_StudentID = '%s' ORDER BY Program_Applicaiton_ID";
    $result= db_query($programs_sql, $user->uid);
    // set a department variable so when it changes we can start populating the second programs array
    $loop = '1';

    $i = 0;
    while ($a = db_fetch_array($result)) {

      if ($i == 0) {
        $form_state['values']['yearofinterest']                   = $a ['Year'];
        $form_state['values']['termofinterest']                   = $a ['Term'];
        $form_state['values']['yearandtermofinterest']            = $a ['Year'] . $a ['Term'];
        $form_state['values']['department1']                      = $a ['Department'];
        // set a flag to show if were working with department1 or department2
        $department = $a['Department'];
        // get the list of programs for the first department
        $selectionboxes = _application_query_to_form_array("select program.prg_cod, '0' from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $a['Department'] ."' order by prg_txt asc", FALSE);
      }
      if ($department != $a['Department'] && $a['Department'] != '') {
        $form_state['values']['department2']                = $a['Department'];
        $department = $a['Department'];
        // get the new list of programs for department2
        $selectionboxes1 = $selectionboxes;
        $selectionboxes = _application_query_to_form_array("select program.prg_cod, '0' from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '". $a['Department'] ."' order by prg_txt asc", FALSE);
        $loop = '2';
      }
      // make 'program' . $loop array
      if (array_key_exists($a['Program'], $selectionboxes)) {
        // set key
        $selectionboxes[$a['Program']] = $a['Program'];
      }
      $i++;
    }
     //print('<br>');
    if ($loop == '2') {
      $form_state['values']['programs1'] = $selectionboxes1;    
      $form_state['values']['programs2'] = $selectionboxes;
    }
    if ($loop == '1') {
      $form_state['values']['programs1'] = $selectionboxes;   
    }
  }
}
