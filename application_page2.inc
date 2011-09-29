<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 2.
 * 
 */

function application_form_page2($form_state) {
  $form = array();

  _application_form_page2_load_defaults($form_state);
  ahah_helper_register($form, $form_state);
  
  $states = sonisweb_integration_dropbox_to_form_api_options_array(
              sonisweb_integration_api("CFC.drp_box", "state", "no", array(array('sonis_ds', '#sonis.ds#'),
                                       array('allow_blank', "yes"),
                                       array('hide', "no"),
                                       array('multi_select', "no"),
                                       array('Additional_Properties', ""),
                                       array('hide_excludes', 'yes'))));
  $countries = sonisweb_integration_dropbox_to_form_api_options_array(
              sonisweb_integration_api("CFC.drp_box", "country", "no", array(array('sonis_ds', '#sonis.ds#'),
                                       array('allow_blank', "yes"),
                                       array('hide', "no"),
                                       array('multi_select', "no"),
                                       array('Additional_Properties', ""),
                                       array('hide_excludes', 'yes'))));
  $years = array_combine(range(date("Y"), (date("Y")-100), -1), range(date("Y"), (date("Y")-100), -1));
  $nograd = array("Did Not Complete Degree" => "Did Not Complete Degree");
  //$result = array_merge($nograd, $years);
  $result = $nograd + $years;
  if ($form_state['values']['attendhighschool'] != "0") {
    $form_state['values']['attendhighschool'] = "1";
  }
  
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
  '#title' => t('Do you have or will you obtain a 4-year diploma?'),
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

  if ($form_state['values']['highschoolcountry'] == "" || strcasecmp($form_state['values']['highschoolcountry'], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "American Samoa") == 0 || strcasecmp($form_state['values']['highschoolcountry'], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "Guam") == 0 || strcasecmp($form_state['values']['highschoolcountry'], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "Puerto Rico") == 0) {
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
  $tmp = array_merge(sonisweb_integration_sql_to_options(
                     sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                              array('inst_txt', ""),
                                              array('insttypcod', "1"),
                                              array('inst_city', ""),
                                              array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ")))), 'inst_city', 'inst_city'),
                     sonisweb_integration_sql_to_options(
                     sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                              array('inst_txt', ""),
                                              array('insttypcod', "2"),
                                              array('inst_city', ""),
                                              array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ")))), 'inst_city', 'inst_city')
            );
  unset($tmp['']);
  ksort($tmp);
  $tmp['0'] = 'Not Listed';
  $tmp = array_merge(array('' => ''), $tmp);
  if ($form_state['values']['highschoolstate'] != "" && (strcasecmp($form_state['values']['highschoolcountry'], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "American Samoa") == 0 || strcasecmp($form_state['values']['highschoolcountry'], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "Guam") == 0 || strcasecmp($form_state['values']['highschoolcountry'], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['highschoolcountry'], "Puerto Rico") == 0) && count($tmp) > 2) {
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
  //highschoolcity_text will get overwritten when highschoolcity == "0".  That's Ok.
  if ($form_state['values']['highschoolstate'] == "" || (strcasecmp($form_state['values']['highschoolcountry'], "UNITED STATES") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "American Samoa") != 0 && strcasecmp($form_state['values']['highschoolcountry'], "Federated States of Micronesia") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "Guam") != 0 && strcasecmp($form_state['values']['highschoolcountry'], "U.S. Minor Outlying Is") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "Puerto Rico") != 0) || $form_state['values']['highschoolcity'] == "0" || count($tmp) <= 2) {
     $form['High School Experience']['highschoolcity_text'] = array(
      '#type' => 'textfield',
      '#title' => t('High School City'),
      '#default_value' => $form_state['values']['highschoolcity_text'],
      '#required' => TRUE,
      '#maxlength' => 20,
      '#size' => 20,
    );
    if ($form_state['values']['highschoolcity'] != "0" || count ($tmp) <= 2) {
      $form['High School Experience']['highschoolcity'] = array(
        '#type' => 'hidden',
        '#value' => "0",
      );
    }
  }

  if ($form_state['values']['highschoolcity'] == "" || $form_state['values']['highschoolcity'] == "0" ||
      $form_state['values']['highschoolstate'] == "" || $form_state['values']['highschoolstate'] == "0" ||
      (strcasecmp($form_state['values']['highschoolcountry'], "UNITED STATES") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "American Samoa") != 0 && strcasecmp($form_state['values']['highschoolcountry'], "Federated States of Micronesia") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "Guam") != 0 && strcasecmp($form_state['values']['highschoolcountry'], "U.S. Minor Outlying Is") != 0
      && strcasecmp($form_state['values']['highschoolcountry'], "Puerto Rico") != 0)) {
    $tmp = array();
  }
  else {
    $tmp = array_merge(sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "1"),
                                                array('inst_city', ($form_state['values']['highschoolcity']?$form_state['values']['highschoolcity']:""),
                                                array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ"))))), 'INST_COD', 'INST_TXT'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "2"),
                                                array('inst_city', ($form_state['values']['highschoolcity']?$form_state['values']['highschoolcity']:""),
                                                array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ"))))), 'INST_COD', 'INST_TXT')
              );
    unset($tmp['']);
    asort($tmp);
    $tmp['0'] = 'Not Listed';
    $tmp = array_merge(array('' => ''), $tmp);
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
  //highschoolname_text will get overwritten when highschoolname == "0".  That's Ok.
  if ($form_state['values']['highschoolname'] == "0" || count ($tmp) <= 2) {
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
        '#value' => "0",
      );
    }
  }
   $form['High School Experience']['graduationyear'] = array(
     '#type' => 'select',
     '#title' => t('Year of Graduation'),
     '#default_value' => $form_state['values']['graduationyear'],
     '#required' => TRUE,
     '#options' => array_combine(range((date("Y") + 4), (date("Y")-100), -1), range((date("Y") + 4), (date("Y")-100), -1)),
   );
}
if($form_state['values']['attendhighschool'] == "0") {
  // School Type
  $form['High School Experience']['highschooltype'] = array(
    '#type' => 'select',
    '#title' => t('Please select your 4-year diploma equivalent'),
    '#default_value' => $form_state['values']['highschooltype'],
    '#options' => array('' => '',
                        'GED' => 'General Educational Development (GED) Certificate',
                        'Homeschool' => 'Homeschool',
                        'None' => 'None of the above',),
    '#required' => TRUE,
    '#ahah' => array(
      'path' => ahah_helper_path(array('High School Experience')),
       'wrapper' => 'High-School-Experience-information-wrapper',
      'method' => 'replace',
      'event' => 'change',
      'effect' => 'fade',
    ),
  );
   $form['High School Experience']['update_highschooltype'] = array(
    '#type' => 'submit',
    '#value' => t('High School Experience Type'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );

  if ($form_state['values']['highschooltype'] != "" && $form_state['values']['highschooltype'] != "None") {
    // GED
    $form['High School Experience']['gedtesting'] = array(
      '#type' => 'textfield',
      '#title' => t(($form_state['values']['highschooltype'] == "GED"?'GED Testing Site':'Homeschool State')),
      '#default_value' => $form_state['values']['gedtesting'],
      '#required' => TRUE,
      '#maxlength' => 50,
      '#size' => 50,
    );
    $form['High School Experience']['geddate'] = array(
      '#type' => 'date_popup',
      '#title' => t(($form_state['values']['highschooltype'] == "GED"?'Date of Issue':'Date of Graduation')),
      '#default_value' => $form_state['values']['geddate'],
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '-100:4',
      '#required' => TRUE,
     );
   }
}

// Postsecondary Educational Experience
$form['Postsecondary Educational Experience'] = array(
    '#type' => 'fieldset',
    '#title' => t('Postsecondary Educational Experience'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  '#prefix' => '<div id="Postsecondary-Educational-Experience-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
  '#field_suffix' => t('You must submit official transcripts from all of your previous educational institutions. Transcripts must be received by FHCHS directly from the issuing institution. Faxes are not considered official. Transcript request forms are provided after completing this application.')
  ); // why doesn't this work?
  
$form['Postsecondary Educational Experience']['attendedfhchs'] = array(
	'#type' => 'select',
	'#title' => t('Have you attended or been accepted to FHCHS?'),
	'#default_value' => isset($form_state['values']['attendedfhchs']) ? $form_state['values']['attendedfhchs']:'never_attended', 
	'#required' => TRUE,
	'#ahah' => array(
		'path' => ahah_helper_path(array('Postsecondary Educational Experience')),
		'wrapper' => 'Postsecondary-Educational-Experience-information-wrapper',
		'method' => 'replace',
		'event' => 'change',
		'effect' => 'fade',
	),
	'#options' => array(
		'attended' => 'Attended',
		'accepted_not_attended' => 'Accepted, not attended',
		'never_attended' => 'No Previous FHCHS Experience'
	)
);
// "attendedfhchs" selection
if( $form_state['values']['attendedfhchs'] == "attended") {
    $form['Postsecondary Educational Experience']['lastattended'] = array(
      '#type' => 'textfield',
      '#title' => t('Last trimester of attendance?'),
      '#default_value' => $form_state['values']['lastattended'], 
      '#required' => TRUE,
     );
		$form['Postsecondary Educational Experience']['lastattended_grant_permission'] = array(
			'#type' => 'checkbox',
			'#title' => t('Grant programs permission to access my FHCHS transcript'), 
			'#required' => TRUE,
			'#default_value' => TRUE
		);
}
// "accepted_not_attended" selection
if( $form_state['values']['attendedfhchs'] == "accepted_not_attended") {
    $form['Postsecondary Educational Experience']['lastattended'] = array(
      '#type' => 'textfield',
      '#title' => t('Acceptance Date'),
      '#default_value' => $form_state['values']['lastattended'], 
      '#required' => TRUE,
     );
}

$form['Postsecondary Educational Experience']['attendpostsecondary'] = array(
    '#type' => 'select',
    '#title' => t('How many colleges, universities or other postsecondary institutions have you attended?'),
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

    if ($form_state['values']['postSecondaryCountry'. $i] == "" || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "American Samoa") == 0 || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Guam") == 0 || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Puerto Rico") == 0) {
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
    $tmp = array_merge(sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "3"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "4"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "5"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "6"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "7"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "8"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                       sonisweb_integration_sql_to_options(
                       sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                array('inst_txt', ""),
                                                array('insttypcod', "9"),
                                                array('inst_city', ""),
                                                array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city')
              );
    unset($tmp['']);
    ksort($tmp);
    $tmp['0'] = 'Not Listed';
    $tmp = array_merge(array('' => ''), $tmp);
    if ($form_state['values']['postSecondaryState'. $i] != "" && (strcasecmp($form_state['values']['postSecondaryCountry'. $i], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "American Samoa") == 0 || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Guam") == 0 || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Puerto Rico") == 0) && count($tmp) > 2) {
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
    //postSecondaryCity#_text will get overwritten when postSecondaryCity# == "0".  That's Ok.
    if ($form_state['values']['postSecondaryState'. $i] == "" || (strcasecmp($form_state['values']['postSecondaryCountry'. $i], "UNITED STATES") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "American Samoa") != 0 && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Federated States of Micronesia") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Guam") != 0 && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "U.S. Minor Outlying Is") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Puerto Rico") != 0) || $form_state['values']['postSecondaryCity'. $i] == "0" || count($tmp) <= 2) {
       $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#default_value' => $form_state['values']['postSecondaryCity'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 20,
        '#size' => 20,
      );
      if ($form_state['values']['postSecondaryCity'. $i] != "0" || count ($tmp) <= 2) {
        $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryCity'. $i] = array(
          '#type' => 'hidden',
          '#value' => "0",
        );
      }
    }

    if ($form_state['values']['postSecondaryCity'. $i] == "" || $form_state['values']['postSecondaryCity'. $i] == "0" ||
        $form_state['values']['postSecondaryState'. $i] == "" || $form_state['values']['postSecondaryState'. $i] == "0" ||
        (strcasecmp($form_state['values']['postSecondaryCountry'. $i], "UNITED STATES") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "American Samoa") != 0 && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Federated States of Micronesia") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Guam") != 0 && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "U.S. Minor Outlying Is") != 0
      && strcasecmp($form_state['values']['postSecondaryCountry'. $i], "Puerto Rico") != 0)) {
      $tmp = array();
    }
    else {
      $tmp = array_merge(sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "3"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "4"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "5"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "6"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "7"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "8"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "9"),
                                                  array('inst_city', $form_state['values']['postSecondaryCity'. $i]),
                                                  array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_cod', 'inst_txt')
                );
      unset($tmp['']);
      asort($tmp);
      $tmp['0'] = 'Not Listed';
      $tmp = array_merge(array('' => ''), $tmp);
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
    //postSecondaryName#_text will get overwritten when postSecondaryName# == "0".  That's Ok.
    if ($form_state['values']['postSecondaryName'. $i] == "0" || count($tmp) <= 2) {
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
          '#value' => "0",
        );
      }
    }
    //postSecondaryDegree#_text will get overwritten when postSecondaryDegree# == "0".  That's Ok.
    $tmp = sonisweb_integration_dropbox_to_form_api_options_array(
                       sonisweb_integration_api("CFC.drp_box", "degree", "no", array(array('sonis_ds', '#sonis.ds#'),
                                                array('allow_blank', "No"),
                                                array('multi_select', "No"),
                                                array('hide', "No"),
                                                array('Additional_Properties', ""))));
    unset($tmp['']);
    ksort($tmp);
    $tmp['0'] = 'Not Listed';
    $tmp = array_merge(array('' => ''), $tmp);
    if (count($tmp) > 2) {
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryDegree'. $i] = array(
        '#type' => 'select',
        '#title' => t('Degree'),
        '#default_value' => $form_state['values']['postSecondaryDegree'. $i],
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
      $form['Postsecondary Educational Experience']['Institution '. $i]['update_postSecondaryDegree'. $i] = array(
        '#type' => 'submit',
        '#value' => t('Degree'),
        '#submit' => array('ahah_helper_generic_submit'),
        '#attributes' => array('class' => 'no-js'),
      );
      $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryDegree'. $i ."_text"] = array(
        '#type' => 'hidden',
        '#value' => $form_state['values']['postSecondaryDegree'. $i ."_text"],
      );
    }
    //postSecondaryDegree#_text will get overwritten when postSecondaryDegree# == "0".  That's Ok.
    if ($form_state['values']['postSecondaryDegree'. $i] == "0" || count($tmp) <= 2) {
       $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryDegree'. $i ."_text"] = array(
        '#type' => 'textfield',
        '#title' => t('Degree'),
        '#default_value' => $form_state['values']['postSecondaryDegree'. $i ."_text"],
        '#required' => TRUE,
        '#maxlength' => 35,
        '#size' => 20,
      );
      if ($form_state['values']['postSecondaryDegree'. $i] != "0") {
        $form['Postsecondary Educational Experience']['Institution '. $i]['postSecondaryDegree'. $i] = array(
          '#type' => 'hidden',
          '#value' => "0",
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

// Acknowledgement of Colleges Attended
$form['Acknowledgement of Colleges Attended'] = array(
    '#type' => 'fieldset',
    '#title' => t('Acknowledgement of Colleges Attended'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  '#prefix' => '<div id="Acknowledgement-of-Colleges-Attended-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
  '#field_suffix' => t('You must acknowledge disclosure of previous postsecondary education before continuing.')
);

$form['Acknowledgement of Colleges Attended']['acknowledgement'] = array(
  '#type' => 'checkbox',
  '#title' => t('I understand that failure to disclose all colleges previously attended could result in denial or dismissal.'), 
  '#required' => TRUE,
	'#default_value' => TRUE
);



$form['Other_Education'] = array(
  '#type' => 'fieldset',
  '#title' => t('CLEP, AP and IB Credits'),
  '#description' => "",
  '#prefix' => '<div id="Other-Schooling-information-wrapper">', // This is our wrapper div.
  '#suffix' => '</div>',
  '#collapsible' => FALSE,
  '#collapsed' => FALSE,
);
$form['Other_Education']['credits'] = array(
  '#type' => 'select',
  '#title' => t('Did you have any CLEP, AP or IB credits?'),
  '#default_value' => $form_state['values']['credits'], 
  '#required' => TRUE,
  '#ahah' => array(
    'path' => ahah_helper_path(array('Other_Education')),
    'wrapper' => 'Other-Schooling-information-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'effect' => 'fade',
    ),
  '#options' => array('1' => t('Yes'),
  '0' => t('No')),
);
$form['Other_Education']['update_credits'] = array(
  '#type' => 'submit',
  '#value' => t('credits'),
  '#submit' => array('ahah_helper_generic_submit'),
  '#attributes' => array('class' => 'no-js'),
);
if ($form_state['values']['credits'] == "1" || $form_state['values']['credits'] == "") {
  $form['Other_Education']['CLEP'] = array(
  '#type' => 'select',
  '#title' => t('Do you have any CLEP credits?'),
  '#default_value' => $form_state['values']['CLEP'], 
  '#required' => TRUE,
  '#options' => array('1' => t('Yes'),
  '0' => t('No')),
  );
  $form['Other_Education']['AP'] = array(
  '#type' => 'select',
  '#title' => t('Do you have any AP credits?'),
  '#default_value' => $form_state['values']['AP'], 
  '#required' => TRUE,
  '#options' => array('1' => t('Yes'),
  '0' => t('No')),
  );
  $form['Other_Education']['IB'] = array(
  '#type' => 'select',
  '#title' => t('Do you have any IB credits?'),
  '#default_value' => $form_state['values']['IB'], 
  '#required' => TRUE,
  '#options' => array('1' => t('Yes'),
  '0' => t('No')),
  );
}





$form['Certificates'] = array(
  '#type' => 'fieldset',
  '#title' => t('Certifications and Licenses'),
  '#description' => "",
  '#prefix' => '<div id="Certificates-information-wrapper">', // This is our wrapper div.
  '#suffix' => '</div>',
  '#collapsible' => FALSE,
  '#collapsed' => FALSE,
);

$form['Certificates']['Certificates_Number'] = array(
  '#type' => 'select',
  '#title' => t('How many certifications or licenses do you have?'),
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
    $tmp = sonisweb_integration_dropbox_to_form_api_options_array(
           sonisweb_integration_api("CFC.licenses", "licenses_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                    array('allow_blank', "No"),
                                    array('multi_select', "No"),
                                    array('hide', "No"))));
    unset($tmp['']);
    asort($tmp);
    $tmp['0'] = 'Not Listed';
    $tmp = array_merge(array('' => ''), $tmp);
  for ($i = 1; $i <= $form_state['values']['Certificates_Number']; $i++) {
    $form['Certificates']['Certificate '. $i] = array(
      '#type' => 'fieldset',
      '#title' => t('License '. $i),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#prefix' => '<div id="Certificate-information-wrapper'. $i .'-information-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#field_suffix' => t('Certificates and licenses may be necessary to submit to enter some programs.')
    );
    $form['Certificates']['Certificate '. $i]['Certificate_text'. $i] = array(
      '#type' => 'select',
      '#title' => t('Certificate Award or License'),
      '#default_value' => $form_state['values']['Certificate_text'. $i],
      '#required' => TRUE,
      '#ahah' => array(
        'path' => ahah_helper_path(array('Certificates', 'Certificate '. $i)),
         'wrapper' => 'Certificate-information-wrapper'. $i .'-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
      '#options' =>  $tmp,
    );
    $form['Certificates']['Certificate '. $i]['update_Certificate_text'. $i] = array(
      '#type' => 'submit',
      '#value' => t('Certificate Award or License'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );
    if ($form_state['values']['Certificate_text'. $i] == "0" || $form_state['values']['Certificate_text'. $i] == "OTHER" ) {
      $form['Certificates']['Certificate '. $i]['Licensetype'. $i] = array(
        '#type' => 'textfield',
        '#title' => t('License type'),
        '#default_value' => $form_state['values']['Licensetype'. $i],
        '#required' => TRUE,
        '#maxlength' => 32,
        '#size' => 32,   
      );
    }  
    $form['Certificates']['Certificate '. $i]['Effective_date'. $i] = array(
      '#type' => 'date_popup',
      '#title' => t('Effective Date'),
      '#default_value' => $form_state['values']['Effective_date'. $i], 
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '-50:+50',
      '#required' => TRUE,
    );
    $form['Certificates']['Certificate '. $i]['Expiration_date'. $i] = array(
      '#type' => 'date_popup',
      '#title' => t('Expiration Date'),
      '#default_value' => $form_state['values']['Expiration_date'. $i], 
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '-50:+50',
      '#required' => TRUE,
    );
    $form['Certificates']['Certificate '. $i]['countryissued'. $i] = array(
      '#type' => 'select',
      '#title' => t('Country Issued'),
      '#default_value' => ($form_state['values']['countryissued'. $i] == ""?"UNITED STATES":$form_state['values']['countryissued'. $i]),
      '#required' => TRUE,
      '#options' => $countries,
      '#ahah' => array(
        'path' => ahah_helper_path(array('Certificates', 'Certificate '. $i)),
         'wrapper' => 'Certificate-information-wrapper'. $i .'-information-wrapper',
        'method' => 'replace',
        'event' => 'change',
        'effect' => 'fade',
      ),
    );
    $form['Certificates']['Certificate '. $i]['update_countryissued'. $i] = array(
      '#type' => 'submit',
      '#value' => t('Country Issued'),
      '#submit' => array('ahah_helper_generic_submit'),
      '#attributes' => array('class' => 'no-js'),
    );

    if ($form_state['values']['countryissued'. $i] == "" || strcasecmp($form_state['values']['countryissued'. $i], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "American Samoa") == 0 || strcasecmp($form_state['values']['countryissued'. $i], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "Guam") == 0 || strcasecmp($form_state['values']['countryissued'. $i], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "Puerto Rico") == 0) {
      $form['Certificates']['Certificate '. $i]['stateissued'. $i] = array(
        '#type' => 'select',
        '#title' => t('State Issued'),
        '#default_value' => $form_state['values']['stateissued'. $i],
        '#required' => TRUE,
        '#options' => $states,
      );
    }
  }
  
  
  
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

function application_form_page2_validate($form, &$form_state) {
  $geddate = split("-", $form_state['values']['geddate']);
  $geddate2 = split(" ", $geddate[2]);
  $ged_error_message = "The GED Date of Issue you selected is invalid.";
  if (intval($geddate[0]) > intval(date("Y"))) {
    form_set_error('geddate', t($ged_error_message));
  }
  elseif (intval($geddate[0]) == intval(date("Y"))) {
    if (intval($geddate[1]) > intval(date("m"))) {
      form_set_error('geddate', t($ged_error_message));
    }
    elseif (intval($geddate[1]) == intval(date("m")) &&
             intval($geddate2[0]) > intval(date("d"))) {
      form_set_error('geddate', t($ged_error_message));
    }
  }
  if ($form_state['values']['CLEP'] == '0' && $form_state['values']['AP'] == '0' && $form_state['values']['IB'] == '0' && $form_state['values']['credits'] == '1') {
    form_set_error('credits', t("You have not selected one of the additional schooling infomation options."));
  }
  for ($i = 1; $i <= $form_state['values']['attendpostsecondary']; $i++) {
    if (intval($form_state['values']['postSecondaryStartYear'. $i]) > intval($form_state['values']['postSecondaryEndYear'. $i])) {
      form_set_error('postSecondaryStartYear'. $i, t("Please ensure that your First Year Attended Occurs Before your Last Year Attended."));
    }
    if (is_numeric($form_state['values']['postSecondaryDegeree'. $i]) && intval($form_state['values']['postSecondaryStartYear'. $i]) > intval($form_state['values']['postSecondaryDegeree'. $i])) {
      form_set_error('postSecondaryDegeree'. $i, t("Please ensure that your Year of Completion Occurs Before your First Year Attended."));
    }
    if (is_numeric($form_state['values']['postSecondaryDegeree'. $i]) && intval($form_state['values']['postSecondaryEndYear'. $i]) < intval($form_state['values']['postSecondaryDegeree'. $i])) {
      form_set_error('postSecondaryDegeree'. $i, t("Please ensure that your Year of Completion Does Not Occur After your Last Year Attended."));
    }
  }
  for ($i = 1; $i <= $form_state['values']['Certificates_Number']; $i++) {
    if (is_string($form_state['values']['Expiration_date'. $i])) {
      $tmp = split("-", $form_state['values']['Expiration_date'. $i]);
      $tmp2 = split("-", $form_state['values']['Effective_date'. $i]);
      if ($tmp[0] < $tmp2[0] || ($tmp[0] == $tmp2[0] && $tmp[1] < $tmp2[1]) || ($tmp[0] == $tmp2[0] && $tmp[1] == $tmp2[1] && $tmp[2] < $tmp2[2]))
        form_set_error('Expiration_date'. $i, t("Please ensure that your Certificate does not Expire before it is Effective."));
    }
  }
}

function application_form_page2_submit($form, &$form_state) {
  global $user;

  date_default_timezone_set('UTC');
  if ($form_state['values']['attendhighschool'] == '1' || $form_state['values']['geddate'] == "") {
    //$GED_date =  date("Y-m-d H:i:s", date_format(date_create('1975-12-30 00:00:00'), DATE_ATOM));
    $GED_date = '1899-12-30 00:00:00';

  }
  else {
    // $GED_date = date("Y-m-d H:i:s", mktime(0, 0, 0, $form_state['values']['geddate']['month'], $form_state['values']['geddate']['day'], $form_state['values']['geddate']['year']));
		// $GED_date = $form_state['values']['geddate']['year'] .'-'. $form_state['values']['geddate']['month'] .'-'. $form_state['values']['geddate']['day'] .' 00:00:00';
    $GED_date = $form_state['values']['geddate'];
  }

  if ($form_state['values']['highschoolname'] != '0') {
  // Need ID and name for insert into database
    $hsname = $form['High School Experience']['highschoolname']['#options'][$form_state['values']['highschoolname']];
  }
  else {
  // Get text version
    $hsname = $form_state['values']['highschoolname_text'];
  }
  if ($form_state['values']['highschoolcity'] == "" || $form_state['values']['highschoolcity'] == "0") {
    $hscity = $form_state['values']['highschoolcity_text'];
  }
  else {
    $hscity = $form_state['values']['highschoolcity'];
  }
  
  if ($form_state['values']['credits'] == "0") {

  }
  else {
    $clep = $form_state['values']['CLEP'];
    $ap = $form_state['values']['AP'];
    $ib = $form_state['values']['IB'];
  }
  
	// Replace FHCHS Previous attendance
	$attendedfhchs_sql = "DELETE FROM {application_fhchs_attendance} WHERE sid = '%s'";
	db_query($attendedfhchs_sql, $user->uid);
	$attendedfhchs_sql = "INSERT INTO {application_fhchs_attendance} (`sid`,`attendance_type`,`attendance_date`) VALUES ('%s','%s','%s')";
  db_query($attendedfhchs_sql, $user->uid, $form_state['values']['attendedfhchs'], $form_state['values']['lastattended'] );
	
  //null values are interperted to 0 by the db_query sql injection fixing this makes it difficult to leave GED date NULL an arbitrary date (12/30/1899) was chosen by the developer to represent lack of GED NULL values
  $biographic_sql = "UPDATE {application_Biographic} SET HighSchool_Name = '%s', HighSchool_Country = '%s', HighSchool_State = '%s', HighSchool_City = '%s', HighSchool_Attendance = '%d', HighSchool_Grad_Year = '%s', HighSchool_Sonis_ID = '%s', HighSchool_Equivalent_Type = '%s', GED_Testing_Site = '%s', GED_Date_Of_Issue = '%s', OtherSchooling_CLEP = '%d', OtherSchooling_AP = '%d', OtherSchooling_IB = '%d' WHERE Student_StudentID = '%s'";
  db_query($biographic_sql, $hsname, $form_state['values']['highschoolcountry'], $form_state['values']['highschoolstate'], $hscity, $form_state['values']['attendhighschool'], $form_state['values']['graduationyear'], $form_state['values']['highschoolname'], $form_state['values']['highschooltype'], $form_state['values']['gedtesting'], $GED_date, $clep, $ap, $ib, $user->uid);
  
  //Assume it's an update.  (Does noting if it's not.)
  $institutions_sql = "DELETE FROM {application_Institutions} WHERE Student_StudentID = '%s'";
  db_query($institutions_sql, $user->uid);

  if ( $form_state['values']['attendpostsecondary'] != 'None') {
    for ($i = 1; $i <= $form_state['values']['attendpostsecondary']; $i++) {
        // Get IDs and Names for colleges to
        if ($form_state['values']['postSecondaryName'. $i] != '0') {
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
       if ($form_state['values']['postSecondaryCity'. $i] == "" ||$form_state['values']['postSecondaryCity'. $i] == "0") {
          $pscity = $form_state['values']['postSecondaryCity'. $i ."_text"];
        }
        else {
          $pscity = $form_state['values']['postSecondaryCity'. $i];
        }
       if ($form_state['values']['postSecondaryDegree'. $i] == "" ||$form_state['values']['postSecondaryDegree'. $i] == "0") {
          $psdegree = $form_state['values']['postSecondaryDegree'. $i ."_text"];
        }
        else {
          $psdegree = $form_state['values']['postSecondaryDegree'. $i];
        }
       
      $institutions_sql = "INSERT into {application_Institutions} (Student_StudentID, Institution_Name, Institution_Country, Institution_City, Institution_State, First_Year_Attended, Last_Year_Attended, Degree_Certificate_Complete, Year_Degree_Completed, Degree, Major, Sonis_Institution_ID)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s' )";
      db_query($institutions_sql, $user->uid, $psname, $form_state['values']['postSecondaryCountry'. $i], $pscity, $form_state['values']['postSecondaryState'. $i], $form_state['values']['postSecondaryStartYear'. $i], $form_state['values']['postSecondaryEndYear'. $i], $degreecomplete, $form_state['values']['postSecondaryDegeree'. $i], $psdegree, $form_state['values']['postSecondaryMajor'. $i], $form_state['values']['postSecondaryName'. $i]);
    }
  }
  
  
  // lets clean out the database of licenses so we don't have to try updating
  $certs_sql = "DELETE FROM {application_Certs} WHERE Student_StudentID = '%s'";
  db_query($certs_sql, $user->uid);
  
  // lets deal with the license information now
  // build a loop to process each license
  for ($i = 1; $i <= $form_state['values']['Certificates_Number']; $i++) {
    $expdate = '1899-12-30 00:00:00';
    $effdate = '1899-12-30 00:00:00';
    $memo = '';
    if ($form_state['values']['Certificate_text'. $i] == "0" || $form_state['values']['Certificate_text'. $i] == "OTHER" ) {
      $licensetype = $form_state['values']['Licensetype'. $i];
    }
    else {
      $licensetype = $form_state['values']['Certificate_text'. $i]; 
    }
    // build memo field
    if (strcasecmp($form_state['values']['countryissued'. $i], "UNITED STATES") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "American Samoa") == 0 || strcasecmp($form_state['values']['countryissued'. $i], "Federated States of Micronesia") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "Guam") == 0 || strcasecmp($form_state['values']['countryissued'. $i], "U.S. Minor Outlying Is") == 0
      || strcasecmp($form_state['values']['countryissued'. $i], "Puerto Rico") == 0) {
      $memo = $memo . $form_state['values']['countryissued'. $i] .', '. $form_state['values']['stateissued'. $i];
    }
    else {
      $memo = $memo . $form_state['values']['countryissued'. $i];
    }   
    // build dates
//     $expdate = $form_state['values']['Expiration_date'. $i]['year'] .'-'. $form_state['values']['Expiration_date'. $i]['month'] .'-'. $form_state['values']['Expiration_date'. $i]['day'] .' 00:00:00';
//     $effdate = $form_state['values']['Effective_date'. $i]['year'] .'-'. $form_state['values']['Effective_date'. $i]['month'] .'-'. $form_state['values']['Effective_date'. $i]['day'] .' 00:00:00';
    $expdate = $form_state['values']['Expiration_date'. $i];
    $effdate = $form_state['values']['Effective_date'. $i];

    $certs_sql = "INSERT into {application_Certs} (Student_StudentID, Cert, Cert_Country, Cert_State, Effective_date, Expiration_date, Memo)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s' )";
    db_query($certs_sql, $user->uid, $licensetype, $form_state['values']['countryissued'. $i], $form_state['values']['stateissued'. $i],  $effdate, $expdate, $memo);
  }
  

  //Fire Application Updated Trigger
  module_invoke_all('application_changed', 'update', $user);

  drupal_set_message(t('Thanks for saving your Academic Information.'));
  if ($form_state['values']['op'] == "Save and Return Later") {
    drupal_goto('logout');
  }
  else {
    drupal_goto('application/generalcollegeapplication3');
  }
}

function _application_form_page2_load_defaults(&$form_state) {
  global $user;

  $biographic_sql = "SELECT HighSchool_Name, HighSchool_Country, HighSchool_State, HighSchool_City, HighSchool_Attendance, HighSchool_Grad_Year, HighSchool_Sonis_ID, HighSchool_Equivalent_Type, GED_Testing_Site, GED_Date_Of_Issue, OtherSchooling_CLEP, OtherSchooling_AP, OtherSchooling_IB FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));

  if ($a) {
    if (!isset($form_state['values']['highschoolcountry']))
      $form_state['values']['highschoolcountry'] = $a['HighSchool_Country'];
    if (!isset($form_state['values']['highschoolstate']))
      $form_state['values']['highschoolstate'] = $a['HighSchool_State'];

    if (!isset($form_state['values']['highschoolcity']) && !isset($form_state['values']['highschoolcity_text'])) {
      $tmp = array_merge(sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "1"),
                                                  array('inst_city', ""),
                                                  array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ")))), 'inst_city', 'inst_city'),
                         sonisweb_integration_sql_to_options(
                         sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('inst_txt', ""),
                                                  array('insttypcod', "2"),
                                                  array('inst_city', ""),
                                                  array('inst_state', ($form_state['values']['highschoolstate']?$form_state['values']['highschoolstate']:"YZ")))), 'inst_city', 'inst_city')
                );
      unset($tmp['']);
      ksort($tmp);
      $tmp['0'] = 'Not Listed';
      $tmp = array_merge(array('' => ''), $tmp);
      if (array_key_exists($a['HighSchool_City'], $tmp))
        $form_state['values']['highschoolcity'] = $a['HighSchool_City'];
      else {
        $form_state['values']['highschoolcity_text'] = $a['HighSchool_City'];
        $form_state['values']['highschoolcity'] = 0;
      }
    }

    if (!isset($form_state['values']['highschoolname']))
      $form_state['values']['highschoolname'] = $a['HighSchool_Sonis_ID'];
    if (!isset($form_state['values']['highschoolname_text']) && $form_state['values']['highschoolname'] == "0")
      $form_state['values']['highschoolname_text'] = $a['HighSchool_Name'];

    if (!isset($form_state['values']['attendhighschool']))
      $form_state['values']['attendhighschool'] = $a['HighSchool_Attendance'];
    if (!isset($form_state['values']['graduationyear']))
      $form_state['values']['graduationyear'] = $a['HighSchool_Grad_Year'];
    if (!isset($form_state['values']['highschooltype']))
      $form_state['values']['highschooltype'] = $a['HighSchool_Equivalent_Type'];
    if (!isset($form_state['values']['gedtesting']))
      $form_state['values']['gedtesting'] = $a['GED_Testing_Site'];

    if (!isset($form_state['values']['geddate']) || substr($form_state['values']['geddate'], 0, 1) == 0) {
//       $GED_date = $a['GED_Date_Of_Issue'];
//       $GED_date = split("-", $GED_date);
//       $form_state['values']['geddate']['year'] = $GED_date[0];
//       $form_state['values']['geddate']['month'] = $GED_date[1];
//       $GED_date = split(" ", $GED_date[2]);
//       $form_state['values']['geddate']['day'] = $GED_date[0];
      $form_state['values']['geddate'] = $a['GED_Date_Of_Issue'];
    }
    if ($a['OtherSchooling_CLEP'] == '1' || $a['OtherSchooling_AP'] == '1' || $a['OtherSchooling_IB'] == '1') {
      if (!isset($form_state['values']['credits']))
        $form_state['values']['credits'] = '1';
    }
    else {
      if (!isset($form_state['values']['credits']))
        $form_state['values']['credits'] = '0';
    }
    if (!isset($form_state['values']['CLEP']))
      $form_state['values']['CLEP'] = $a['OtherSchooling_CLEP'];
    if (!isset($form_state['values']['AP']))
      $form_state['values']['AP'] = $a['OtherSchooling_AP'];
    if (!isset($form_state['values']['IB']))
      $form_state['values']['IB'] = $a['OtherSchooling_IB'];
		
    if (!isset($form_state['values']['attendedfhchs'])) {
  		// Take care of fhchs attendance
  		$fhchs_attendance_sql = "SELECT * FROM {application_fhchs_attendance} WHERE sid='%s'";
  		$result = db_query($fhchs_attendance_sql, $user->uid);
  		// iterate through results
  		$a = db_fetch_array($result);
			$form_state['values']['attendedfhchs'] = $a['attendance_type'];
			$form_state['values']['lastattended'] = $a['attendance_date'];
    }
		
    // take care of the post secondary institutions
    $institutions_sql = "SELECT Institution_Name, Institution_Country, Institution_City, Institution_State, First_Year_Attended, Last_Year_Attended, Degree_Certificate_Complete, Year_Degree_Completed, Degree, Major, Sonis_Institution_ID FROM {application_Institutions} WHERE Student_StudentID = '%s'";
    $result = db_query($institutions_sql, $user->uid);
    $i = 0;

    while ($a = db_fetch_array($result)) {
      $i++;
      if (!isset($form_state['values']['postSecondaryCountry'. $i]))
        $form_state['values']['postSecondaryCountry'. $i] = $a['Institution_Country'];
      if (!isset($form_state['values']['postSecondaryState'. $i]))
        $form_state['values']['postSecondaryState'. $i] = $a['Institution_State'];

      if (!isset($form_state['values']['postSecondaryCity'. $i]) && !isset($form_state['values']['postSecondaryCity'. $i ."_text"])) {
        $tmp = array_merge(sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "3"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "4"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "5"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "6"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "7"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "8"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city'),
                           sonisweb_integration_sql_to_options(
                           sonisweb_integration_api("CFC.education", "institutsearch", "yes", array(array('sonis_ds', '#sonis.ds#'),
                                                    array('inst_txt', ""),
                                                    array('insttypcod', "9"),
                                                    array('inst_city', ""),
                                                    array('inst_state', ($form_state['values']['postSecondaryState'. $i]?$form_state['values']['postSecondaryState'. $i]:"YZ")))), 'inst_city', 'inst_city')
                  );
        unset($tmp['']);
        ksort($tmp);
        $tmp['0'] = 'Not Listed';
        $tmp = array_merge(array('' => ''), $tmp);
        if (array_key_exists($a['Institution_City'], $tmp))
          $form_state['values']['postSecondaryCity'. $i] = $a['Institution_City'];
        else {
          $form_state['values']['postSecondaryCity'. $i ."_text"] = $a['Institution_City'];
          $form_state['values']['postSecondaryCity'. $i] = 0;
        }
      }

      if (!isset($form_state['values']['postSecondaryName'. $i]) && !isset($form_state['values']['postSecondaryName'. $i ."_text"])) {
        $form_state['values']['postSecondaryName'. $i] = $a['Sonis_Institution_ID'];
        if ($form_state['values']['postSecondaryName'. $i] == '0') {
          $form_state['values']['postSecondaryName'. $i ."_text"] = $a['Institution_Name'];
        }
      }

      if (!isset($form_state['values']['postSecondaryMajor'. $i]))
        $form_state['values']['postSecondaryMajor'. $i] = $a['Major'];

      $tmp = sonisweb_integration_dropbox_to_form_api_options_array(
                         sonisweb_integration_api("CFC.drp_box", "degree", "no", array(array('sonis_ds', '#sonis.ds#'),
                                                  array('allow_blank', "No"),
                                                  array('multi_select', "No"),
                                                  array('hide', "No"),
                                                  array('Additional_Properties', ""))));
      unset($tmp['']);
      if (!isset($form_state['values']['postSecondaryDegree'. $i])) {
        if (array_key_exists($a['Degree'], $tmp))
          $form_state['values']['postSecondaryDegree'. $i] = $a['Degree'];
        else {
          $form_state['values']['postSecondaryDegree'. $i] = 0;
          $form_state['values']['postSecondaryDegree'. $i ."_text"] = $a['Degree'];
        }
      }


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
    // take care of certs
    $certs_sql = "SELECT Student_StudentID, Cert, Cert_Country, Cert_State, Effective_date, Expiration_date, Memo FROM {application_Certs} WHERE Student_StudentID = '%s'";
    $result = db_query($certs_sql, $user->uid);
    $i = 0;
    $licenses = sonisweb_integration_dropbox_to_form_api_options_array(
                sonisweb_integration_api("CFC.licenses", "licenses_drop", "no", array(array('sonis_ds', '#sonis.ds#'),
                                         array('allow_blank', "No"),
                                         array('multi_select', "No"),
                                         array('hide', "No"))));
    unset($licenses['']);
    asort($licenses);
    $licenses['0'] = 'Not Listed';
    $licenses = array_merge(array('' => ''), $licenses);
    while ($a = db_fetch_array($result)) {
      $i++;
      if (!isset( $form_state['values']['Certificate_text'. $i]) && !isset($form_state['values']['Licensetype'. $i])) {
        if (array_key_exists($a['Cert'], $licenses))
          $form_state['values']['Certificate_text'. $i] = $a['Cert'];
        else {
          $form_state['values']['Licensetype'. $i] = $a['Cert'];
          $form_state['values']['Certificate_text'. $i] = 0;
        }
      }
      if (!isset($form_state['values']['Effective_date'. $i]) || substr($form_state['values']['Effective_date'], 0, 1) == 0) {
//         $dob                                            = $a['Effective_date'];
//         $dob = split("-", $dob);
//         $form_state['values']['Effective_date'. $i]['year'] = $dob[0];
//         $form_state['values']['Effective_date'. $i]['month'] = $dob[1];
//         $dob = split(" ", $dob[2]);
//         $form_state['values']['Effective_date'. $i]['day'] = $dob[0];
        $form_state['values']['Effective_date'. $i] = $a['Effective_date'];
      }
      if (!isset($form_state['values']['Expiration_date'. $i]) || substr($form_state['values']['Expiration_date'], 0, 1) == 0) {
//         $dob                                            = $a['Expiration_date'];
//         $dob = split("-", $dob);
//         $form_state['values']['Expiration_date'. $i]['year'] = $dob[0];
//         $form_state['values']['Expiration_date'. $i]['month'] = $dob[1];
//         $dob = split(" ", $dob[2]);
//         $form_state['values']['Expiration_date'. $i]['day'] = $dob[0];
        $form_state['values']['Expiration_date'. $i] = $a['Expiration_date'];
      }
      if (!isset($form_state['values']['countryissued'. $i]))
        $form_state['values']['countryissued'. $i] = $a['Cert_Country']; 
      if (!isset($form_state['values']['stateissued'. $i]))
        $form_state['values']['stateissued'. $i] = $a['Cert_State']; 
    }
    if (!isset($form_state['values']['Certificates_Number'])) {
      if ($i == 0)
        $form_state['values']['Certificates_Number'] = 'None';
      else
        $form_state['values']['Certificates_Number'] = $i;
    }
  }
}
