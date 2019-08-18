<?php include "include.php";

// pak eerst het gemiddelde van alle gebruikers

$AVGquery = "SELECT ROUND(AVG(data),0) 
AS Gemiddelde_Stress 
FROM data";

if (!($result = $mysqli->query($AVGquery)))
showerror($mysqli->errno,$mysqli->error);  


//maak selectie van wat ik terug krijg uit query.  
while ($row = $result->fetch_assoc()){
    $var_avg = $row["Gemiddelde_Stress"];
   // echo "Gemiddelde stressniveau: " . $var_avg;
    
}


$query = "SELECT data 
FROM data 
WHERE thing_id = 1
ORDER BY id DESC
LIMIT 1";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error); 

while ($row = $result->fetch_assoc()){
    $var_recent = $row["data"];
   // echo "<br>";
  //  echo "Persoonlijk stressniveau: " . $var_recent;
    
}

if ($var_recent >= $var_avg){
    
    echo "! ! ! alarm ! ! !<br>";
} else {

    echo "Ik ben blij dat het goed met je gaat!<br>";
}


echo "Gemiddelde stressniveau: " . $var_avg;
echo "<br>";
echo "Persoonlijk stressniveau: " . $var_recent;


?>