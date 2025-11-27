<?php
$conn = mysqli_connect("localhost", "root", "", "nazwa bazy");

//cisnienie mi nie dziala za dobrze wiec nie ma null
$temp = $_POST['temp'] ?? null;
$wilg = $_POST['wilg'] ?? null;
$uv = $_POST['uv'] ?? null;
$cisn = $_POST['cisn'] ?? "NULL";

if ($temp === null || $wilg === null) {
    var_dump($_POST);
    die("Brak podstawowych danych");
}

//trzeba dostosowac pod swoja baze
$sql = "INSERT INTO data (date, temp, press, hum, uv) 
        VALUES (NOW(), $temp, $cisn, $wilg, $uv)";
        
mysqli_query($conn, $sql);

echo "OK";
