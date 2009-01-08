<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * Page 1.
 * 
 */
  require_once('sonis_sql.inc');
  require_once('CFsoap.php');
function application_form_page1($form_state) {
  global $user;
  $form = array();

  _application_form_page1_load_defaults($form_state);
  ahah_helper_register($form, $form_state);
  $states = get_sonis_drop_box("state");
  $countries = get_sonis_drop_box("country");

//   print_r($form);
//   print_r($form_state);

//
// Name
  $form['Name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Name']['preferred'] = array(
    '#type' => 'textfield',
    '#title' => t('Preferred Name or Nickname'),
    '#default_value' => $form_state['values']['preferred'],
    '#description' => "The name you would like us to refer to you by. For example, <em>Bob</em> if your first name is <em>Robert</em>.",
    '#maxlength' => 20,
  '#size' => 20,
  );
  $form['Name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('Legal First Name'),
    '#default_value' => $form_state['values']['first'],
    '#required' => TRUE,
    '#maxlength' => 30,
    '#size' => 30,
  );
  $form['Name']['middle'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle Name'),
    '#default_value' => $form_state['values']['middle'],
    '#required' => FALSE,
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $form_state['values']['last'],
    '#required' => TRUE,
    '#maxlength' => 30,
    '#size' => 30,
  );

// Birthplace Information
  $form['Birthplace_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Birthplace Information'),
    '#prefix' => '<div id="birthplace-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Birthplace_Information']['dateofbirth'] = array(
    '#type' => 'date',
    '#title' => t('Date of Birth'),
    '#default_value' => $form_state['values']['dateofbirth'],
     '#required' => TRUE,
  );
  $form['Birthplace_Information']['countryofbirth'] = array(
    '#type' => 'select',
    '#title' => t('Country of Birth'),
    '#default_value' => ($form_state['values']['countryofbirth'] == ""?"UNITED STATES":$form_state['values']['countryofbirth']),
    '#options' => $countries,
   '#ahah' => array(
     'path' => ahah_helper_path(array('Birthplace_Information')),
     'wrapper' => 'birthplace-information-wrapper',
     'method' => 'replace',
     'event' => 'change',
     'effect' => 'fade',
    ),
    '#required' => TRUE,
  );
  $form['Birthplace_Information']['update_countryofbirth'] = array(
    '#type' => 'submit',
    '#value' => t('Country of Birth'),
    // Note that we can simply use the generic submit callback provided by the
    // ahah_helper module here!
    // All it does, is set $form_state['rebuild'] = TRUE.
    '#submit' => array('ahah_helper_generic_submit'),
    // We set the 'no-js' class, which means this submit button will be hidden
    // automatically by Drupal if JS is enabled.
    '#attributes' => array('class' => 'no-js'),
  );

  if ($form_state['values']['countryofbirth'] == "" || $form_state['values']['countryofbirth'] == "UNITED STATES") {
    $form['Birthplace_Information']['cityofbirth'] = array(
      '#type' => 'textfield',
      '#title' => t('City of Birth'),
      '#default_value' => $form_state['values']['cityofbirth'],
      '#required' => TRUE,
      '#maxlength' => 35,
      '#size' => 35,
    );
    $form['Birthplace_Information']['stateofbirth'] = array(
      '#type' => 'select',
      '#title' => t('State of Birth'),
      '#default_value' => $form_state['values']['stateofbirth'],
      '#options' => $states,
      '#required' => FALSE,
    );
    $form['Birthplace_Information']['ssn'] = array(
      '#type' => 'textfield',
      '#title' => t('Social Security Number'),
      '#default_value' => $form_state['values']['ssn'],
      '#required' => TRUE,
      '#maxlength' => 9,
      '#size' => 9,
    );
  }
  else {
    $form['Birthplace_Information']['cityofbirth'] = array(
      '#type' => 'textfield',
      '#title' => t('City of Birth'),
      '#default_value' => $form_state['values']['cityofbirth'],
      '#required' => TRUE,
      '#maxlength' => 35,
      '#size' => 35,
    );
    $form['Birthplace_Information']['countryofcitizenship'] = array(
      '#type' => 'select',
      '#title' => t('Country of Citizenship'),
      '#default_value' => ($form_state['values']['countryofcitizenship'] == ""?$form_state['values']['countryofbirth']:$form_state['values']['countryofcitizenship']),
      '#ahah' => array(
        'path' => ahah_helper_path(array('Birthplace_Information')),
          'wrapper' => 'birthplace-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      '#options' => $countries,
      '#required' => FALSE,
    );
    $form['Birthplace_Information']['update_countryofcitizenship'] = array(
      '#type' => 'submit',
      '#value' => t('Country of Citizenship'),
      // Note that we can simply use the generic submit callback provided by the
      // ahah_helper module here!
      // All it does, is set $form_state['rebuild'] = TRUE.
      '#submit' => array('ahah_helper_generic_submit'),
      // We set the 'no-js' class, which means this submit button will be hidden
      // automatically by Drupal if JS is enabled.
      '#attributes' => array('class' => 'no-js'),
    );
    $form['Birthplace_Information']['numberquestion'] = array(
      '#type' => 'select',
      '#title' => t('Please indicate the immigration or citizenship number you have'),
      '#default_value' => $form_state['values']['numberquestion'],
      '#options' => array(
        'Please Select' => t(''),
        // US Social Security Number makes SS Field appear and Number field go away
        'US Social Security Number' => t('US Social Security Number'),
        'Naturalized Citizen Number' => t('Naturalized Citizen Number'),
        'Permanent Resident Number' => t('Permanent Resident Number'),
        // Applied for and Online Only makes number field go away
        'Permanent Resident Number Applied For' => t('Permanent Resident Number Applied For'),
        'Taking Online Courses Only' => t('Taking Online Courses Only'),
        ),
        '#ahah' => array(
        'path' => ahah_helper_path(array('Birthplace_Information')),
          'wrapper' => 'birthplace-information-wrapper',
          'method' => 'replace',
          'event' => 'change',
          'effect' => 'fade',
        ),
      '#required' => TRUE,
    );
      $form['Birthplace_Information']['update_numberquestion'] = array(
      '#type' => 'submit',
      '#value' => t('Please indicate the immigration or citizenship number you have'),
      // Note that we can simply use the generic submit callback provided by the
      // ahah_helper module here!
      // All it does, is set $form_state['rebuild'] = TRUE.
      '#submit' => array('ahah_helper_generic_submit'),
      // We set the 'no-js' class, which means this submit button will be hidden
      // automatically by Drupal if JS is enabled.
      '#attributes' => array('class' => 'no-js'),
    );
    if ($form_state['values']['numberquestion'] != "Taking Online Courses Only") {
      if ($form_state['values']['countryofcitizenship'] == "UNITED STATES" || $form_state['values']['numberquestion'] == "US Social Security Number") {
        $form['Birthplace_Information']['ssn'] = array(
          '#type' => 'textfield',
          '#title' => t('Social Security Number'),
          '#default_value' => $form_state['values']['ssn'],
          '#required' => TRUE,
          '#maxlength' => 9,
          '#size' => 9,
        );
      }
      else{
        $form['Birthplace_Information']['number'] = array(
          '#type' => 'textfield',
          '#title' => t('Naturalized Citizen or Permanent Resident Number'),
          '#default_value' => $form_state['values']['number'],
          '#required' => TRUE,
        );
        $form['Birthplace_Information']['visa'] = array(
        '#type' => 'select',
        '#title' => t('Current Visa Status'),
        '#default_value' => $form_state['values']['visa'],
        '#description' => "FHCHS is not currently accepting applicants requiring an F visa.",
        '#options' => _application_query_to_form_array("select visa_cod, visa_desc from visa order by visa_desc asc", TRUE, array('AppliedFor' => t('Visa Applied For'))),
        '#required' => FALSE,
        );
      }
    }

  }

// Contact Information
  $form['Contact_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
  '#prefix' => '<div id="contact-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['Contact_Information']['countryofresidence'] = array(
    '#type' => 'select',
    '#title' => t('Country of Residence'),
    '#default_value' => ($form_state['values']['countryofresidence'] == ""?"UNITED STATES":$form_state['values']['countryofresidence']),
  '#ahah' => array(
     'path' => ahah_helper_path(array('Contact_Information')),
     'wrapper' => 'contact-information-wrapper',
     'method' => 'replace',
     'event' => 'change',
     'effect' => 'fade',
    ),
    '#options' => $countries,
    '#required' => FALSE,
  );
  $form['Contact_Information']['update_countryofresidence'] = array(
    '#type' => 'submit',
    '#value' => t('Country of Residence'),
    '#submit' => array('ahah_helper_generic_submit'),
    '#attributes' => array('class' => 'no-js'),
  );
  $form['Contact_Information']['streetaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Address'),
    '#default_value' => $form_state['values']['streetaddress'],
    '#required' => TRUE,
    '#maxlength' => 35,
    '#size' => 35,
  );
  $form['Contact_Information']['addresscity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $form_state['values']['addresscity'],
    '#required' => TRUE,
    '#maxlength' => 35,
    '#size' => 35,
  );
  if ($form_state['values']['countryofresidence'] == "" || $form_state['values']['countryofresidence'] == "UNITED STATES") {
    $form['Contact_Information']['state'] = array(
      '#type' => 'select',
      '#title' => t('State'),
      '#default_value' => $form_state['values']['state'],
      '#options' => $states,
      '#required' => TRUE,
    );
  }
  $form['Contact_Information']['postalcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => $form_state['values']['postalcode'],
    '#required' => TRUE,
    '#maxlength' => 10,
    '#size' => 10,
  );
  $form['Contact_Information']['primaryphone'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary Phone Number'),
    '#default_value' => $form_state['values']['primaryphone'],
    '#required' => TRUE,
    '#description' => "The first number we should dial when trying to reach you.",
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Contact_Information']['alternatephone'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternate Phone Number'),
    '#default_value' => $form_state['values']['alternatephone'],
    '#required' => FALSE,
    '#description' => "If we can't reach you at the first number, we'll try this one.",
    '#maxlength' => 15,
    '#size' => 15,
  );
  $form['Contact_Information']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#default_value' => ($form_state['values']['email'] == ""?$user->mail:$form_state['values']['email']),
    '#required' => FALSE,
    '#description' => "",
    '#maxlength' => 100,
    '#size' => 35,
  );
  $form['Submit'] = array(
  '#type' => 'submit',
  '#value' => t('Save and Continue'),
  );
  return ($form);
}

