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

  _application_form_page2_load_defaults($form_state);
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
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['High School Experience']['attendhighschool'] = array(
    '#type' => 'select',
    '#title' => t('Did you graduate from High School?'),
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
  $tmp = _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['highschoolstate'] ."' and insttypcod in ('1', '2') order by inst_city asc", TRUE, array('-1' => 'Not Listed'));
  if ($form_state['values']['highschoolstate'] != "" && $form_state['values']['highschoolcountry'] == "UNITED STATES" && count($tmp) > 2) {
    $form['High School Experience']['highschoolcity'] = array(
      '#type' => 'select',
      '#title' => t('High School City'),
      '#default_value' => $form_state['values']['highschoolcity'],
      '#options' => $tmp,
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
    $form['High School Experience']['highschoolcity_text'] = array(
      '#type' => 'hidden',
      '#value' => $form_state['values']['highschoolcity_text'],
    );
  }
  //highschoolcity_text will get overwritten when highschoolcity == "-1".  That's Ok.
  if ($form_state['values']['highschoolstate'] == "" || $form_state['values']['highschoolcountry'] != "UNITED STATES" || $form_state['values']['highschoolcity'] == "-1" || count ($tmp) <= 2) {
     $form['High School Experience']['highschoolcity_text'] = array(
      '#type' => 'textfield',
      '#title' => t('High School City'),
      '#default_value' => $form_state['values']['highschoolcity_text'],
      '#required' => TRUE,
      '#maxlength' => 20,
      '#size' => 20,
    );
    if ($form_state['values']['highschoolcity'] != "-1" || count ($tmp) <= 2) {
      $form['High School Experience']['highschoolcity'] = array(
        '#type' => 'hidden',
        '#value' => "-1",
      );
    }
  }

  if ($form_state['values']['highschoolcity'] == "" || $form_state['values']['highschoolcity'] == "-1" ||
      $form_state['values']['highschoolstate'] == "" || $form_state['values']['highschoolstate'] == "-1" ||
      $form_state['values']['highschoolcountry'] != "UNITED STATES") {
    $tmp = array();
  }
  else {
    $tmp = _application_query_to_form_array("select distinct inst_cod, inst_txt from institut where inst_state = '". $form_state['values']['highschoolstate'] ."' and inst_city = '". $form_state['values']['highschoolcity'] ."' and insttypcod in ('1', '2') order by inst_txt asc", TRUE, array('-1' => 'Not Listed'));
  }
  if (count($tmp) > 2) {
    $form['High School Experience']['highschoolname'] = array(
      '#type' => 'select',
      '#title' => t('Name of last High School attended'),
      '#default_value' => $form_state['values']['highschoolname'],
      '#options' => $tmp,
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
    $form['High School Experience']['highschoolname_text'] = array(
      '#type' => 'hidden',
      '#value' => $form_state['values']['highschoolname_text'],
    );
  }
  //highschoolname_text will get overwritten when highschoolname == "-1".  That's Ok.
  if ($form_state['values']['highschoolname'] == "-1" || count ($tmp) <= 2) {
    $form['High School Experience']['highschoolname_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Name of last High School attended'),
      '#default_value' => $form_state['values']['highschoolname_text'],
      '#required' => TRUE,
      '#maxlength' => 50,
      '#size' => 50,
    );
    if (count ($tmp) <= 2) {
      $form['High School Experience']['highschoolname'] = array(
        '#type' => 'hidden',
        '#value' => "-1",
      );
    }
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
    '#collapsible' => FALSE,
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
      '#collapsible' => FALSE,
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
    $tmp = _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['postSecondaryState'. $i] ."' and insttypcod in ('3', '4', '5', '6', '7', '8', '9') order by inst_city asc", TRUE, array('-1' => 'Not Listed'));
    if ($form_state['values']['postSecondaryState'. $i] != "" && $form_state['values']['postSecondaryCountry'. $i] == "UNITED STATES" && count($tmp) > 2) {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i] = array(
        '#type' => 'select',
        '#title' => t('City'),
        '#default_value' => $form_state['values']['postSecondaryCity'. $i],
        '#required' => TRUE,
        '#options' => $tmp,
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
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i ."_text"] = array(
        '#type' => 'hidden',
        '#value' => $form_state['values']['postSecondaryCity'. $i ."_text"],
      );
    }
    //postSecondaryCity#_text will get overwritten when postSecondaryCity# == "-1".  That's Ok.
    if ($form_state['values']['postSecondaryState'. $i] == "" || $form_state['values']['postSecondaryCountry'. $i] != "UNITED STATES" || $form_state['values']['postSecondaryCity'. $i] == "-1" || count ($tmp) <= 2) {
       $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#default_value' => $form_state['values']['postSecondaryCity'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 20,
        '#size' => 20,
      );
      if ($form_state['values']['postSecondaryCity'. $i] != "-1" || count ($tmp) <= 2) {
        $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i] = array(
          '#type' => 'hidden',
          '#value' => "-1",
        );
      }
    }

    if ($form_state['values']['postSecondaryCity'. $i] == "" || $form_state['values']['postSecondaryCity'. $i] == "-1" ||
        $form_state['values']['postSecondaryState'. $i] == "" || $form_state['values']['postSecondaryState'. $i] == "-1" ||
        $form_state['values']['postSecondaryCountry'. $i] != "UNITED STATES") {
      $tmp = array();
    }
    else {
      $tmp = _application_query_to_form_array("select distinct inst_cod, inst_txt from institut where inst_state = '". $form_state['values']['postSecondaryState'. $i] ."' and inst_city = '". $form_state['values']['postSecondaryCity'. $i] ."' and insttypcod in ('3', '4', '5', '6', '7', '8', '9') order by inst_txt asc", TRUE, array('-1' => 'Not Listed'));
    }
    if (count($tmp) > 2) {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i] = array(
        '#type' => 'select',
        '#title' => t('Institution Name'),
        '#default_value' => $form_state['values']['postSecondaryName'. $i],
        '#options' => $tmp,
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
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i ."_text"] = array(
        '#type' => 'hidden',
        '#value' => $form_state['values']['postSecondaryName'. $i ."_text"],
      );
    }
    //postSecondaryName#_text will get overwritten when postSecondaryName# == "-1".  That's Ok.
    if ($form_state['values']['postSecondaryName'. $i] == "-1" || count($tmp) <= 2) {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('Institution Name'),
        '#default_value' => $form_state['values']['postSecondaryName'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 50,
        '#size' => 50,
      );
      if (count ($tmp) <= 2) {
        $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryName'. $i] = array(
          '#type' => 'hidden',
          '#value' => "-1",
        );
      }
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


