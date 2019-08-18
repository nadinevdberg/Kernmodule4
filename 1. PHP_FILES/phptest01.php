<?php include "include.php";

//$query = "SELECT * FROM thing WHERE data > 20  ";
$query = "SELECT * FROM thing WHERE thing_id=1 LIMIT 1";

if (!($result = $mysqli->query($query)))
showerror($mysqli->errno,$mysqli->error);  

$row = $result->fetch_assoc();  


// uitvoeren zonder gebruik te maken van JSON
/*do {
echo $row["timestamp"] ."</br>". $row["data"]."<br />"."</br>";
} while ($row = $result->fetch_assoc());
?>*/

// geef mij als output een json array 
// deze kun je in je thing verder verwerken
echo json_encode($row); 

?>