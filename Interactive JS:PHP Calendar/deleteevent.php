<?php
    require 'phpreq.php';
    global $mysqli;
    header("Content-Type: application/json");
    session_start();

    $json_str = file_get_contents('php://input');

    $json_obj = json_decode($json_str, true);

    $deleteevent = $json_obj['deleteevent'];

    $stmt = $mysqli->prepare("DELETE FROM events WHERE event_id=?");
    if(!$stmt){
        printf("Query Prep Failed: %s\n", $mysqli->error);
        exit;
    }
    $stmt->bind_param('i',$deleteevent);
    if(!$stmt->execute()){
        echo json_encode(array(
            "success" => false,
            "message" => "Did not add Event"
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

