<?php
function get_sonis_drop_box($method) {
	//Import the SOAP library
	require_once('nusoap/nusoap.php');

	//Get a handle to the webservice
	$tmp_variable_client = new nusoap_client('http://fhcdv-mars/sonisweb200/soap.cfc', false, '', '', '', '');

	//Error Handleing
	$tmp_variable_err = $tmp_variable_client->getError();
	if ($tmp_variable_err) {
		$tmp_variable_result = array('error' => t('An error has occured'));
	}

	$tmp_variable_result = $tmp_variable_client->call("doSomething", array('component' => "CFC.drp_box",
												 'method' => $method,
												 'hasReturnVariable' => "no",
												 'argumentdata' => array(array('sonis_ds', '#sonis.ds#'),
																   array('allow_blank', "yes"),
																   array('hide', "no"),
																   array('multi_select', "no"),
																   array('Additional_Properties', ""),
                                   array('hide_excludes', 'yes'))
												  ));

	 $tmp_variable_result = preg_replace("/\s/", " ", $tmp_variable_result);
	 $tmp_variable_result = preg_replace("/<select name=\".*?\" >/", "", $tmp_variable_result);
	 
	 $tmp_variable_resulta = preg_replace("/.*?\"(.*?)\".*?/", "$1|", $tmp_variable_result);
	 $tmp_variable_resulta = explode("|", $tmp_variable_resulta);
	 array_push($tmp_variable_resulta, preg_replace("/>.*$/", "$1", array_pop($tmp_variable_resulta)));
	 array_pop($tmp_variable_resulta);

	 $tmp_variable_resultb = preg_replace("/.*?(>(.*?)<).*?/", "$2|", $tmp_variable_result);
	 $tmp_variable_resultb = explode("|", $tmp_variable_resultb);
	 array_push($tmp_variable_resultb, preg_replace("/\/.*$/", "$1", array_pop($tmp_variable_resultb)));
	 array_pop($tmp_variable_resultb);

	 $tmp_variable_result = array_combine($tmp_variable_resulta, $tmp_variable_resultb);

	// Check for a fault
	if ($tmp_variable_client->fault) {
		$tmp_variable_result = array('fault' => t('A fault has occured'));
	} else {
		// Check for errors
		$tmp_variable_err = $tmp_variable_client->getError();
		if ($tmp_variable_err) {
			// Display the error
		   $tmp_variable_result = array('error' => t('An error has occured'));
		}
	}
	return $tmp_variable_result;
}
?>
