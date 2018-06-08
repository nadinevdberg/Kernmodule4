<?php include "include.php";

$query = "SELECT thing_id, ROUND(AVG(temperature),0) AS gemiddelde_temperatuur FROM things WHERE thing_id=2 GROUP BY thing_id";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  

//maak selectie van wat ik terug krijg uit query. ik wil door alels wat je terug krijgt heenlopen  
while ($row = $result->fetch_assoc()){

    echo $row["gemiddelde_temperatuur"];
   // echo $row["thing_id"]." ". $row["gemiddelde_temperatuur"]."</br>";
}


?>