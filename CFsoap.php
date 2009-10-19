<?php
// $Id$

//Import the SOAP library
require_once('nusoap/nusoap.php');

function get_sonis_instutition_dropdown_list($name = '', $city = '', $state = '') {
  $url = variable_get('application_sonis_api_url', '');

  $output = array();
  $client = new nusoap_client($url[$_SERVER['SERVER_NAME']], false, '', '', '', '');
  if ($client->getError()) { $output = array(t('An error has occured')); }

  $result = $client->call("doSomething", array('component' => "CFC.education",
                         'method' => 'institutsearch',
                         'hasReturnVariable' => "yes",
                         'argumentdata' => array(array('sonis_ds', '#sonis.ds#'),
                                                 array('inst_txt', $name),
                                                 array('inst_city', $city),
                                                 array('inst_state', $state))
                          ));
  foreach ($result['data'] as $resulta) {
    array_push($output, check_plain(trim($resulta[1])));
  }

  // Check for errors
  if ($client->fault) { $output = array(t('A fault has occured')); }
  else { if ($client->getError()) { $output = array(t('An error has occured')); } }

  return array_combine($output, $output);
}

?>
