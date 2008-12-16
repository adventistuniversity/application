<?php

function application_form_page4() {
// page 4
// Statistical Data
$form['Statistical Data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Statistical Data'),
	'#description' => "This information is collected for reporting purposes and is not considered for admissions.",
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
$form['Statistical Data']['gender'] = array(
	'#type' => 'select',
	'#title' => t('Gender'),
	'#default_value' => $form_state['values']['gender'], 
	'#required' => TRUE,
	'#options' => array(t('Yes'), t('No'), t('I prefer not to share.')),
);
$form['Statistical Data']['ethnicorigin'] = array(
	'#type' => 'select',
	'#title' => t('Ethnic Origin'),
	'#default_value' => $form_state['values']['ethnicorigin'], 
	'#required' => TRUE,
	'#options' => array(t('Need List'), t('No'), t('I prefer not to share.')),
); 
// ethinic origin must be two step question

$form['Statistical Data']['nativelanguage'] = array(
	'#type' => 'select',
	'#title' => t('Native Language'),
	'#default_value' => $form_state['values']['nativelanguage'], 
	'#required' => TRUE,
	'#options' => array(t('Yes'), t('No'), t('I prefer not to share.')),
	'#description' => t('Proof of English proficiency is required for admission.')
);
$form['Statistical Data']['maritalstatus'] = array(
	'#type' => 'select',
	'#title' => t('Marital Status'),
	'#default_value' => $form_state['values']['maritalstatus'], 
	'#required' => TRUE,
	'#options' => array(t('Yes'), t('No'), t('I prefer not to share.')),
);
$form['Statistical Data']['religion'] = array(
	'#type' => 'select',
	'#title' => t('Religion'),
	'#default_value' => $form_state['values']['Religion'], 
	'#required' => TRUE,
	'#options' => array(t('Yes'), t('No'), t('I prefer not to share.')),
);
// if Adventist then show Home church + City and State
$form['Statistical Data']['religionhomechurch'] = array(
	'#type' => 'textfield',
	'#title' => t('Name of Home Church'),
	'#default_value' => $form_state['values']['religionhomechurch'], 
	'#required' => FALSE,
);
$form['Statistical Data']['religionhomechurchcity'] = array(
	'#type' => 'textfield',
	'#title' => t('Home Church City'),
	'#default_value' => $form_state['values']['religionhomechurchcity'], 
	'#required' => FALSE,
);
$form['Statistical Data']['religionhomechurchstate'] = array(
	'#type' => 'select',
	'#title' => t('Home Church State'),
	'#default_value' => $form_state['values']['religionhomechurchstate'], 
	'#options' => array(
      'FL' => t('Florida'),
      'MS' => t('Mississippi'),
      'NY' => t('New York'),
  ),
	'#required' => FALSE,
);
return ($form);

}