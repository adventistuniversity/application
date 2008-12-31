<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 2.
 * 
 */

  require_once('CFsoap.php');
  require_once('sonis_sql.inc');
  
function application_form_page2($form_state) {
  $form = array();
  ahah_helper_register($form, $form_state);
  
  $states = get_sonis_drop_box("state");
  $countries = get_sonis_drop_box("country");
  $years = get_years();
  $nograd = array("Did Not Complete Degree" => "Did Not Complete Degree");
  //$result = array_merge($nograd, $years);
  $result = $nograd + $years;
// Academic Plans and Experience - Page 2
//
$form['High School Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('High School Experience'),
  '#description' => "",
  '#prefix' => '<div id="High-School-Experience-information-wrapper">', // This is our wrapper div.
  '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['High School Experience']['attendhighschool'] = array(
    '#type' => 'select',
    '#title' => t('Did you attend High School?'),
    '#default_value' => $form_state['values']['attendhighschool'], 
    '#required' => TRUE,
  '#ahah' => array(
    'path' => ahah_helper_path(array('High School Experience')),
    'wrapper' => 'High-School-Experience-information-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'effect' => 'fade',
    ),
  '#options' => array('1' => t('Yes'),
    '0' => t('No')),
  );
$form['High School Experience']['update_attendhighschool'] = array(
  '#type' => 'submit',
  '#value' => t('attendhighschool'),
  '#submit' => array('ahah_helper_generic_submit'),
  '#attributes' => array('class' => 'no-js'),
);


// if Yes, then show High School, if No then show GED
if ($form_state['values']['attendhighschool'] == "1" || $form_state['values']['attendhighschool'] == "") {
  $form['High School Experience']['highschoolcountry'] = array(
    '#type' => 'select',
    '#title' => t('High School Country'),
    '#default_value' => ($form_state['values']['highschoolcountry'] == ""?"UNITED STATES":$form_state['values']['highschoolcountry']),
    '#options' => $countries,
    '#required' => TRUE,
    '#ahah' => array(
      'path' => ahah_helper_path(array('High School Experience')),
       'wrapper' => 'High-School-Experience-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
    ),
  );
  $form['High School Experience']['update_highschoolcountry'] = array(
    '#type' => 'submit',
    '#value' => t('High School Country'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );

  if ($form_state['values']['highschoolcountry'] == "" || $form_state['values']['highschoolcountry'] == "UNITED STATES") {
    $form['High School Experience']['highschoolstate'] = array(
      '#type' => 'select',
      '#title' => t('High School State'),
      '#default_value' => $form_state['values']['highschoolstate'],
      '#options' => $states,
      '#required' => TRUE,
      '#ahah' => array(
        'path' => ahah_helper_path(array('High School Experience')),
         'wrapper' => 'High-School-Experience-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
    );
    $form['High School Experience']['update_highschoolstate'] = array(
      '#type' => 'submit',
      '#value' => t('High School State'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
  }
  if ($form_state['values']['highschoolstate'] != "" && $form_state['values']['highschoolcountry'] == "UNITED STATES") {
    $form['High School Experience']['highschoolcity'] = array(
      '#type' => 'select',
      '#title' => t('High School City'),
      '#default_value' => $form_state['values']['highschoolcity'],
      '#options' => _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['highschoolstate'] ."' and insttypcod in ('1', '2') order by inst_city asc", TRUE, array('-1' => 'Not Listed')),
      '#required' => TRUE,
      '#ahah' => array(
        'path' => ahah_helper_path(array('High School Experience')),
         'wrapper' => 'High-School-Experience-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
    );
    $form['High School Experience']['update_highschoolcity'] = array(
      '#type' => 'submit',
      '#value' => t('High School City'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
  }
  if ($form_state['values']['highschoolstate'] == "" || $form_state['values']['highschoolcountry'] != "UNITED STATES" || $form_state['values']['highschoolcity'] == "-1") {
     $form['High School Experience']['highschoolcity_text'] = array(
      '#type' => 'textfield',
      '#title' => t('High School City'),
      '#default_value' => $form_state['values']['highschoolcity_text'],
      '#required' => TRUE,
      '#maxlength' => 20,
      '#size' => 20,
    );
  }
  else {
     $form['High School Experience']['highschoolcity_text'] = array(
      '#type' => 'hidden',
      '#value' => $form_state['values']['highschoolcity_text'],
    );
  }
  $form['High School Experience']['highschoolname'] = array(
    '#type' => 'select',
    '#title' => t('Name of last High School attended'),
    '#default_value' => $form_state['values']['highschoolname'],
    '#options' => _application_query_to_form_array("select distinct inst_cod, inst_txt from institut where inst_city = '". $form_state['values']['highschoolcity'] ."' and insttypcod in ('1', '2') order by inst_txt asc", TRUE, array('-1' => 'Not Listed')),
    '#required' => TRUE,
    '#ahah' => array(
      'path' => ahah_helper_path(array('High School Experience')),
       'wrapper' => 'High-School-Experience-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
    ),
  );
   $form['High School Experience']['update_highschoolname'] = array(
    '#type' => 'submit',
    '#value' => t('High School Name'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  if (!isset($form['High School Experience']['highschoolname_text'])) {
    $form['High School Experience']['highschoolname_text'] = array(
      '#type' => 'hidden',
      '#value' => $form_state['values']['highschoolname_text'],
    );
  }

  if ($form_state['values']['highschoolcity'] == "" || $form_state['values']['highschoolcity'] == "-1" || $form_state['values']['highschoolname'] == "-1" || $form_state['values']['highschoolstate'] == "" || $form_state['values']['highschoolcountry'] != "UNITED STATES") {
    $form['High School Experience']['highschoolname_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of last High School attended'),
      '#default_value' => $form_state['values']['highschoolname_text'],
      '#required' => TRUE,
      '#maxlength' => 50,
      '#size' => 50,
    );
  }
}
if($form_state['values']['attendhighschool'] == "0") {
  // GED
  $form['High School Experience']['gedtesting'] = array(
    '#type' => 'textfield',
    '#title' => t('GED Testing Site'),
    '#default_value' => $form_state['values']['gedtesting'], 
    '#required' => TRUE,
    '#maxlength' => 50,
    '#size' => 50,    
  );
  $form['High School Experience']['geddate'] = array(
    '#type' => 'date',
    '#title' => t('Date of Issue'),
    '#default_value' => $form_state['values']['geddate'], 
    '#required' => TRUE,
   );
}

// Postsecondary Educational Experience
$form['Postsecondary Educational Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('Postsecondary Educational Experience Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  '#prefix' => '<div id="Postsecondary-Educational-Experience-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
  '#field_suffix' => t('You must submit official transcripts from all of your previous educational institutions. Transcripts must be received by FHCHS directly from the issuing institution. Faxes are not considered official. Transcript request forms are provided after completing this application.')
  ); // why doesn't this work?
  

$form['Postsecondary Educational Experience']['attendpostsecondary'] = array(
    '#type' => 'select',
    '#title' => t('How many colleges, universities or other postsecondary institutions Have you attended?'),
    '#default_value' => $form_state['values']['attendpostsecondary'], 
    '#required' => TRUE,
  '#ahah' => array(
    'path' => ahah_helper_path(array('Postsecondary Educational Experience')),
    'wrapper' => 'Postsecondary-Educational-Experience-information-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'effect' => 'fade',
    ),
  '#options' => array(
    'None' => t('None'),
    '1' => t('1'),
    '2' => t('2'),
    '3' => t('3'),
    '4' => t('4'),
    '5' => t('5'),
    '6' => t('6'),
    '7' => t('7'),
    '8' => t('8'),
    '9' => t('9'),
    '10' => t('10')
    )
  );
$form['Postsecondary Educational Experience']['update_attendpostsecondary'] = array(
  '#type' => 'submit',
  '#value' => t('attendpostsecondary'),
  '#submit' => array('ahah_helper_generic_submit'),
  '#attributes' => array('class' => 'no-js'),
);



if($form_state['values']['attendpostsecondary'] != "None") {
  for ($i = 1; $i <= $form_state['values']['attendpostsecondary']; $i++) {
    $form['Postsecondary Educational Experience']['Institution '. $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Institution '. $i),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#prefix' => '<div id="Institutions-information-wrapper'. $i .'-information-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#field_suffix' => t('You must submit official transcripts from all of your previous educational institutions. Transcripts must be received by FHCHS directly from the issuing institution. Faxes are not considered official. Transcript request forms are provided after completing this application.')
    );
    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCountry'. $i] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => ($form_state['values']['postSecondaryCountry'. $i] == ""?"UNITED STATES":$form_state['values']['postSecondaryCountry'. $i]),
      '#required' => TRUE,
      '#options' => $countries,
      '#ahah' => array(
        'path' => ahah_helper_path(array('Postsecondary Educational Experience', 'Institution '. $i)),
         'wrapper' => 'Institutions-information-wrapper'. $i .'-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
    );
    $form['Postsecondary Educational Experience']['Institution '. $i]['update_postSecondaryCountry'. $i] = array(
      '#type' => 'submit',
      '#value' => t('Country'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
    if ($form_state['values']['postSecondaryCountry'. $i] == "" || $form_state['values']['postSecondaryCountry'. $i] == "UNITED STATES") {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryState'. $i] = array(
        '#type' => 'select',
        '#title' => t('State'),
        '#default_value' => $form_state['values']['postSecondaryState'. $i],
        '#required' => TRUE,
        '#options' => $states,
        '#ahah' => array(
          'path' => ahah_helper_path(array('Postsecondary Educational Experience', 'Institution '. $i)),
           'wrapper' => 'Institutions-information-wrapper'. $i .'-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      );
      $form['Postsecondary Educational Experience']['Institution '. $i]['update_postSecondaryState'. $i] = array(
        '#type' => 'submit',
        '#value' => t('State'),
        '#submit' => array('ahah_helper_generic_submit'),
        '#attributes' => array('class' => 'no-js'),
      );
    }
    if ($form_state['values']['postSecondaryState'. $i] != "" && $form_state['values']['postSecondaryCountry'. $i] == "UNITED STATES") {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i] = array(
        '#type' => 'select',
        '#title' => t('City'),
        '#default_value' => $form_state['values']['postSecondaryCity'. $i],
        '#required' => TRUE,
        '#options' => _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['postSecondaryState'. $i] ."' and insttypcod in ('3', '4', '5', '6', '7', '8', '9') order by inst_city asc", TRUE, array('-1' => 'Not Listed')),
        '#ahah' => array(
          'path' => ahah_helper_path(array('Postsecondary Educational Experience', 'Institution '. $i)),
           'wrapper' => 'Institutions-information-wrapper'. $i .'-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      );
      $form['Postsecondary Educational Experience']['Institution '. $i]['update_postSecondaryCity'. $i] = array(
        '#type' => 'submit',
        '#value' => t('City'),
        '#submit' => array('ahah_helper_generic_submit'),
        '#attributes' => array('class' => 'no-js'),
      );
    }
    if ($form_state['values']['postSecondaryState'. $i] == "" || $form_state['values']['postSecondaryCountry'. $i] != "UNITED STATES" || $form_state['values']['postSecondaryCity'. $i] == "-1") {
       $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#default_value' => $form_state['values']['postSecondaryCity'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 20,
        '#size' => 20,
      );
    }
    else {
       $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i ."_text"] = array(
        '#type' => 'hidden',
        '#value' => $form_state['values']['postSecondaryCity'. $i ."_text"],
      );
    }

    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i] = array(
      '#type' => 'select',
      '#title' => t('Institution Name'),
      '#default_value' => $form_state['values']['postSecondaryName'. $i],
      '#options' => _application_query_to_form_array("select distinct inst_cod, inst_txt from institut where inst_city = '". $form_state['values']['postSecondaryCity'. $i] ."' and insttypcod in ('3', '4', '5', '6', '7', '8', '9') order by inst_txt asc", TRUE, array('-1' => 'Not Listed')),
      '#required' => TRUE,
      '#ahah' => array(
        'path' => ahah_helper_path(array('Postsecondary Educational Experience', 'Institution '. $i)),
         'wrapper' => 'Institutions-information-wrapper'. $i .'-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
    );
    $form['Postsecondary Educational Experience']['Institution '. $i]['update_postSecondaryName'. $i] = array(
      '#type' => 'submit',
      '#value' => t('Institution Name'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
    if (isset($form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i ."_text"])) {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i ."_text"] = array(
        '#type' => 'hidden',
        '#value' => $form_state['values']['postSecondaryName'. $i ."_text"],
      );
    }
    if ($form_state['values']['postSecondaryCity'. $i] == "" || $form_state['values']['postSecondaryCity'. $i] == "-1" || $form_state['values']['postSecondaryName'. $i] == "-1" || $form_state['values']['postSecondaryState'. $i] == "" || $form_state['values']['postSecondaryCountry'. $i] != "UNITED STATES") {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('Institution Name'),
        '#default_value' => $form_state['values']['postSecondaryName'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 50,
        '#size' => 50,
      );
    }
    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryMajor'. $i] = array(
      '#type' => 'textfield',
      '#title' => t('Major'),
      '#default_value' => $form_state['values']['postSecondaryMajor'. $i],
      '#required' => TRUE,
      '#maxlength' => 32,
      '#size' => 32,      
      );
    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryStartYear'. $i] = array(
      '#type' => 'select',
      '#title' => t('First Year Attended'),
      '#default_value' => $form_state['values']['postSecondaryStartYear'. $i], 
      '#required' => TRUE,
      '#options' => $years,
      );
    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryEndYear'. $i] = array(
      '#type' => 'select',
      '#title' => t('Year Last Attended'),
      '#default_value' => $form_state['values']['postSecondaryEndYear'. $i], 
      '#required' => TRUE,
      '#options' => $years,
      );
    $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryDegeree'. $i] = array(
      '#type' => 'select',
      '#title' => t('Year Degree or Certificate Earned'),
      '#default_value' => $form_state['values']['postSecondaryDegeree'. $i], 
      '#required' => TRUE,
      '#options' => $result,
    );

  }
}
  $form['Submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Continue'),
  );

return ($form);

}

function application_form_page2_submit($form, &$form_state) {
  global $user;
  date_default_timezone_set('UTC');
  if ($form_state['values']['attendhighschool'] == '1') {
    //$GED_date =  date("Y-m-d H:i:s", date_format(date_create('1975-12-30 00:00:00'), DATE_ATOM));
    $GED_date = '1899-12-30 00:00:00';

  }
  else {
    //$GED_date = date("Y-m-d H:i:s", mktime(0, 0, 0, $form_state['values']['geddate']['month'], $form_state['values']['geddate']['day'], $form_state['values']['geddate']['year']));
    $GED_date = $form_state['values']['geddate']['year'] .'-'. $form_state['values']['geddate']['month'] .'-'. $form_state['values']['geddate']['day'] .' 00:00:00';
  }

  if ($form_state['values']['highschoolname'] != '-1') {
  // Need ID and name for insert into database
    $hsname = $form['High School Experience']['highschoolname']['#options'][$form_state['values']['highschoolname']];
  }
  else {
  // Get text version
    $hsname = $form_state['values']['highschoolname_text'];
  }
//   print_r($form_state);

  //null values are interperted to 0 by the db_query sql injection fixing this makes it difficult to leave GED date NULL an arbitrary date (12/30/1899) was chosen by the developer to represent lack of GED NULL values
  $biographic_sql = "UPDATE {application_Biographic} SET HighSchool_Name = '%s', HighSchool_Country = '%s', HighSchool_State = '%s', HighSchool_City = '%s', HighSchool_Attendance = '%d', HighSchool_Sonis_ID = '%s', GED_Testing_Site = '%s', GED_Date_Of_Issue = '%s' WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, $hsname, $form_state['values']['highschoolcountry'], $form_state['values']['highschoolstate'], ($form_state['values']['highschoolcity'] == "-1"?$form_state['values']['highschoolcity_text']:$form_state['values']['highschoolcity']),   $form_state['values']['attendhighschool'], $form_state['values']['highschoolname'], $form_state['values']['gedtesting'], $GED_date, $user->uid);
  
  if ( $form_state['values']['attendpostsecondary'] != 'None') {
    for ($i = 1; $i <= $form_state['values']['attendpostsecondary']; $i++) {
        // Get IDs and Names for colleges to
        if ($form_state['values']['postSecondaryName'. $i] != '-1') {
        // Need ID and name for insert into database
          $psname = $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i]['#options'][$form_state['values']['postSecondaryName'. $i]];
        }
        else {
        // Get text version
          $psname = $form_state['values']['postSecondaryName'. $i ."_text"];
        }
      
      // get the boolean and set for the completion
       if ($form_state['values']['postSecondaryDegeree'. $i] == 'Did Not Complete Degree') {
         $degreecomplete = 0;
         $form_state['values']['postSecondaryDegeree'. $i] = 0;
       }
       else {
         $degreecomplete = 1;
       }
      $institutions_sql = "INSERT into {application_Institutions} (Student_StudentID, Institution_Name, Institution_Country, Institution_City, Institution_State, First_Year_Attended, Last_Year_Attended, Degree_Certificate_Complete, Year_Degree_Completed, Major, Sonis_Institution_ID)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s' )";
      db_query($institutions_sql, $user->uid, $psname, $form_state['values']['postSecondaryCountry'. $i], ($form_state['values']['postSecondaryCity'. $i] == "-1"?$form_state['values']['postSecondaryCity'. $i ."_text"]:$form_state['values']['postSecondaryCity'. $i]), $form_state['values']['postSecondaryState'. $i], $form_state['values']['postSecondaryStartYear'. $i], $form_state['values']['postSecondaryEndYear'. $i], $degreecomplete, $form_state['values']['postSecondaryDegeree'. $i], $form_state['values']['postSecondaryMajor'. $i], $form_state['values']['postSecondaryName'. $i]);
    }
  }
   
drupal_set_message(t('Thank you for your schooling information.'));
drupal_goto('application/generalcollegeapplication3');
}
