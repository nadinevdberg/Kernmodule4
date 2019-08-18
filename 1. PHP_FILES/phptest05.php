<?php include "include.php";

$query = "SELECT u.username as gebruikersnaam, th.thing_id as 'Thing ID', th.data 
AS Data FROM users u 
LEFT JOIN thing th ON (th.user_id = u.id) 
ORDER BY u.username ";


if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  

//maak selectie van wat ik terug krijg uit query. ik wil door alles wat je terug krijgt heenlopen  
while ($row = $result->fetch_assoc()){

    echo $row["gebruikersnaam"] ." ". $row["Thing ID"]." ". $row["Data"]."</br>";
}


?>