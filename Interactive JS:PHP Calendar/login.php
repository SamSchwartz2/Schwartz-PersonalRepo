<?php
require 'phpreq.php';
global $mysqli;
header("Content-Type: application/json");
session_start();
$stmt = $mysqli->prepare("SELECT COUNT(*), username, password1 FROM userInfo WHERE username=?");

$json_str = file_get_contents('php://input');

$json_obj = json_decode($json_str, true);

$stmt->bind_param('s', $user);
$user = $json_obj['username'];
$stmt->execute();

// Bind the results
$stmt->bind_result($cnt, $user_id, $pwd_hash);
$stmt->fetch();

$pwd_guess = $json_obj['password'];
// Compare the submitted password to the actual password hash

if($cnt == 1 && password_verify($pwd_guess, $pwd_hash)){
	// Login succeeded!
	$_SESSION["user_id"] = $user_id;
	$_SESSION['token'] = bin2hex(openssl_random_pseudo_bytes(32));
    echo json_encode(array(
		"success" => true,
        "id" => $user_id
	));
	exit;
} else{
    echo json_encode(array(
		"success" => false,
		"message" => "Incorrect Username or Password"
	));
	exit;
}
?>

