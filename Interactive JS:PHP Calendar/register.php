<?php
    require 'phpreq.php';
    global $mysqli;
    header("Content-Type: application/json");
    session_start();

    $json_str = file_get_contents('php://input');

    $json_obj = json_decode($json_str, true);

    $newUser = $json_obj['newUser'];
    $newPass= $json_obj['newPass'];
    $phash = password_hash($newPass, PASSWORD_DEFAULT);
    // $stmt = $mysqli->prepare("select username from userInfo");
    // if(!$stmt){
    //     printf("Query Prep Failed: %s\n", $mysqli->error);
    //     exit;
    // }
    // $stmt->execute();
    // $stmt->bind_result($username);
    // while($stmt->fetch()){
    //     if($username === $newUser){
    //         echo json_encode(array(
	// 	    "success" => false,
	// 	    "message" => "User already registered"
	//         ));
    //         exit;
    //     }
    // }
    
    $stmt2 = $mysqli->prepare("insert into userInfo (username, password1) values (?,?)");
    if(!$stmt2){
        printf("Query Prep Failed: %s\n", $mysqli->error);
        exit;
    }
    $stmt2->bind_param('ss', $newUser, $phash);
    if(!$stmt2->execute()){
        echo json_encode(array(
            "success" => false,
            "message" => "Username already taken"
        ));
        exit;
    }else{
        echo json_encode(array(
            "success" => true
        ));
        exit;
    }
    exit;
?>