$form['Certificates'] = array(
  '#type' => 'fieldset',
  '#title' => t('Certificates Awards and Licenses'),
  '#description' => "",
  '#prefix' => '<div id="Certificates-information-wrapper">', // This is our wrapper div.
  '#suffix' => '</div>',
  '#collapsible' => FALSE,
  '#collapsed' => FALSE,
);

$form['Certificates']['Certificates_Number'] = array(
    '#type' => 'select',
    '#title' => t('How many awards certificates or licenses do you have?'),
    '#default_value' => $form_state['values']['Certificates_Number'], 
    '#required' => TRUE,
  '#ahah' => array(
    'path' => ahah_helper_path(array('Certificates')),
    'wrapper' => 'Certificates-information-wrapper',
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
$form['Certificates']['update_Certificates_Number'] = array(
  '#type' => 'submit',
  '#value' => t('Certificates_Number'),
  '#submit' => array('ahah_helper_generic_submit'),
  '#attributes' => array('class' => 'no-js'),
);



if($form_state['values']['Certificates_Number'] != "None") {
  for ($i = 1; $i <= $form_state['values']['Certificates_Number']; $i++) {
    $form['Certificates']['Certificate '. $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Institution '. $i),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#prefix' => '<div id="Certificate-information-wrapper'. $i .'-information-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#field_suffix' => t('Certificates, awards and licenses may be necessary to submit to enter some programs.')
    );
    $form['Certificates']['Certificate '. $i]['Certificate_text'. $i] = array(
      '#type' => 'textfield',
      '#title' => t('Certificate Award or License'),
      '#default_value' => $form_state['values']['Certificate_text'. $i],
      '#required' => TRUE,
      '#maxlength' => 32,
      '#size' => 32,      
      );
    $form['Certificates']['Certificate '. $i]['Validity_date'. $i] = array(
      '#type' => 'select',
      '#title' => t('Validity Date'),
      '#default_value' => $form_state['values']['Validity_date'. $i], 
      '#required' => TRUE,
      '#options' => $years,
      );
    $form['Certificates']['Certificate '. $i]['Expiration_date'. $i] = array(
      '#type' => 'select',
      '#title' => t('Expiration Date'),
      '#default_value' => $form_state['values']['Expiration_date'. $i], 
      '#required' => TRUE,
      '#options' => $years,
      );
    $form['Certificates']['Certificate '. $i]['Memo'. $i] = array(
      '#type' => 'select',
      '#title' => t('Additional information'),
      '#default_value' => $form_state['values']['Memo'. $i], 
      '#required' => False,
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

function application_form_page2_validate($form, &$form_state) {
  $ged_error_message = "The GED Date of Issue you selected is invalid.";
  if (intval($form_state['values']['geddate']['year']) > intval(date("Y"))) {
    form_set_error('geddate', t($ged_error_message));
  }
  else if (intval($form_state['values']['geddate']['year']) == intval(date("Y"))) {
    if (intval($form_state['values']['geddate']['month']) > intval(date("m"))) {
      form_set_error('geddate', t($ged_error_message));
    }
    else if (intval($form_state['values']['geddate']['month']) == intval(date("m")) &&
             intval($form_state['values']['geddate']['day']) > intval(date("d"))) {
      form_set_error('geddate', t($ged_error_message));
    }
  }
  for ($i = 1; $i <= $form_state['values']['attendpostsecondary']; $i++) {
    if (intval($form_state['values']['postSecondaryStartYear'. $i]) > intval($form_state['values']['postSecondaryEndYear'. $i])) {
      form_set_error('postSecondaryStartYear'. $i, t("Please ensure that your First Year Attended Occurs Before your Last Year Attended."));
    }
    if (is_numeric($form_state['values']['postSecondaryDegeree'. $i]) && intval($form_state['values']['postSecondaryStartYear'. $i]) > intval($form_state['values']['postSecondaryDegeree'. $i])) {
      form_set_error('postSecondaryDegeree'. $i, t("Please ensure that your Year of Completion Occurs Before your First Year Attended."));
    }
  }
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
  if ($form_state['values']['highschoolcity'] == "" || $form_state['values']['highschoolcity'] == "-1") {
    $hscity = $form_state['values']['highschoolcity_text'];
  }
  else {
    $hscity = $form_state['values']['highschoolcity'];
  }
//   print_r($form_state);

  //null values are interperted to 0 by the db_query sql injection fixing this makes it difficult to leave GED date NULL an arbitrary date (12/30/1899) was chosen by the developer to represent lack of GED NULL values
  $biographic_sql = "UPDATE {application_Biographic} SET HighSchool_Name = '%s', HighSchool_Country = '%s', HighSchool_State = '%s', HighSchool_City = '%s', HighSchool_Attendance = '%d', HighSchool_Sonis_ID = '%s', GED_Testing_Site = '%s', GED_Date_Of_Issue = '%s' WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, $hsname, $form_state['values']['highschoolcountry'], $form_state['values']['highschoolstate'], $hscity, $form_state['values']['attendhighschool'], $form_state['values']['highschoolname'], $form_state['values']['gedtesting'], $GED_date, $user->uid);
  
  //Assume it's an update.  (Does noting if it's not.)
  $institutions_sql = "DELETE FROM {application_Institutions} WHERE Student_StudentID = '%s'";
  db_query($institutions_sql, $user->uid);

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
       if ($form_state['values']['postSecondaryCity'. $i] == "" ||$form_state['values']['postSecondaryCity'. $i] == "-1") {
          $pscity = $form_state['values']['postSecondaryCity'. $i ."_text"];
        }
        else {
          $pscity = $form_state['values']['postSecondaryCity'. $i];
        }
       
       
       
       
      $institutions_sql = "INSERT into {application_Institutions} (Student_StudentID, Institution_Name, Institution_Country, Institution_City, Institution_State, First_Year_Attended, Last_Year_Attended, Degree_Certificate_Complete, Year_Degree_Completed, Major, Sonis_Institution_ID)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s' )";
      db_query($institutions_sql, $user->uid, $psname, $form_state['values']['postSecondaryCountry'. $i], $pscity, $form_state['values']['postSecondaryState'. $i], $form_state['values']['postSecondaryStartYear'. $i], $form_state['values']['postSecondaryEndYear'. $i], $degreecomplete, $form_state['values']['postSecondaryDegeree'. $i], $form_state['values']['postSecondaryMajor'. $i], $form_state['values']['postSecondaryName'. $i]);
    }
  }
   
drupal_set_message(t('Thank you for your schooling information.'));
drupal_goto('application/generalcollegeapplication3');
}

function _application_form_page2_load_defaults(&$form_state) {
  global $user;

  $biographic_sql = "SELECT HighSchool_Name, HighSchool_Country, HighSchool_State, HighSchool_City, HighSchool_Attendance, HighSchool_Sonis_ID, GED_Testing_Site, GED_Date_Of_Issue FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));

  if ($a) {
    if (!isset($form_state['values']['highschoolcountry']))
      $form_state['values']['highschoolcountry'] = $a['HighSchool_Country'];
    if (!isset($form_state['values']['highschoolstate']))
      $form_state['values']['highschoolstate'] = $a['HighSchool_State'];

    if (!isset($form_state['values']['highschoolcity']) && !isset($form_state['values']['highschoolcity_text'])) {
      if (array_key_exists($a['HighSchool_City'], _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['highschoolstate'] ."' and insttypcod in ('1', '2') order by inst_city asc")))
        $form_state['values']['highschoolcity'] = $a['HighSchool_City'];
      else {
        $form_state['values']['highschoolcity_text'] = $a['HighSchool_City'];
        $form_state['values']['highschoolcity'] = -1;
      }
    }

    if (!isset($form_state['values']['highschoolname']))
      $form_state['values']['highschoolname'] = $a['HighSchool_Sonis_ID'];
    if (!isset($form_state['values']['highschoolname_text']) && $form_state['values']['highschoolname'] == "-1")
      $form_state['values']['highschoolname_text'] = $a['HighSchool_Name'];

    if (!isset($form_state['values']['attendhighschool']))
      $form_state['values']['attendhighschool'] = $a['HighSchool_Attendance'];
    if (!isset($form_state['values']['gedtesting']))
      $form_state['values']['gedtesting'] = $a['GED_Testing_Site'];

    if (!isset($form_state['values']['geddate'])) {
      $GED_date = $a['GED_Date_Of_Issue'];
      $GED_date = split("-", $GED_date);
      $form_state['values']['geddate']['year'] = $GED_date[0];
      $form_state['values']['geddate']['month'] = $GED_date[1];
      $GED_date = split(" ", $GED_date[2]);
      $form_state['values']['geddate']['day'] = $GED_date[0];
    }

    $institutions_sql = "SELECT Institution_Name, Institution_Country, Institution_City, Institution_State, First_Year_Attended, Last_Year_Attended, Degree_Certificate_Complete, Year_Degree_Completed, Major, Sonis_Institution_ID FROM {application_Institutions} WHERE Student_StudentID = '%s'";
    $result = db_query($institutions_sql, $user->uid);
    $i = 0;

    while ($a = db_fetch_array($result)) {
      $i++;
      if (!isset($form_state['values']['postSecondaryCountry'. $i]))
        $form_state['values']['postSecondaryCountry'. $i] = $a['Institution_Country'];
      if (!isset($form_state['values']['postSecondaryState'. $i]))
        $form_state['values']['postSecondaryState'. $i] = $a['Institution_State'];

      if (!isset($form_state['values']['postSecondaryCity'. $i]) && !isset($form_state['values']['postSecondaryCity'. $i ."_text"])) {
        if (array_key_exists($a['Institution_City'], _application_query_to_form_array("select distinct inst_city, inst_city from institut where inst_state = '". $form_state['values']['postSecondaryState'. $i] ."' and insttypcod in ('3', '4', '5', '6', '7', '8', '9') order by inst_city asc", TRUE, array('-1' => 'Not Listed'))))
          $form_state['values']['postSecondaryCity'. $i] = $a['Institution_City'];
        else {
          $form_state['values']['postSecondaryCity'. $i ."_text"] = $a['Institution_City'];
          $form_state['values']['postSecondaryCity'. $i] = -1;
        }
      }

      if (!isset($form_state['values']['postSecondaryName'. $i]) && !isset($form_state['values']['postSecondaryName'. $i ."_text"])) {
        $form_state['values']['postSecondaryName'. $i] = $a['Sonis_Institution_ID'];
        if ($form_state['values']['postSecondaryName'. $i] == '-1') {
          $form_state['values']['postSecondaryName'. $i ."_text"] = $a['Institution_Name'];
        }
      }

      if (!isset($form_state['values']['postSecondaryMajor'. $i]))
        $form_state['values']['postSecondaryMajor'. $i] = $a['Major'];
      if (!isset($form_state['values']['postSecondaryStartYear'. $i]))
        $form_state['values']['postSecondaryStartYear'. $i] = $a['First_Year_Attended'];
      if (!isset($form_state['values']['postSecondaryEndYear'. $i]))
        $form_state['values']['postSecondaryEndYear'. $i] = $a['Last_Year_Attended'];

      if (!isset($form_state['values']['Degree_Certificate_Complete'. $i])) {
        $form_state['values']['postSecondaryDegeree'. $i] = $a['Year_Degree_Completed'];
        if ($form_state['values']['postSecondaryDegeree'. $i] == 0)
          $form_state['values']['postSecondaryDegeree'. $i] = 'Did Not Complete Degree';
      }
    }
    if (!isset($form_state['values']['attendpostsecondary'])) {
      if ($i == 0)
        $form_state['values']['attendpostsecondary'] = 'None';
      else
        $form_state['values']['attendpostsecondary'] = $i;
    }
  }
}
