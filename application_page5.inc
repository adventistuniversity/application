<?php
  require_once('CFsoap.php');
  require_once('sonis_sql.inc');
  
function application_form_page5($form_state) {
  $form = array();
  ahah_helper_register($form, $form_state);
  
    $form['Personal Statement'] = array(
      '#type' => 'fieldset',
      '#title' => t('Personal Statement'),
      '#description' => "There are lots of rules for being a student at FHCHS I understand that I will be expected to abide by these even if I don't know all of em.",
      '#prefix' => '<div id="Personal-Statement-study-wrapper">', // This is our wrapper div.
      '#suffix' => '</div>',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
  $form['Personal Statement']['Iagree'] = array(
      '#type' => 'select',
      '#title' => t('Please Say Yes'),
      '#default_value' => $form_state['values']['Iagree'],
      '#options' => array('Yes' => t('Yes'),
		'No' => t('No')),
      '#required' => TRUE,
  );
  
  return ($form);

}
?>