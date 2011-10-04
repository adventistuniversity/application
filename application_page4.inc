<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 4.
 * 
 */

  function application_form_page4($form_state) {
  $form = array();  
  _application_form_page4_load_defaults($form_state);
  ahah_helper_register($form, $form_state);
  $states = sonisweb_integration_dropbox_to_form_api_options_array(
              sonisweb_integration_api("CFC.drp_box", "state", "no", array(array('sonis_ds', '#sonis.ds#'),
                                       array('allow_blank', "yes"),
                                       array('hide', "no"),
                                       array('multi_select', "no"),
                                       array('Additional_Properties', ""),
                                       array('hide_excludes', 'yes'))));
  // page 4
  // Statistical Data
  $form['Statistical Data'] = array(
      '#type' => 'fieldset',
      '#title' => t('Statistical Data'),
    '#description' => "FHCHS is required to submit various state and federal reports which use the demographic information collected on this page. <strong>None of the information will be used for admissions purposes.</strong>",
    '#prefix' => '<div id="Statistical-Data-information-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

  // Veteran
  $form['Statistical Data']['veteran'] = array(
    '#type' => 'select',
    '#title' => t('Are you a US Military Veteran?'),
    '#default_value' => $form_state['values']['veteran'],
    '#required' => TRUE,
        '#ahah' => array(
      'path' => ahah_helper_path(array('Statistical Data')),
      'wrapper' => 'Statistical-Data-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
      ),
    '#options' => array(
      '' => '',
      '1' => t('Yes'),
      '0' => t('No')),
  );

  $form['Statistical Data']['update_veteran'] = array(
    '#type' => 'submit',
    '#value' => t('veteran'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if ($form_state['values']['veteran'] == "1") {
    $form['Statistical Data']['veteranbenefits'] = array(
      '#type' => 'select',
      '#title' => t('Will you be receiving VA benefits?'),
      '#default_value' => $form_state['values']['veteranbenefits'],
      '#required' => TRUE,
      '#options' => array(
        '' => '',
        '1' => t('Yes'),
        '0' => t('No')),
    );
  }

  $gender = sonisweb_integration_dropbox_to_form_api_options_array(
           sonisweb_integration_api("CFC.gender", "gender_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                    array('allow_blank', "yes"),
                                    array('multi_select', "no"),
                                    array('hide', "no"))));
  asort($gender);
  $gender = array_merge(array('' => ''), $gender);
  $form['Statistical Data']['gender'] = array(
    '#type' => 'select',
    '#title' => t('Gender'),
    '#default_value' => $form_state['values']['gender'],
    '#required' => TRUE,
    '#options' => $gender,
  );
  $form['Statistical Data']['attend'] = array(
    '#type' => 'select',
    '#title' => t('Did either of your parents attend college?'),
    '#default_value' => $form_state['values']['attend'],
    '#required' => TRUE,
    '#options' => array(
      '' => '',
      '1' => t('Yes'),
      '0' => t('No')),
  );

  // ethinic origin must be two step question
  $form['Statistical Data']['ethnicorigin'] = array(
    '#type' => 'select',
    '#title' => t('Are you Hispanic?'),
    '#default_value' => $form_state['values']['ethnicorigin'],
    '#required' => TRUE,
        '#ahah' => array(
      'path' => ahah_helper_path(array('Statistical Data')),
      'wrapper' => 'Statistical-Data-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
      ),
    '#options' => array(
      '' => '',
      'H' => t('Yes'),
      '0' => t('No')),
  );

  $form['Statistical Data']['update_ethnicorigin'] = array(
    '#type' => 'submit',
    '#value' => t('ethnicorigin'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if ($form_state['values']['ethnicorigin'] == "H" || $form_state['values']['ethnicorigin'] == "0" || $form_state['values']['ethnicorigin'] == "I prefer not to share.") {
    $ethnic = sonisweb_integration_dropbox_to_form_api_options_array(
              sonisweb_integration_api("CFC.ethnic", "ethnic_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                       array('allow_blank', "yes"),
                                       array('multi_select', "no"))));
    unset($ethnic['H']);
    asort($ethnic);
    $ethnic = array_merge(array('' => ''), $ethnic);
    $form['Statistical Data']['ethnicorigin2'] = array(
      '#type' => 'select',
      '#title' => t('Ethnic Origin'),
      '#default_value' => $form_state['values']['ethnicorigin2'],
      '#required' => ($form_state['values']['ethnicorigin'] == "0"), // Returns TRUE or FALSE
      '#options' => $ethnic,
    );
  }

  $tuit_stat = sonisweb_integration_dropbox_to_form_api_options_array(
               sonisweb_integration_api("CFC.tuitstat", "tuitstat_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                        array('allow_blank', "yes"),
                                        array('multi_select', "no"),
                                        array('hide', "no"))));
  asort($tuit_stat);
  $tuit_stat = array_merge(array('' => ''), $tuit_stat);
  $form['Statistical Data']['religion'] = array(
    '#type' => 'select',
    '#title' => t('Religious Preference'),
    '#default_value' => $form_state['values']['religion'],
    '#required' => TRUE,
    '#ahah' => array(
      'path' => ahah_helper_path(array('Statistical Data')),
      'wrapper' => 'Statistical-Data-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
      ),
    '#options' => $tuit_stat,
  );
  $form['Statistical Data']['update_religion'] = array(
    '#type' => 'submit',
    '#value' => t('religion'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );


  if ($form_state['values']['religion'] == "SA") {
    // if Adventist then show Home church + City and State
    $form['Statistical Data']['religionhomechurchstate'] = array(
      '#type' => 'select',
      '#title' => t('Home Church State'),
      '#default_value' => $form_state['values']['religionhomechurchstate'],
      '#options' => $states,
      '#required' => FALSE,
    );
    $form['Statistical Data']['religionhomechurchcity'] = array(
      '#type' => 'textfield',
      '#title' => t('Home Church City'),
      '#default_value' => $form_state['values']['religionhomechurchcity'],
      '#required' => FALSE,
      '#maxlength' => 50,
      '#size' => 50,      
    );
    $form['Statistical Data']['religionhomechurch'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of Home Church'),
      '#default_value' => $form_state['values']['religionhomechurch'],
      '#required' => FALSE,
      '#maxlength' => 50,
      '#size' => 50,      
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
  
function application_form_page4_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['gender'] == 'I prefer not to share.') {
    $form_state['values']['gender'] = 'U';
  }
  if ($form_state['values']['ethnicorigin'] == 'I prefer not to share.') {
    $form_state['values']['ethnicorigin'] = 'U';
  }
  if ($form_state['values']['ethnicorigin2'] == 'I prefer not to share.') {
    $form_state['values']['ethnicorigin2'] = 'N';
  }
  if ($form_state['values']['religion'] == 'I prefer not to share.') {
    $form_state['values']['religion'] = 'O';
  }  

  $biographic_sql = "UPDATE {application_Biographic} SET Statistics_Gender = '%s', Statistics_Hispanic = '%s',  Statistics_Ethnic_Origin = '%s',  Statistics_Religious_Affiliation = '%s', Statistics_Home_Church = '%s', Statistics_Home_Church_City = '%s', Statistics_Home_Church_State = '%s', Statistics_First_Generation = '%s', Statistics_US_Military_Veteran = '%s', Statistics_Receiving_Veteran_Benefits = '%s' WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, $form_state['values']['gender'], $form_state['values']['ethnicorigin'], $form_state['values']['ethnicorigin2'],  $form_state['values']['religion'], $form_state['values']['religionhomechurch'], $form_state['values']['religionhomechurchcity'], $form_state['values']['religionhomechurchstate'], $form_state['values']['attend'], $form_state['values']['veteran'], ($form_state['values']['veteranbenefits']==''?0:$form_state['values']['veteranbenefits']), $user->uid);
  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

  drupal_set_message(t('Your Statistical Information has been recorded.'));
  if ($form_state['values']['op'] == "Save and Return Later") {
    drupal_goto('logout');
  }
  else {
    drupal_goto('application/generalcollegeapplication5');
  }
}

function _application_form_page4_load_defaults(&$form_state) {
  global $user;

  $biographic_sql = "SELECT Statistics_Gender, Statistics_Hispanic, Statistics_Ethnic_Origin, Statistics_Native_English, Statistics_Native_Language, Statistics_Marital_Status, Statistics_Religious_Affiliation, Statistics_Home_Church, Statistics_Home_Church_City, Statistics_Home_Church_State, Statistics_First_Generation, Statistics_US_Military_Veteran, Statistics_Receiving_Veteran_Benefits FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));
 
  if (!isset($form_state['values']['gender']))
    $form_state['values']['gender']                   = $a['Statistics_Gender'];
  if (!isset($form_state['values']['ethnicorigin']))
    $form_state['values']['ethnicorigin']             = $a['Statistics_Hispanic'];
  if (!isset($form_state['values']['ethnicorigin2']))
    $form_state['values']['ethnicorigin2']            = $a['Statistics_Ethnic_Origin'];
  if (!isset($form_state['values']['religion']))
    $form_state['values']['religion']                 = $a['Statistics_Religious_Affiliation'];
  if (!isset($form_state['values']['religionhomechurch']))
    $form_state['values']['religionhomechurch']       = $a['Statistics_Home_Church'];
  if (!isset($form_state['values']['religionhomechurchcity']))
    $form_state['values']['religionhomechurchcity']   = $a['Statistics_Home_Church_City'];
  if (!isset($form_state['values']['religionhomechurchstate']))
    $form_state['values']['religionhomechurchstate']  = $a['Statistics_Home_Church_State'];
  if (!isset($form_state['values']['attend']))
    $form_state['values']['attend']                   = $a['Statistics_First_Generation'];
  if (!isset($form_state['values']['veteran']))
    $form_state['values']['veteran']                  = $a['Statistics_US_Military_Veteran'];
  if (!isset($form_state['values']['veteranbenefits']))
    $form_state['values']['veteranbenefits']          = $a['Statistics_Receiving_Veteran_Benefits'];

 //print_r($form_state);
  
}
  
