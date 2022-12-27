<!DOCTYPE html>
<html lang = "en"> 

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="stylesheet.css" />
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/js/bootstrap.bundle.min.js"></script>
    <!-- Code for bootstrap implementation taken from https://www.w3schools.com/bootstrap5/tryit.asp?filename=trybs_default&stacked=h-->
    <title> Calendar </title>
</head>
<body>
    <div class = "container mt-5">
        <div class = "row">
            <div class = "headBut" id = "prev">
                <input type = "button" class = "monthBut" value = "Previous Month" id = "prevMonth">
            </div>
            <div class = "heading">
                <h4 id = month class = date> Month </h4>
                <h4 id = year class = date > Year </h4>
            </div>
            <div class = "headBut" id = "next">
                <input type = "button" class = "monthBut" value = "Next Month" id = "nextMonth">
            </div>
        </div>
        <div class = "row" id = "week1">
            <div id = "sunday" class = "col-md-1">
                <p> sunday</p>
            </div>
            <div id = "monday" class = "col-md-1">
                <p> monday</p>
            </div>
            <div id = "tuesday" class = "col-md-1">
                <p> tuesday</p>
            </div>
            <div id = "wednesday" class = "col-md-1">
                <p> wednesday</p>
            </div>
            <div id = "thursday" class = "col-md-1">
                <p> thursday</p>
            </div>
            <div id = "friday" class = "col-md-1">
                <p> friday</p>
            </div>
            <div id = "saturday" class = "col-md-1">
                <p> saturday</p>
            </div>
        </div>

        <div class = "row" id = "week2">
            <div id = "sunday2" class = "col-md-1">
            </div>
            <div id = "monday2" class = "col-md-1">
            </div>
            <div id = "tuesday2" class = "col-md-1">
            </div>
            <div id = "wednesday2" class = "col-md-1">
            </div>
            <div id = "thursday2" class = "col-md-1">
            </div>
            <div id = "friday2" class = "col-md-1">
            </div>
            <div id = "saturday2" class = "col-md-1">
            </div>
        </div>
        <div class = "row" id = "week3">
            <div id = "sunday3" class = "col-md-1">
            </div>
            <div id = "monday3" class = "col-md-1">
            </div>
            <div id = "tuesday3" class = "col-md-1">
            </div>
            <div id = "wednesday3" class = "col-md-1">
            </div>
            <div id = "thursday3" class = "col-md-1">
            </div>
            <div id = "friday3" class = "col-md-1">
            </div>
            <div id = "saturday3" class = "col-md-1">
            </div>
        </div>
        <div class = "row" id = "week4">
            <div id = "sunday4" class = "col-md-1">
            </div>
            <div id = "monday4" class = "col-md-1">
            </div>
            <div id = "tuesday4" class = "col-md-1">
            </div>
            <div id = "wednesday4" class = "col-md-1">
            </div>
            <div id = "thursday4" class = "col-md-1">
            </div>
            <div id = "friday4" class = "col-md-1">
            </div>
            <div id = "saturday4" class = "col-md-1">
            </div>
        </div>
        <div class = "row" id = "week5">
            <div id = "sunday5" class = "col-md-1">
            </div>
            <div id = "monday5" class = "col-md-1">
            </div>
            <div id = "tuesday5" class = "col-md-1">
            </div>
            <div id = "wednesday5" class = "col-md-1">
            </div>
            <div id = "thursday5" class = "col-md-1">
            </div>
            <div id = "friday5" class = "col-md-1">
            </div>
            <div id = "saturday5" class = "col-md-1">
            </div>
        </div>
</div>
<script src = mainFile.js> </script>
<button class = "btn" id = "b7"> Display event </button><br><br>
<div class = "eventDisp">
        <output id = "title"> </output>
        <output id = "date"> </output>
        <output id = "time"> </output>
        <output id = "month"> </output>
        <output id = "year"> </output>
        <output id = "event_id"> </output>
</div>

<div class="events">
    Event:
    <input type="text" id="nameevent" name="nameevent"><br><br>
    Year:
    <input type = "number" id = "yearevent" name = "yearevent"><br><br>
    Month:
    <input type = "number" id = "monthevent" name = "monthevent"><br><br>
    Day:
    <input type = "number" id = "dayevent" name = "dayevent"><br><br>
    Time:
    <input type = "text" id = "timeevent" name = "dayevent"><br><br>
    <button class = "btn" id = "b4">Add Event</button><br><br>
</div>
<div class="deleteevent">
    Event:
    <input type="number" id="deleteevent" name="deleteevent"><br><br>
    <button class = "btn" id = "b5">Delete Event</button><br><br>
</div>
<div class="editevent">
    Event Number:
    <input type="number" id="eventid" name="eventid"><br><br>
    Event:
    <input type="text" id="nameedit" name="nameedit"><br><br>
    Year:
    <input type = "number" id = "yearedit" name = "yearedit"><br><br>
    Month:
    <input type = "number" id = "monthedit" name = "monthedit"><br><br>
    Day:
    <input type = "number" id = "dayedit" name = "dayedit"><br><br>
    Time:
    <input type = "text" id = "timeedit" name = "dayedit"><br><br>
    <button class = "btn" id = "b6">Edit Event</button><br><br>
</div>
<br><br>
<script src = event.js></script>
<h2>
    Log-in!
</h2>
<div>
    Username:
    <input type="text" id="usery" name="usery"><br><br>
    Password:
    <input type = "text" id = "pass" name = "pass"> <br><br>
    <button class = "btn" id = "b1">Log-In</button><br><br>
</div>
<h2>
    Register!
</h2>
<div>
    Enter a Username:
    <input type="text" id="newUser" name="newUser"><br><br>
    Enter a Password:
    <input type = "text" id = "newPass" name = "newPass"> <br><br>
    <button class = "btn" id = "b2">Register</button>
</div>

<div>
    <button class = "btn" id = "b3">Log-Out</button>
</div>

<script src = loginajax.js> </script>

</body>
</html>
