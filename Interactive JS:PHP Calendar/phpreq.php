<?php
$mysqli = new mysqli("localhost", "root", "8501415076", "mod5");

if($mysqli -> connect_errno){
    printf("Connection Failed: %s\n", $mysqli->connect_error);
    exit;
}
?>