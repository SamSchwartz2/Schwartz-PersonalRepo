<?php 
require 'phpreq.php';
global $mysqli;
header("Content-Type: application/json");
session_start();
$json_str = file_get_contents('php://input');
$json_obj = json_decode($json_str, true);
$username = $_SESSION["user_id"];
$stmt = $mysqli->prepare("select title, date, time, month, year, endtime, tag, event_id from events where username = ?");
if (!$username) {
    echo json_encode(array(
        "success" => false,
        "error" => 'security check failed'
    ));
    exit;
}else{
    if(!$stmt){
        // printf("Query Prep Failed: %s\n", $mysqli->error);
        // exit;
        echo json_encode(array(
            "success" => false,
            "error" => '$mysqli->error'
        ));
        exit;
    }
    $stmt->bind_param('s', $username);
    $stmt->execute();
    $stmt->bind_result($username, $title, $date, $time, $month, $year, $endtime, $tag, $event_id);
    // if(!$stmt->execute()){
    //     echo json_encode(array(
    //         "success" => false,
    //         "message" => "Can Not show this user's events"
    //     ));
    //     exit;
    // }else{
        while($stmt->fetch()){
            $title = htmlentities($title);
            $date = htmlentities($date);
            $time = htmlentities($time);
            $month = htmlentities($month);
            $year = htmlentities($year);
            $endtime = htmlentites($endtime);
            $tag = htmlentities($tag);
            $event_id = htmlentites($event_id);
        }
    $stmt->close();
            echo json_encode(array(
            "success" => true,
            // "title" => $title,
            // "date" => $date,
            // "time" => $time,
            // "month" => $month,
            // "year" => $year,
            // "endtime" => $endtime,
            // "tag" => $tag,
            // "event_id" => $event_id,
        ));
        exit;
    }

    ?>
