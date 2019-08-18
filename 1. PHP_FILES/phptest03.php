<?php include "include.php";

session_start();

$var_thing_id =$_GET["thing_id"];
$var_password = $_GET["password"];


$query = "SELECT thing_id FROM thing WHERE thing_id = $var_thing_id AND password = '$var_password'";


if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  

$row = $result->fetch_assoc(); //ga naar die brij en trek daar 1 rij uit met iets wat ik wel begrijp

if ($row["thing_id"] == $var_thing_id){
    $_SESSION["thing_id"]= $var_thing_id;
    $_SESSION["password"]=$var_password;
   // echo " You are logged in";
    echo " You are logged in with session ID " ;
    echo $_SESSION["thing_id"];
    echo " and your session ID is: ";
    echo session_id();
} 

if ($row["thing_id"]!= $var_thing_id){
    echo "0";
}

?>