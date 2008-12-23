<?php
  require_once('CFsoap.php');
function application_form_page1($form_state) {
  global $user;
  $form = array();

  ahah_helper_register($form, $form_state);
  $states = get_sonis_drop_box("state");
  $countries = get_sonis_drop_box("country");

//
// Name
  $form['Name'] = array(
    '#type' => 'fieldset',
    '#title' => t('Name'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['Name']['preferred'] = array(
    '#type' => 'textfield',
    '#title' => t('Preferred Name or Nickname'),
    '#default_value' => $form_state['values']['first'],
    '#description' => "The name you would like us to refer to you by. For example, <em>Bob</em> if your first name is <em>Robert</em>.",
    '#maxlength' => 20,
  );
  $form['Name']['first'] = array(
    '#type' => 'textfield',
    '#title' => t('Legal First Name'),
    '#default_value' => $form_state['values']['first'],
    '#required' => TRUE,
    '#maxlength' => 30,
  );
  $form['Name']['middle'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle Name'),
    '#default_value' => $form_state['values']['middle'],
    '#required' => FALSE,
    '#maxlength' => 15,
  );
  $form['Name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $form_state['values']['last'],
    '#required' => TRUE,
    '#maxlength' => 30,
  );

// Birthplace Information
  $form['Birthplace_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Birthplace Information'),
    '#prefix' => '<div id="birthplace-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
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
    '#default_value' => $form_state['values']['countryofbirth'],
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
    );
  }
  else {
    $form['Birthplace_Information']['countryofcitizenship'] = array(
		'#type' => 'select',
		'#title' => t('Country of Citizenship'),
		'#default_value' => $form_state['values']['countryofcitizenship'],
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
  if ($form_state['values']['countryofbirth'] == "")
  {
	      $form['Birthplace_Information']['cow'] = array(
      '#type' => 'textfield',
      '#title' => t('I am a cow'),
      '#default_value' => $form_state['values']['cow'],
      '#required' => TRUE,
    );
  }
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
      '#required' => TRUE,
    );
    $form['Birthplace_Information']['number'] = array(
      '#type' => 'textfield',
      '#title' => t('Naturalized Citizen or Permanent Resident Number'),
      '#default_value' => $form_state['values']['number'],
      '#required' => TRUE,
    );

    $form['Birthplace_Information']['visa'] = array(
      '#type' => 'select',
      '#title' => t('Current Visa Status'),
      '#default_value' => $form_state['values']['countryofbirth'],
      '#description' => "FHCHS is not currently accepting applicants requiring an F visa.",
    '#options' => array(
      'Ask Zoe' => t(':)'),
      'or Katie' => t('F2'),
      'AppliedFor' => t('Visa Applied For'),
    ),
      '#required' => FALSE,
    );
  }

// Contact Information
  $form['Contact_Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
	'#prefix' => '<div id="contact-information-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['Contact_Information']['countryofresidence'] = array(
    '#type' => 'select',
    '#title' => t('Country of Residence'),
    '#default_value' => $form_state['values']['countryofresidence'],
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
    // Note that we can simply use the generic submit callback provided by the
    // ahah_helper module here!
    // All it does, is set $form_state['rebuild'] = TRUE.
    '#submit' => array('ahah_helper_generic_submit'),
    // We set the 'no-js' class, which means this submit button will be hidden
    // automatically by Drupal if JS is enabled.
    '#attributes' => array('class' => 'no-js'),
  );
  $form['Contact_Information']['streetaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Address'),
    '#default_value' => $form_state['values']['streetaddress'],
    '#required' => TRUE,
  );
  $form['Contact_Information']['addresscity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $form_state['values']['addresscity'],
    '#required' => TRUE,
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
  );
  $form['Contact_Information']['alternatephone'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternate Phone Number'),
    '#default_value' => $form_state['values']['alternatephone'],
    '#required' => FALSE,
    '#description' => "If we can't reach you at the first number, we'll try this one.",
  );
  $form['Contact_Information']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#default_value' => ($form_state['values']['email'] == ""?$user->mail:$form_state['values']['email']),
    '#required' => FALSE,
    '#description' => "",
  );
  $form['Submit'] = array(
	'#type' => 'submit',
	'#value' => t('Save and Continue'),
	);
return ($form);

}
?>
