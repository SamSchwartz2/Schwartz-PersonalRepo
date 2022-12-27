function loginAjax(event) {
    const username = document.getElementById("usery").value; 
    const password = document.getElementById("pass").value; 

    const data = { 'username': username, 'password': password };
    console.log(username);
    console.log(password);
    console.log(data);
    fetch("login.php", {
            method: 'POST',
            body: JSON.stringify(data),
            headers: { 'content-type': 'application/json' }
        })
        .then(response => response.json())
        .then(data => {if (data.success == true) {
            alert("You have logged in");
        }
        else {s
            alert("You have not logged in");
        }})
        .catch(err => console.error(err));
}

document.getElementById("b1").addEventListener("click", loginAjax, false);

function registerAjax(event) {
    const newUser = document.getElementById("newUser").value;
    const newPass = document.getElementById("newPass").value;

    const data = { 'newUser': newUser, 'newPass': newPass };
    console.log(newUser);
    console.log(newPass);
    console.log(data);
    fetch("register.php", {
        method: 'post',
        body: JSON.stringify(data),
        headers: { 'content-type': 'application/json' }
    })
    .then(response => response.json())
    .then(data => {if (data.success == true) {
        console.log(data.id);
        alert("You have Registered");
    }
    else {
        alert("You did not Register");
    }})
    .catch(err => console.error(err));
    
}

document.getElementById("b2").addEventListener("click", registerAjax, false);

function logoutAjax() {
    fetch("logout.php", {
        method: 'post',  
        headers: { 'content-type': 'application/json' }
    }) 
    .then(response => response.json())
    .catch(err => console.error(err));
    alert("you have logged out")
}

document.getElementById("b3").addEventListener("click", logoutAjax, false);