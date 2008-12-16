<?php

function application_form_page2($form_state) {
  $form = array();

  ahah_helper_register($form, $form_state);

// Academic Plans and Experience - Page 2
//
$form['High School Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('High School Experience'),
	'#description' => "",
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['High School Experience']['attendhigh school'] = array(
    '#type' => 'radios',
    '#title' => t('Did you attend high school?'),
    '#default_value' => $form_state['values']['attendhigh school'], 
    '#required' => TRUE,
	'#options' => array(t('Yes'), t('No')),
  );
// if Yes, then show High School, if No then show GED
$form['High School Experience']['high schoolname'] = array(
  '#type' => 'textfield',
  '#title' => t('Name of last high school attended'),
  '#default_value' => $form_state['values']['high schoolname'], 
  '#required' => TRUE,
);
$form['High School Experience']['high schoolcountry'] = array(
    '#type' => 'select',
    '#title' => t('high school Country'),
    '#default_value' => $form_state['values']['high schoolcountry'], 
  '#options' => array(
    'USA' => t('USA'),
    'Chile' => t('Chile'),
    'Italy' => t('Italy'),
  ),
    '#required' => TRUE,
  );
  $form['High School Experience']['high schoolcity'] = array(
    '#type' => 'textfield',
    '#title' => t('high school City'),
    '#default_value' => $form_state['values']['high schoolcity'], 
     '#required' => TRUE,
  );
  $form['High School Experience']['high schoolstate'] = array(
    '#type' => 'select',
    '#title' => t('high school State'),
    '#default_value' => $form_state['values']['high schoolstate'], 
  '#options' => array(
    'FL' => t('Florida'),
    'MS' => t('Mississippi'),
    'NY' => t('New York'),
  ),
    '#required' => FALSE,
  );
// GED
$form['GED Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Equivalency Diploma (GED) Experience'),
	'#description' => "",
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
$form['GED Experience']['gedtesting'] = array(
  '#type' => 'textfield',
  '#title' => t('GED Testing Site'),
  '#default_value' => $form_state['values']['gedtesting'], 
  '#required' => TRUE,
);
$form['GED Experience']['geddate'] = array(
   '#type' => 'date',
   '#title' => t('Date of Issue'),
   '#default_value' => $form_state['values']['geddate'], 
    '#required' => TRUE,
 );
// Postsecondary Educational Experience
$form['Postsecondary Educational Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('Postsecondary Educational Experience Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
	'#field_suffix' => t('You must submit official transcripts from all of your previous educational institutions. Transcripts must be received by FHCHS directly from the issuing institution. Faxes are not considered official. Transcript request forms are provided after completing this application.')
  ); // why doesn't this work?
$form['Postsecondary Educational Experience']['attendpostsecondary'] = array(
    '#type' => 'radios',
    '#title' => t('Have you attended any colleges, universities or other postsecondary institutions?'),
    '#default_value' => $form_state['values']['attendpostsecondary'], 
    '#required' => TRUE,
	'#options' => array(t('Yes'), t('No')),
  );
return ($form);

}
