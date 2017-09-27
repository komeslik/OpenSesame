var curDiv = "login";
var users = [new user("guest", "guest"), new user("dank", "123")];
var openTimeout;
var closeTimeout;

function show(divId) {
  if(divId == 'logout'){ //Change links shown
    document.getElementById('isUser').style.display = 'none';
    document.getElementById('noUser').style.display = 'block';
    divId = 'login';
  } if (divId == 'controls' && curDiv == 'login'){
    document.getElementById('noUser').style.display = 'none';
    document.getElementById('isUser').style.display = 'block';
  }
  document.getElementById(curDiv).style.display = 'none';
  document.getElementById(divId).style.display = 'block';
  curDiv = divId;
}

function user(un, pass, email) {
  this.un = un;
  this.pass = pass;
  this.email = email;
}

function login() {
  var userI = users.findIndex(function(e) {
    return e.un == document.getElementById('user').value;
  });
  if (userI >= 0 && users[userI].pass == document.getElementById('password').value) {
    alert("Success!");
    document.getElementById('user').value = "";
    document.getElementById('password').value = "";
    show('controls');
  } else {
    alert("Invalid credentials.");
  }
}

function addUser() {
  var newUser = new user(document.getElementById('un').value, document.getElementById('pass').value, document.getElementById('email').value);
  if (users.some(function(e) {
      return e.un == newUser.un;
    })) {
    alert("Username already exists.");
  } else if (newUser.pass != document.getElementById('pass2').value) {
    alert("Passwords don't match!");
  } else {
    users.push(newUser);
    alert("Created new user");
    document.getElementById('email').value = "";
    document.getElementById('un').value = "";
    document.getElementById('pass').value = "";
    document.getElementById('pass2').value = "";
    show('login');
  }
}

function doorToggle() {
  var image = document.getElementById("door1");
  if (image.src.match("garageClosed") || image.src.match("downArrow")) {
    clearTimeout(closeTimeout);
    clearTimeout(openTimeout);
    image.src = "upArrow.gif";
    openTimeout = setTimeout(openDoor, 5000);
  } else {
    clearTimeout(openTimeout);
    clearTimeout(closeTimeout);
    image.src = "downArrow.gif";
    closeTimeout = setTimeout(closeDoor, 5000);
  }
}

function openDoor() {
  var image = document.getElementById("door1");
  image.src = "garageOpen.svg";
}

function closeDoor() {
  var image = document.getElementById("door1");
  image.src = "garageClosed.svg";
}

/////////////////////////////////////

function toggleTimer() {
  if (document.getElementById("timerEnable").checked) {
    activateTimer();
  } else {
    deactivateTimer();
  }
}

function activateTimer() {
  var closeTime = document.getElementById("closeTime").value;
  if (closeTime < 0) {
    alert("Invalid Door Close Time. Please check your timer.");
  } else {
    var image = document.getElementById("door1");
    setTimeout(
      function() {
        clearTimeout(openTimeout);
        clearTimeout(closeTimeout);
        image.src = "downArrow.gif";
      }, closeTime * 60000 - 5000);
    closeTimeout = setTimeout(closeDoor, closeTime * 60000);
  }

}

function deactivateTimer() {}
document.getElementById("timerEnable").addEventListener("change", toggleTimer, false);
