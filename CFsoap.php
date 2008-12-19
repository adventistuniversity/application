<?php
//Import the SOAP library
require_once('nusoap/nusoap.php');

function get_sonis_drop_box($method) {
	//Get a handle to the webservice
	$client = new nusoap_client('http://fhcdv-mars/sonisweb200/soap.cfc', false, '', '', '', '');

	//Error Handleing
	$err = $client->getError();
	if ($err) {
		$result = array('error' => t('An error has occured'));
	}

	$result = $client->call("doSomething", array('component' => "CFC.drp_box",
												 'method' => $method,
												 'hasReturnVariable' => "no",
												 'argumentdata' => array(array('sonis_ds', '#sonis.ds#'),
																   array('allow_blank', "yes"),
																   array('hide', "no"),
																   array('multi_select', "no"),
																   array('Additional_Properties', ""),
                                   array('hide_excludes', 'yes'))
												  ));

	 $result = preg_replace("/\s/", " ", $result);
	 $result = preg_replace("/<select name=\".*?\" >/", "", $result);
	 
	 $resulta = preg_replace("/.*?\"(.*?)\".*?/", "$1|", $result);
	 $resulta = explode("|", $resulta);
	 array_push($resulta, preg_replace("/>.*$/", "$1", array_pop($resulta)));
	 array_pop($resulta);

	 $resultb = preg_replace("/.*?(>(.*?)<).*?/", "$2|", $result);
	 $resultb = explode("|", $resultb);
	 array_push($resultb, preg_replace("/\/.*$/", "$1", array_pop($resultb)));
	 array_pop($resultb);

	 $result = array_combine($resulta, $resultb);

	// Check for a fault
	if ($client->fault) {
		$result = array('fault' => t('A fault has occured'));
	} else {
		// Check for errors
		$err = $client->getError();
		if ($err) {
			// Display the error
		   $result = array('error' => t('An error has occured'));
		}
	}
	return $result;
}
?>
