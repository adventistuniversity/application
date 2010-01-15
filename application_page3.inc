<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 3.
 * 
 */

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
    
  $years = sonisweb_integration_dropbox_to_form_api_options_array(
           sonisweb_integration_api("CFC.sch_yr", "sch_yr_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                    array('allow_blank', "yes"),
                                    array('multi_select', "no"),
                                    array('hide', "no"),
                                    array('value', ""),
                                    array('size', "3"),
                                    array('use_cur_schyr', 'yes'))));
  asort($years);
  $terms = sonisweb_integration_dropbox_to_form_api_options_array(
           sonisweb_integration_api("CFC.semester", "semester_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                    array('allow_blank', "yes"),
                                    array('multi_select', "no"),
                                    array('hide', "no"))));
  asort($terms);
  $removal = _application_query_to_form_array("select '0', cur_schyr + cur_sem from sysvar", FALSE);
  $yearterms = array('' => '');
  foreach ($years as $yearcode => $prettyyear) {
    foreach ($terms as $termcode => $prettyterm) {
      if ($yearcode . $termcode > $removal[0]) {
        if ($termcode == "10") {
          $yearterms[$yearcode . $termcode] = $prettyterm ." ". substr($prettyyear, 0, 4);
        }
        else {
          $yearterms[$yearcode . $termcode] = $prettyterm ." ". (substr($prettyyear, 0, 4) + 1);
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
  $depts = sonisweb_integration_dropbox_to_form_api_options_array(
           sonisweb_integration_api("CFC.dept", "dept_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                    array('allow_blank', "yes"),
                                    array('use_cur_sem', "yes"),
                                    array('multi_select', "no"))));
  asort($depts);
  $depts = array_merge(array('' => ''), $depts);
  $form['Plans for Study']['department1'] = array(
      '#type' => 'select',
      '#title' => t('First Department Choice'),
      '#default_value' => $form_state['values']['department1'],
      '#options' => $depts,
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
        '#required' => TRUE,
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
      // make 'program' . $loop array
      if (array_key_exists($a['Program'], $selectionboxes)) {
        // set key
        $selectionboxes[$a['Program']] = $a['Program'];
      }
      $i++;
    }
     //print('<br>');
    $form_state['values']['programs1'] = $selectionboxes;
  }
}
