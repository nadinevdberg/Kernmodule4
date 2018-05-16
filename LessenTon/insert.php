<?php include "include.php";

session_start();

$var_thing_id = $_SESSION["thing_id"];
$var_temp = $_GET["temp"];

$query = "INSERT INTO nadinevandenberg.things(id, thing_id, user_id, time, temperature) VALUES (NULL, $var_thing_id, 6, NOW(), $var_temp)";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  


?>