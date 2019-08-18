<?php include "include.php";

// Ik pak het gemiddelde van iedereen met een SSM. Dit doe ik zodat er een landelijk gemiddelde word genomen
// in plaats van een persoonlijk gemiddelde. Als ik alleen een persoonlijk gemiddelde gebruik, kan het zijn dat de gebruiker bij het 
// eerste gebruik van het product al een te hoog stressniveau heeft en dat de stressmeter daardoor geen alarm slaat

$query = "SELECT ROUND(AVG(data),0) AS Gemiddelde_Stress FROM data";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  


//maak selectie van wat ik terug krijg uit query.  
while ($row = $result->fetch_assoc()){

    echo $row["Gemiddelde_Stress"];

}


?>