function application_form_page1_validate($form, &$form_state) {
//  form_set_error('middle', t(print_r($form)));
}
function application_form_page1_submit($form, &$form_state) {
  global $user;
  date_default_timezone_set('UTC');
  $name = $form_state['values']['first'];
  $dob = $form_state['values']['dateofbirth']['year'] .'-'. $form_state['values']['dateofbirth']['month'] .'-'. $form_state['values']['dateofbirth']['day'] .' 00:00:00';
  //null values are interperted to 0 by the db_query sql injection fixing this makes it difficult to leave GED date NULL an arbitrary date (1/1/1800) was chosen by the developer to represent lack of GED NULL values
  $GED_date = '1899-12-30 00:00:00';
  if ($form_state['values']['ssn'] != NULL) {
    $ssn = $form_state['values']['ssn'];
  }
  else {
    $ssn = '0';
  }
//
//   print_r($form);
//   print_r($form_state);
//   exit;

  $a = "SELECT count(Student_StudentID) as count FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($a, $user->uid));

  if ($a['count'] > 0) {
    $biographic_sql = "UPDATE {application_Biographic} SET Student_Nickname = '%s', Student_Fname = '%s', Student_Mname = '%s', Student_Lname = '%s', Student_DOB = '%s', Student_SSN = '%s', Birth_Country = '%s', Birth_City = '%s', Birth_State = '%s', Citizenship_Country = '%s', Citizenship_ID_Number = '%s', Citizenship_ID_Type = '%s', Citizenship_Visa_Status = '%s' WHERE  Student_StudentID = '%s'";
    db_query($biographic_sql, $form_state['values']['preferred'], $form_state['values']['first'], $form_state['values']['middle'], $form_state['values']['last'], $dob , $ssn, $form_state['values']['countryofbirth'], $form_state['values']['cityofbirth'], $form_state['values']['stateofbirth'], $form_state['values']['countryofcitizenship'], $form_state['values']['number'], $form_state['values']['numberquestion'], $form_state['values']['visa'], $user->uid);
  }
  else {
    $biographic_sql = "INSERT into {application_Biographic} (Student_StudentID, Student_Nickname, Student_Fname, Student_Mname, Student_Lname, Student_DOB, Student_SSN, Birth_Country, Birth_City, Birth_State, Citizenship_Country, Citizenship_ID_Number, Citizenship_ID_Type, Citizenship_Visa_Status, HighSchool_Name, HighSchool_Country, HighSchool_State, HighSchool_City, HighSchool_Attendance, HighSchool_Sonis_ID, GED_Testing_Site, GED_Date_Of_Issue, Statistics_Gender, Statistics_Hispanic, Statistics_Ethnic_Origin, Statistics_Native_English, Statistics_Native_Language, Statistics_Marital_Status, Statistics_Religious_Affiliation, Statistics_Home_Church, Statistics_Home_Church_City, Statistics_Home_Church_State, Personal_Statement_Agreement)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%s', '%s', '%s', '%s', '%d', '%s', '%d', '%s', '%s', '%s', '%s', '%s', '%s', '%d')";
    db_query($biographic_sql, $user->uid, $form_state['values']['preferred'], $form_state['values']['first'], $form_state['values']['middle'], $form_state['values']['last'], $dob , $ssn, $form_state['values']['countryofbirth'], $form_state['values']['cityofbirth'], $form_state['values']['stateofbirth'], $form_state['values']['countryofcitizenship'], $form_state['values']['number'], $form_state['values']['numberquestion'], $form_state['values']['visa'], '', '', '', '', '', '', '', $GED_date, '', '', '', '', '', '', '', '', '', '', 0);
  }
  

  $a = "SELECT count(Student_StudentID) as count FROM {application_Address} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($a, $user->uid));

  if ($a['count'] > 0) {
    $address_sql = "UPDATE {application_Address} SET Country = '%s', State = '%s', City = '%s', Postal = '%s', Street = '%s', Primary_phone = '%s', Alternate_phone = '%s', Email = '%s', Contact_Name = '%s' WHERE Student_StudentID = '%s' and Type = '%s'";
    db_query($address_sql, $form_state['values']['countryofresidence'], $form_state['values']['state'],   $form_state['values']['addresscity'], $form_state['values']['postalcode'], $form_state['values']['streetaddress'], $form_state['values']['primaryphone'], $form_state['values']['alternatephone'], $form_state['values']['email'], $form_state['values']['preferred'], $user->uid, 'Pref Add');
  }
  else {
    $address_sql = "INSERT into {application_Address} (Student_StudentID, Country, State, City, Postal, Street, Primary_phone, Alternate_phone, Email, Type, Contact_Name)VALUES('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')";
    db_query($address_sql, $user->uid, $form_state['values']['countryofresidence'], $form_state['values']['state'],   $form_state['values']['addresscity'], $form_state['values']['postalcode'], $form_state['values']['streetaddress'], $form_state['values']['primaryphone'], $form_state['values']['alternatephone'], $form_state['values']['email'], 'Pref Add', $form_state['values']['preferred']);
  }
  drupal_set_message(t('Thank you for starting your application. %name', array('%name' => $name)));
  drupal_goto('application/generalcollegeapplication2');
}

