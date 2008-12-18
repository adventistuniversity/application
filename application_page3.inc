<?php

require_once('sonis_sql.inc');
require_once('CFsoap.php');

function application_form_page3($form_state) {
  $form = array();

  ahah_helper_register($form, $form_state);

  // Page 3
  // Educational Experience - Plans for Study at FHCHS
  $form['Plans for Study'] = array(
      '#type' => 'fieldset',
      '#title' => t('Plans for Study at FHCHS'),
    	'#description' => "Please select the year, term, department and programs you would like to apply for.",
      '#prefix' => '<div id="plans-for-study-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => TRUE,
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
      '#options' => _application_query_to_form_array("select dept_cod, dept_txt from dept where disabled = 0 and dept_cod <> '".$form_state['values']['department2']."' order by dept_txt asc", TRUE),
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
        '#options' => _application_query_to_form_array("select program.prg_cod, program.prg_txt from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '".$form_state['values']['department1']."' order by prg_txt asc", FALSE),
        '#required' => FALSE,
    );
  }
  $form['Plans for Study']['department2'] = array(
      '#type' => 'select',
      '#title' => t('Second Department Choice'),
  	'#description' => t('The second department choice is optional.'),
      '#default_value' => $form_state['values']['department2'],
      '#options' => _application_query_to_form_array("select dept_cod, dept_txt from dept where disabled = 0 and dept_cod <> '".$form_state['values']['department1']."' order by dept_txt asc", TRUE),
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
        '#options' => _application_query_to_form_array("select program.prg_cod, program.prg_txt from program inner join programfilter on program.prg_cod = programfilter.prg_cod where programfilter.dept_cod = '".$form_state['values']['department2']."' order by prg_txt asc", FALSE),
        '#required' => FALSE,
    );
  }
  return ($form);

}
