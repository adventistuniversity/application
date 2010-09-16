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
  $limited_programs = _application_form_page3_load_defaults($form_state);
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
  $campus = _application_query_to_form_array("select camp_cod, camp_txt from campus where camp_mem like '%#onlineapp%' order by camp_txt", TRUE);
  $form['Plans for Study']['campus'] = array(
      '#type' => 'select',
      '#title' => t('Campus'),
      '#default_value' => $form_state['values']['campus'],
      '#options' => $campus,
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
  $form['Plans for Study']['update_campus'] = array(
    '#type' => 'submit',
    '#value' => t('Campus Choice'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if (isset($form_state['values']['campus']) && strlen($form_state['values']['campus']) == 2) {
    $depts = _application_query_to_form_array("select dept.dept_cod, dept.dept_txt ".
                                              "from dept inner join ( ".
                                              "	select distinct programfilter.dept_cod ".
                                              "	from (select distinct div_cod, dept_cod, camp_cod ".
                                              "			 from name inner join nmmodst on name.soc_sec = nmmodst.soc_sec and mod_stat = 'ST' ".
                                              "           and name.soc_sec <> 'LI8793682' UNION select 'RE', 'RS', 'DV') as name ".
                                              "		inner join programfilter on ".
                                              "			name.div_cod = programfilter.div_cod and name.dept_cod = programfilter.dept_cod ".
                                              "	where name.camp_cod = '".$form_state['values']['campus']."') as a on dept.dept_cod = a.dept_cod ".
                                              "order by dept.dept_txt", TRUE);
  }
  else {
    $depts = array('' => '');
  }
  if ($depts != array('' => '')) {
    $form['Plans for Study']['department1'] = array(
        '#type' => 'select',
        '#title' => t('Department Choice'),
        '#description' => t('All undergraduate Main Campus program will be automatically reviewed for General College.  Please select the program from which you hope to graduate.'),
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
      '#value' => t('Department Choice'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
  }
  else {
    $form['Plans for Study']['department1'] = array(
        '#type' => 'select',
        '#title' => t('Department Choice'),
        '#description' => t('All undergraduate Main Campus program will be automatically reviewed for General College.  Please select the program from which you hope to graduate.'),
        '#options' => array('' => 'Please Select a Campus'),
        '#required' => TRUE,
        '#disabled' => TRUE,
    );
  }
  
  if (isset($form_state['values']['campus']) && strlen($form_state['values']['campus']) == 2 &&
      isset($form_state['values']['department1']) && $form_state['values']['department1'] != "") {
    $programs = _application_query_to_form_array("select program.prg_cod, CASE WHEN program.memo is null or program.memo LIKE '' THEN rtrim(program.prg_txt) ELSE rtrim(program.prg_txt) + '<br /><span class=\"label-memo\">' + CAST(program.memo as varchar(8000)) + '</span></label>' END ".
                                                 "from program inner join ( ".
                                                 " 	select distinct programfilter.prg_cod ".
                                                 " 	from (select distinct div_cod, dept_cod, camp_cod ".
                                                 " 			 from name inner join nmmodst on name.soc_sec = nmmodst.soc_sec and nmmodst.mod_stat = 'ST' ".
                                                 "       where rtrim(name.camp_cod)+rtrim(name.dept_cod)+rtrim(name.div_cod) not in ('DINURE', 'CONUDL', 'CORSDL')".
                                                 " 	  	 UNION select 'RE', 'RS', 'DV') as name inner join programfilter on ".
                                                 " 			name.div_cod = programfilter.div_cod and name.dept_cod = programfilter.dept_cod ".
                                                 " 	where name.camp_cod = '".$form_state['values']['campus']."' and name.dept_cod = '". $form_state['values']['department1'] ."'".
                                                 "         and rtrim(name.camp_cod)+rtrim(programfilter.prg_cod) not in ('DVASNM', 'DVCNMT')) as a on".
                                                 "  program.prg_cod = a.prg_cod ".
                                                 "order by prg_txt asc", FALSE);
    for ($i = 0; $i < count($limited_programs); $i++) {
      if (isset($programs[$limited_programs[$i]])) {
        $banned_programs[$limited_programs[$i]] = $programs[$limited_programs[$i]];
        unset($programs[$limited_programs[$i]]);
      }
    }
  }
  else {
    $programs = array('' => '');
  }
  if ($form_state['values']['department1'] != "" && $programs != array() && $programs != array('' => '')) {
    $form['Plans for Study']['programs1'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Programs'),
        '#default_value' => $form_state['values']['programs1'],
        '#options' => $programs,
        '#required' => TRUE,
    );
  }
  else {
    $form['Plans for Study']['programs1'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Programs'),
        '#options' => (count($banned_programs) > 0?array('' => 'None based on qualifications'):array('' => 'Please Select a Department')),
        '#required' => TRUE,
        '#disabled' => TRUE,
    );
  }
  if (count($banned_programs) > 0) {
    $form['Plans for Study']['programsignored'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Additional Degree Programs Offered'),
        '#prefix' => t('Based on your <a href="generalcollegeapplication2">academic experience</a> or licensure it appears you are not eligible for the following programs.'),
        '#options' => $banned_programs,
        '#disabled' => TRUE,
        '#required' => FALSE,
    );
  }
  $form['Submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Continue'),
  );
  $form['Logout'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Return Later'),
  '#prefix' => '<div class="button_secondary">',
  '#suffix' => '</div>',
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
      $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Campus, Department, Program)VALUES('%s', '%s', '%s', '%s', '%s', '%s')";
      db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['campus'], $form_state['values']['department1'], $key);
    }
    // else {
     // // $picks = $picks . "$key Not Picked, ";
    // }    
  }
  if ($i == 0) {
    $programs_sql = "INSERT into {application_Programs} (Student_StudentID, Year, Term, Campus, Department)VALUES('%s', '%s', '%s', '%s', '%s')";
    db_query($programs_sql, $user->uid, $form_state['values']['yearofinterest'], $form_state['values']['termofinterest'], $form_state['values']['campus'], $form_state['values']['department1']);
  }


  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

//drupal_set_message(t('Thank you for selecting some programs. %programs programs', array('%programs' => $picks)));
  drupal_set_message(t('Thank you for indicating your academic plans.'));
  if ($form_state['values']['op'] == "Save and Return Later") {
    drupal_goto('logout');
  }
  else {
    drupal_goto('application/generalcollegeapplication4');
  }
}

