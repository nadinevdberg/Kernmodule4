<?php include "include.php";



$query = "SELECT temp AS Temperatuur FROM data WHERE thing_id=2 ORDER BY datetime DESC LIMIT 1 ";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  

//maak selectie van wat ik terug krijg uit query. ik wil door alels wat je terug krijgt heenlopen  
while ($row = $result->fetch_assoc()){

    echo $row["Temperatuur"];
}


?>