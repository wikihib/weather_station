<?php
$conn = mysqli_connect("localhost", "root", "", "nazwa_bazy");

$temp = $_POST['temp'];
$wilg = $_POST['wilg'];
$uv   = $_POST['uv'];
$cisn = $_POST['cisn'];

$stmt = mysqli_prepare(
    $conn,
    "INSERT INTO data (date, temp, press, hum, uv) VALUES (NOW(), ?, ?, ?, ?)"
);

mysqli_stmt_bind_param($stmt, "dddd", $temp, $cisn, $wilg, $uv);
mysqli_stmt_execute($stmt);