function _application_form_page3_load_defaults(&$form_state) {
  global $user;
  if (sizeof($_POST)) {
  }
  else {

    $programs_sql = "SELECT Program_Applicaiton_ID, Student_StudentID, Year, Term, Campus, Department, Program FROM {application_Programs} WHERE Student_StudentID = '%s' ORDER BY Program_Applicaiton_ID";
    $result= db_query($programs_sql, $user->uid);

    $i = 0;
    while ($a = db_fetch_array($result)) {

      if ($i == 0) {
        $form_state['values']['yearofinterest']                   = $a ['Year'];
        $form_state['values']['termofinterest']                   = $a ['Term'];
        $form_state['values']['yearandtermofinterest']            = $a ['Year'] . $a ['Term'];
        $form_state['values']['department1']                      = $a ['Department'];
        $form_state['values']['campus']                           = $a ['Campus'];
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
  //Look up banned programs
  $limited_programs = sonisweb_integration_sql_to_options(sonisweb_integration_sql("select distinct prg_cod, appchk_txt from appchk inner join appchklist on appchk.appchk_cod = appchklist.appchk_cod where appchk_txt like '%license%' and disabled = 0"));
  //Look up cleared programs
  $cert_sql = "SELECT Cert FROM {application_Certs} WHERE Student_StudentID = '%s'";
  $result= db_query($cert_sql, $user->uid);

  $i = 0;
  $certs = array();
  while ($a = db_fetch_array($result)) {
    foreach ($limited_programs as $tmpk => $tmp) {
      if (stristr($tmp, $a['Cert'])) {
        unset($limited_programs[$tmpk]);
      }
    }
  }
  return (array_keys($limited_programs));
}
