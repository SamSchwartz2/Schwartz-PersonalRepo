function showevents() {
    const user = document.getElementById("usery").value;
    const data = {'user': user}
    console.log(user);
    
    fetch("printevent.php", {
        method: "POST",
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })

    .then(response => response.json())
    .then(data => {if (data.success == true) {
        let title = date.title;
        let time = date.time;
        let month = date.month;
        let year = date.year;
        let event_id = data.eventid;
        for(i = 0; i< event_id.length; i++){
            document.getElementById("title")[i].innerHTML = title;
    }

        alert("Your events can be displayed");
    }
    else {
        alert("Your events cannot be displayed");
    }})

}    
document.getElementById("b7").addEventListener("click", showevents, false);

function addevent (event) {
    const title = document.getElementById("nameevent").value; 
    const year = document.getElementById("yearevent").value;
    const month = document.getElementById("monthevent").value; 
    const day = document.getElementById("dayevent").value; 
    const time = document.getElementById("timeevent").value; 

    const data = { 'title': title, 'year': year, 'month': month, 'day': day, 'time': time };

    console.log(title);
    console.log(year);
    console.log(month);
    console.log(day);
    console.log(time);
    console.log(data);

    fetch("addevent.php", {
        method: 'POST',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })
    .then(response => response.json())
    .then(data => {if (data.success == true) {
        alert("You have added in the event");
    }
    else {
        alert("You have not added in the event");
    }})
    .catch(err => console.error(err));
}
document.getElementById("b4").addEventListener("click", addevent, false);

function deleteevent(event) {
    const deleteevent = document.getElementById("deleteevent").value;
    const data = { 'deleteevent': deleteevent}

    console.log(deleteevent);
    console.log(data);

    fetch("deleteevent.php", {
        method: 'POST',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })
    .then(response => response.json())
    .then(data => {if (data.success == true) {
        alert("You have deleted the event");
    }
    else {
        alert("You have not deleted the event");
    }})
    .catch(err => console.error(err));
}

document.getElementById("b5").addEventListener("click", deleteevent, false);

function editevent(event) {
    console.log("we made it");

    const eventid = document.getElementById("eventid").value;
    const title = document.getElementById("nameedit").value; 
    const year = document.getElementById("yearedit").value;
    const month = document.getElementById("monthedit").value; 
    const day = document.getElementById("dayedit").value; 
    const time = document.getElementById("timeedit").value;

    const data = { 'eventid': eventid, 'title': title, 'year': year, 'month': month, 'day': day, 'time': time };

    console.log(eventid);
    console.log(title);
    console.log(year);
    console.log(month);
    console.log(day);
    console.log(time);
    console.log(data);

    fetch("editevent.php", {
        method: 'POST',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })
    .then(response => response.json())
    .then(data => {if (data.success == true) {
        alert("You have edited the event");
    }
    else {
        alert("You have not edited the event");
    }})
    .catch(err => console.error(err));
}
document.getElementById("b6").addEventListener("click", editevent, false);

function tagevent(event) {
    const eventid = document.getElementById("tagid").value;

    if (document.getElementById('school').checked) {
        var tag = "School";
    }
    else if (document.getElementById('work').checked) {
        var tag = "Work";
    }
    else if (document.getElementById('family').checked) {
        var tag = "Family";
    }
    else {
        var tag = "Other";
    }
    const data = { 'eventid': eventid, 'tag': tag};

    console.log(eventid);
    console.log(tag);
    console.log(data);
    fetch("tagevent.php", {
        method: 'POST',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })
    .then(response => response.json())
    .then(data => {if (data.success == true) {
        alert("You have tagged the event");
    }
    else {
        alert("You have not tagged the event");
    }})
    .catch(err => console.error(err));
}

document.getElementById("b8").addEventListener("click", tagevent, false);