function _application_form_page1_load_defaults(&$form_state) {
  global $user;

  $biographic_sql = "SELECT Student_Nickname, Student_Fname, Student_Mname, Student_Lname, Student_DOB, Student_SSN, Birth_Country, Birth_City, Birth_State, Citizenship_Country, Citizenship_ID_Number, Citizenship_ID_Type, Citizenship_Visa_Status, GED_Date_Of_Issue FROM {application_Biographic} WHERE Student_StudentID = '%s'";
  $a = db_fetch_array(db_query($biographic_sql, $user->uid));

  if ($a) {
    $address_sql = "SELECT Country, State, City, Postal, Street, Primary_phone, Alternate_phone, Email, Type FROM {application_Address} WHERE Student_StudentID = '%s'";
    $b = db_fetch_array(db_query($address_sql, $user->uid));

    if ($b) {
      if (!isset($form_state['values']['preferred']))
        $form_state['values']['preferred']              = $a['Student_Nickname'];
      if (!isset($form_state['values']['first']))
        $form_state['values']['first']                  = $a['Student_Fname'];
      if (!isset($form_state['values']['middle']))
        $form_state['values']['middle']                 = $a['Student_Mname'];
      if (!isset($form_state['values']['last']))
        $form_state['values']['last']                   = $a['Student_Lname'];
     if (!isset($form_state['values']['dateofbirth'])) {
        $dob                                            = $a['Student_DOB'];
        $dob = split("-", $dob);
        $form_state['values']['dateofbirth']['year'] = $dob[0];
        $form_state['values']['dateofbirth']['month'] = $dob[1];
        $dob = split(" ", $dob[2]);
        $form_state['values']['dateofbirth']['day'] = $dob[0];
      }
      if (!isset($form_state['values']['ssn'])) {
        if ($a['Student_SSN'] == 0)
          $form_state['values']['ssn']                  = "";
        else
          $form_state['values']['ssn']                  = $a['Student_SSN'];
      }
      if (!isset($form_state['values']['countryofbirth']))
        $form_state['values']['countryofbirth']         = $a['Birth_Country'];
      if (!isset($form_state['values']['cityofbirth']))
        $form_state['values']['cityofbirth']            = $a['Birth_City'];
      if (!isset($form_state['values']['stateofbirth']))
        $form_state['values']['stateofbirth']           = $a['Birth_State'];
      if (!isset($form_state['values']['countryofcitizenship']))
        $form_state['values']['countryofcitizenship']   = $a['Citizenship_Country'];
      if (!isset($form_state['values']['number']))
        $form_state['values']['number']                 = $a['Citizenship_ID_Number'];
      if (!isset($form_state['values']['numberquestion']))
        $form_state['values']['numberquestion']         = $a['Citizenship_ID_Type'];
      if (!isset($form_state['values']['visa']))
        $form_state['values']['visa']                   = $a['Citizenship_Visa_Status'];
      if (!isset($form_state['values']['countryofresidence']))
        $form_state['values']['countryofresidence']     = $b['Country'];
      if (!isset($form_state['values']['state']))
        $form_state['values']['state']                  = $b['State'];
      if (!isset($form_state['values']['addresscity']))
        $form_state['values']['addresscity']            = $b['City'];
      if (!isset($form_state['values']['postalcode']))
        $form_state['values']['postalcode']             = $b['Postal'];
      if (!isset($form_state['values']['streetaddress']))
        $form_state['values']['streetaddress']          = $b['Street'];
      if (!isset($form_state['values']['primaryphone']))
        $form_state['values']['primaryphone']           = $b['Primary_phone'];
      if (!isset($form_state['values']['alternatephone']))
        $form_state['values']['alternatephone']         = $b['Alternate_phone'];
      if (!isset($form_state['values']['email']))
        $form_state['values']['email']                  = $b['Email'];
      if (!isset($form_state['values']['preferred']))
        $form_state['values']['preferred']              = $b['Type'];
    }
  }
  else {
    $address_sql = "INSERT into {application_Biographic} (Student_StudentID) VALUES ('%s')";
    db_query($address_sql, $user->uid);
 }
}
