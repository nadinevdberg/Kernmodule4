<?php

   $db_user = 'nadine';
   $db_pass = 'Aifeeku3OhH0aim1';
   $db_host = 'localhost';
   $db_name = 'nadine';

/* Open a connection */
$mysqli = new mysqli("$db_host","$db_user","$db_pass","$db_name");

/* check connection */
if ($mysqli->connect_errno) {
   echo "Failed to connect to MySQL: (" . $mysqli->connect_errno() . ") " . $mysqli->connect_error();
   exit();
} 

function showerror($error,$errornr) {
die("Error (" . $errornr . ") " . $error);
}


?>