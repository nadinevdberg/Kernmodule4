<?php include "include.php";

$var_thing_id = $_GET["thing_id"];
$var_data = $_GET["data"];

$query = "INSERT INTO data(id, thing_id, datetime, data) VALUES (NULL, $var_thing_id, NOW(), $var_data)";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  


?>