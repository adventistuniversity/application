<?php

function application_form_page3() {
// Page 3
// Educational Experience - Plans for Study at FHCHS
$form['Plans for Study'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plans for Study at FHCHS'),
	'#description' => "Once accepted to take general courses, what program would you like to study?",
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['Plans for Study']['asprogramanddate'] = array(
    '#type' => 'checkboxes',
    '#title' => t('AS Department of Choice'),
    '#default_value' => $form_state['values']['asprogramanddate'], 
  '#options' => array(
    'AS Nursing - Fall 2009' => t('AS Nursing - Fall 2009'),
    'AS Nursing - Spring 2010' => t('AS Nursing - Spring 2010'),
    'AS Nursing - Summer 2010' => t('AS Nursing - Summer 2010'),
    'AS Health and Biomedical Sciences - Fall 2009' => t('AS Health and Biomedical Sciences - Fall 2009'),
    'AS Health and Biomedical Sciences - Spring 2010' => t('AS Health and Biomedical Sciences - Spring 2010'),
    'AS Health and Biomedical Sciences - Summer 2010' => t('AS Health and Biomedical Sciences - Summer 2010'),
  ),
    '#required' => FALSE,
  );
$form['Plans for Study']['bsprogramanddate'] = array(
    '#type' => 'checkboxes',
    '#title' => t('BS Department of Choice'),
'#description' => "If you have an eligible license, you my apply to our Bachelor's completion programs.",
    '#default_value' => $form_state['values']['bsprogramanddate'], 
  '#options' => array(
    'BS Nursing - Fall 2009' => t('BS Nursing - Fall 2009'),
    'BS Nursing - Spring 2010' => t('BS Nursing - Spring 2010'),
    'BS Nursing - Summer 2010' => t('BS Nursing - Summer 2010'),
    'BS Health and Biomedical Sciences - Fall 2009' => t('BS Health and Biomedical Sciences - Fall 2009'),
    'BS Health and Biomedical Sciences - Spring 2010' => t('BS Health and Biomedical Sciences - Spring 2010'),
    'BS Health and Biomedical Sciences - Summer 2010' => t('BS Health and Biomedical Sciences - Summer 2010'),
  ),
    '#required' => FALSE,
  );
// BS Health Sciences before other BS programs
$form['Plans for Study']['bsprogramanddate'] = array(
    '#type' => 'checkboxes',
    '#title' => t('BS Program of Choice'),
'#description' => "If you have an eligible license, you my apply to our Bachelor's completion programs.",
    '#default_value' => $form_state['values']['bsprogramanddate'], 
  '#options' => array(
    'BS Nursing - Fall 2009' => t('BS Nursing - Fall 2009'),
    'BS Nursing - Spring 2010' => t('BS Nursing - Spring 2010'),
    'BS Nursing - Summer 2010' => t('BS Nursing - Summer 2010'),
    'BS Health Sciences - Fall 2009' => t('BS Health Sciences - Fall 2009'), // If checked then provide choice of tracks: 3-6 tracks.
    'BS Health and Biomedical Sciences - Spring 2010' => t('BS Health and Biomedical Sciences - Spring 2010'),
    'BS Health and Biomedical Sciences - Summer 2010' => t('BS Health and Biomedical Sciences - Summer 2010'),
  ),
    '#required' => FALSE,
  );
//      Certificates
//   	M.S. Nurse Anesthetist 
//  	Graduate General Studies 
// ? Maybe this should use jQuery Acordian ?
//

return ($form);

}