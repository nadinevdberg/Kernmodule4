<?php include "include.php";


if (isset($_GET['PHPSESSID'])) {
$sid=htmlspecialchars($_GET['PHPSESSID']);
session_id($sid);
}	
session_start();

if (isset($_SESSION["thing_id"]) && $_SESSION["thing_id"]!=0) {
 echo $_SESSION["thing_id"]

} else {

echo "0";


$var_thing_id = $_SESSION["thing_id"];
$var_temp = $_GET["temp"];

$query = "INSERT INTO data(id, thing_id, datetime, temp) VALUES (NULL, $var_thing_id, NOW(), $var_temp)";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  


?>