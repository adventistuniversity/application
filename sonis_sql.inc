<?php
// $Id$

/**
 * @file
 * FHCHS General College Application
 *
 * SONIS SQL.
 * 
 */
  function _application_query_to_form_array($query, $blank_first_value = FALSE, $extra_values = array()) {
    if (stristr($query, "insert") === FALSE &&
       stristr($query, "update") === FALSE &&
       stristr($query, "drop") === FALSE &&
       stristr($query, "delete") === FALSE &&
       stristr($query, "create") === FALSE &&
       stristr($query, "into") === FALSE &&
       stristr($query, "alter") === FALSE) {

        if ($blank_first_value)
          $output = array('' => '');
        else
          $output = array();

        //Retrieve Username and Password
        $handle = fopen("c:\\php\\SecretFiles\\studentrw.cfg", "r");
                $trasha = fgets($handle);
                $dblocation = eregi_replace("[\r\n]", "", fgets($handle));
                $usernamey = eregi_replace("[\r\n]", "", fgets($handle));
                $passywordy = eregi_replace("[\r\n]", "", fgets($handle));
        fclose($handle);

        //Open Database Connection
        $dbhandle = mssql_connect($dblocation, $usernamey, $passywordy);
        mssql_select_db("SonisWebDatabase");

        $results = mssql_query($query, $dbhandle);

        while ($row = mssql_fetch_array($results)) {
          $output[$row[0]] = t($row[1]);
        }

        //Close Database connection
        mssql_close($dbhandle);
        
        if ($extra_values != array()) {
          foreach ($extra_values as $key => $values) {
            $output[$key] = $values;
          }
        }
        
        return ($output);
    }
    else {
      return (array('' => t('')));
    }
  }
  function get_years() {
    $year = range(date("Y"), (date("Y")-100), -1);
    return array_combine($year, $year);
  }
