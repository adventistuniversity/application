<?php

function application_form_page3($form_state) {
  $form = array();

  ahah_helper_register($form, $form_state);

// Page 3
// Educational Experience - Plans for Study at FHCHS
$form['Plans for Study'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plans for Study at FHCHS'),
	'#description' => "Please select the year, term, department and programs you would like to apply for.",
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
$form['Plans for Study']['yearofinterest'] = array(
    '#type' => 'select',
    '#title' => t('School Year'),
    '#default_value' => $form_state['values']['yearofinterest'], 
    '#options' => array(
      '1964' => t('1964-1965'),
      '1965' => t('1965-1966'),
      '1966' => t('1966-1967'),
    ),
    '#required' => TRUE,
);
$form['Plans for Study']['termofinterest'] = array(
    '#type' => 'select',
    '#title' => t('Start Term'),
    '#default_value' => $form_state['values']['termofinterest'], 
    '#options' => array(
      'Fall' => t('Fall'),
      'Spring' => t('Spring'),
      'Summer' => t('Summer'),
    ),
    '#required' => TRUE,
);
$form['Plans for Study']['department1'] = array(
    '#type' => 'select',
    '#title' => t('First Department Choice'),
    '#default_value' => $form_state['values']['department1'], 
    '#options' => array(
      'Nursing' => t('Department of Nursing'),
      'OTA' => t('Department of Occupational Therapy Assistant'),
      'Something else' => t('Department of Radiography'),
    ),
    '#required' => TRUE,
);
$form['Plans for Study']['programs1'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Programs'),
    '#default_value' => $form_state['values']['programs1'], 
    '#options' => array(
      'Nursing' => t('AS Nursing'),
      'OTA' => t('BS Nursing'),
      'Something else' => t('Nursing Certificates'),
    ),
    '#required' => TRUE,
);
$form['Plans for Study']['department2'] = array(
    '#type' => 'select',
    '#title' => t('Second Department Choice'),
	'#description' => t('The second department choice is optional.'),
    '#default_value' => $form_state['values']['department2'], 
    '#options' => array(
      'Nursing' => t('Department of Nursing'),
      'OTA' => t('Department of Occupational Therapy Assistant'),
      'Something else' => t('Department of Radiography'),
    ),
    '#required' => FALSE,
);
$form['Plans for Study']['programs2'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Programs'),
    '#default_value' => $form_state['values']['programs2'], 
    '#options' => array(
      'Nursing' => t('AS Nursing'),
      'OTA' => t('BS Nursing'),
      'Something else' => t('Nursing Certificates'),
    ),
    '#required' => FALSE,
);
return ($form);

}
