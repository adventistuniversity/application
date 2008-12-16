<?php

function application_form_page1($form_state) {
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
    '#maxlength' => 20,
  );
  $form['Name']['middle'] = array(
    '#type' => 'textfield',
    '#title' => t('Middle Name'),
    '#default_value' => $form_state['values']['middle'],
    '#required' => FALSE,
    '#maxlength' => 20,
  );
  $form['Name']['last'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#default_value' => $form_state['values']['last'],
    '#required' => TRUE,
    '#maxlength' => 20,
  );

// Birthplace Information
  $form['Birthplace Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Birthplace Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['Birthplace Information']['dateofbirth'] = array(
    '#type' => 'date',
    '#title' => t('Date of Birth'),
    '#default_value' => $form_state['values']['dateofbirth'],
     '#required' => TRUE,
  );
  $form['Birthplace Information']['countryofbirth'] = array(
    '#type' => 'select',
    '#title' => t('Country of Birth'),
    '#default_value' => $form_state['values']['countryofbirth'],
    '#options' => array(
      'USA' => t('USA'),
      'Chile' => t('Chile'),
      'Italy' => t('Italy'),
  ),
	'#ahah' => array(
	  'path' => 'application/js',
	  'wrapper' => 'edit-stateofbirth-wrapper',
	  'method' => 'replace',
	  'event' => 'change',
	  'effect' => 'fade',
	),
    '#required' => TRUE,
  );
  $form['Birthplace Information']['cityofbirth'] = array(
    '#type' => 'textfield',
    '#title' => t('City of Birth'),
    '#default_value' => $form_state['values']['cityofbirth'],
     '#required' => TRUE,
  );
  $form['Birthplace Information']['stateofbirth'] = array(
    '#type' => 'select',
    '#title' => t('State of Birth'),
    '#default_value' => $form_state['values']['stateofbirth'],
  '#options' => array(
	'AL' => t('Alabama'),
	'AK' => t('Alaska'),
	'AZ' => t('Arizona'),
	'AR' => t('Arkansas'),
	'CA' => t('California'),
	'CO' => t('Colorado'),
	'CT' => t('Connecticut'),
	'DE' => t('Delaware'),
	'DC' => t('District of Columbia'),
	'FL' => t('Florida'),
	'GA' => t('Georgia'),
	'HI' => t('Hawaii'),
	'ID' => t('Idaho'),
	'IL' => t('Illinois'),
	'IN' => t('Indiana'),
	'IA' => t('Iowa'),
	'KS' => t('Kansas'),
	'KY' => t('Kentucky'),
	'LA' => t('Louisiana'),
	'ME' => t('Maine'),
	'MD' => t('Maryland'),
	'MA' => t('Massachusetts'),
	'MI' => t('Michigan'),
	'MN' => t('Minnesota'),
	'MS' => t('Mississippi'),
	'MO' => t('Missouri'),
	'MT' => t('Montana'),
	'NE' => t('Nebraska'),
	'NV' => t('Nevada'),
	'NH' => t('New Hampshire'),
	'NJ' => t('New Jersey'),
	'NM' => t('New Mexico'),
	'NY' => t('New York'),
	'NC' => t('North Carolina'),
	'ND' => t('North Dakota'),
	'OH' => t('Ohio'),
	'OK' => t('Oklahoma'),
	'OR' => t('Oregon'),
	'PA' => t('Pennsylvania'),
	'RI' => t('Rhode Island'),
	'SC' => t('South Carolina'),
	'SD' => t('South Dakota'),
	'TN' => t('Tennessee'),
	'TX' => t('Texas'),
	'UT' => t('Utah'),
	'VT' => t('Vermont'),
	'VA' => t('Virginia'),
	'WA' => t('Washington'),
	'WV' => t('West Virginia'),
	'WI' => t('Wisconsin'),
	'WY' => t('Wyoming'),
  ),
    '#required' => FALSE,
  );
  $form['Birthplace Information']['countryofcitizenship'] = array(
    '#type' => 'select',
    '#title' => t('Country of Citizenship'),
    '#default_value' => $form_state['values']['countryofbirth'],
  '#options' => array(
    'USA' => t('USA'),
    'Chile' => t('Chile'),
    'Italy' => t('Italy'),
  ),
    '#required' => FALSE,
  );

  $form['Birthplace Information']['ssn'] = array(
    '#type' => 'textfield',
    '#title' => t('Social Security Number'),
    '#default_value' => $form_state['values']['ssn'],
     '#required' => TRUE,
  );
  $form['Birthplace Information']['aliennumber'] = array(
    '#type' => 'textfield',
    '#title' => t('Naturalized Citizen or Permanent Resident Number'),
    '#default_value' => $form_state['values']['aliennumber'],
    '#required' => TRUE,
  );
  $form['Birthplace Information']['aliennumberapplied'] = array(
    '#type' => 'checkbox',
    '#title' => t('Permanent Resident Number applied for'),
    '#default_value' => $form_state['values']['aliennumberapplied'],
     '#required' => TRUE,
  );
  $form['Birthplace Information']['visa'] = array(
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

// Contact Information
  $form['Contact Information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['Contact Information']['countryofresidence'] = array(
    '#type' => 'select',
    '#title' => t('Country of Residence'),
    '#default_value' => $form_state['values']['countryofresidence'],
  '#options' => array(
    'USA' => t('USA'),
    'Chile' => t('Chile'),
    'Italy' => t('Italy'),
  ),
    '#required' => FALSE,
  );
  $form['Contact Information']['streetaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Address'),
    '#default_value' => $form_state['values']['streetaddress'],
    '#required' => TRUE,
  );
  $form['Contact Information']['addresscity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $form_state['values']['addresscity'],
    '#required' => TRUE,
  );
  $form['Contact Information']['addresscity'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => $form_state['values']['addresscity'],
    '#required' => TRUE,
  );
  $form['Contact Information']['state'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#default_value' => $form_state['values']['state'],
  '#options' => array(
    'FL' => t('Florida'),
    'MS' => t('Mississippi'),
    'NY' => t('New York'),
  ),
    '#required' => TRUE,
  );
  $form['Contact Information']['postalcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => $form_state['values']['postalcode'],
    '#required' => TRUE,
	'#maxlength' => 10,
	'#size' => 10,
  );
  $form['Contact Information']['primaryphone'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary Phone Number'),
    '#default_value' => $form_state['values']['primaryphone'],
    '#required' => TRUE,
	'#description' => "The first number we should dial when trying to reach you.",
  );
  $form['Contact Information']['alternatephone'] = array(
    '#type' => 'textfield',
    '#title' => t('Alternate Phone Number'),
    '#default_value' => $form_state['values']['alternatephone'],
    '#required' => FALSE,
    '#description' => "If we can't reach you at the first number, we'll try this one.",
  );
return ($form);

}
?>
