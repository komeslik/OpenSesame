var curUser;
var curDiv = "login";
var users = [new user("guest", "guest", "guest@gmail.com", "closed"), new user("dank", "123", "dank@dank.com", "open")];

var openTimeout;
var closeTimeout;
var timerTimeout1;
var timerTimeout2;
var timerTimeout3;

function show(divId) {
  if (divId == 'logout') { //Change links shown
    document.getElementById('isUser').style.display = 'none';
    document.getElementById('noUser').style.display = 'block';
    divId = 'login';
  }
  if (divId == 'controls' && curDiv == 'login') {
    document.getElementById('noUser').style.display = 'none';
    document.getElementById('isUser').style.display = 'block';
  }
  document.getElementById(curDiv).style.display = 'none';
  document.getElementById(divId).style.display = 'block';
  curDiv = divId;
}

function user(un, pass, email, door) {
  this.un = un;
  this.pass = pass;
  this.email = email;
  this.door = door;
  this.notifyClosed = false;
  this.notifyOpen = false;
  this.notifyOpenTooLong = false;
  this.howLong;
}

function login() {
  var userI = users.findIndex(function(e) {
    return e.un == document.getElementById('user').value;
  });
  if (userI >= 0 && users[userI].pass == document.getElementById('password').value) {
    alert("Success!");
    document.getElementById('user').value = "";
    document.getElementById('password').value = "";
    curUser = users[userI];
    show('controls');
    if (curUser.door == 'open') {
      var image = document.getElementById("door1");
      image.src = "garageOpen.svg";
      var image2 = document.getElementById("door2");
      image2.src = "garageOpen.svg";
      var image3 = document.getElementById("door3");
      image3.src = "garageOpen.svg";
    }
    if (curUser.door == 'closed') {
      var image = document.getElementById("door1");
      image.src = "garageClosed.svg";
      var image2 = document.getElementById("door2");
      image2.src = "garageClosed.svg";
      var image3 = document.getElementById("door3");
      image3.src = "garageClosed.svg";
    }
    document.getElementById('doorClosedNotification').checked = curUser.doorClosedNotification;
    document.getElementById('doorOpenNotification').checked = curUser.doorOpenNotification;
    document.getElementById('doorLeftOpenNotification').checked = curUser.notifyOpenTooLong;
    document.getElementById('howLong').value = curUser.howLong;
    notifyOpenTooLong();
  } else {
    alert("Invalid credentials.");
  }
}

function logout() {
  document.getElementById('howLong').value = "";
  curUser = null;
  show('logout');
}

function addUser() {
  var newUser = new user(document.getElementById('un').value, document.getElementById('pass').value, document.getElementById('email').value, "closed");
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

function recoverPass() {
  var userI = users.findIndex(function(e) {
    return e.un == document.getElementById('recUser').value;
  });
  if (userI >= 0) {
    alert("Password: " + users[userI].pass);
  } else {
    alert("User does not exist!");
  }
}

function doorToggle() {
  var image = document.getElementById("door1");
  var image2 = document.getElementById("door2");
  var image3 = document.getElementById("door3");
  if (curUser.door == "closed" || curUser.door == "closing") {
    clearTimeout(closeTimeout);
    clearTimeout(openTimeout);
    curUser.door = "opening";
    image.src = "upArrow.gif";
    image2.src = "upArrow.gif";
    image3.src = "upArrow.gif";
    openTimeout = setTimeout(openDoor, 5000);
  } else {
    clearTimeout(openTimeout);
    clearTimeout(closeTimeout);
    curUser.door = "closing";
    image.src = "downArrow.gif";
    image2.src = "downArrow.gif";
    image3.src = "downArrow.gif";
    closeTimeout = setTimeout(closeDoor, 5000);
  }
  notifyTimeout = setTimeout(notifyOpenTooLong, 5000);
}

function openDoor() {
  curUser.door = "open";
  var image = document.getElementById("door1");
  image.src = "garageOpen.svg";
  var image2 = document.getElementById("door2");
  image2.src = "garageOpen.svg";
  var image3 = document.getElementById("door3");
  image3.src = "garageOpen.svg";
  if (curUser.notifyOpen) {
    alert("Door1 open!!")
  }
}

function closeDoor() {
  curUser.door = "closed";
  var image = document.getElementById("door1");
  image.src = "garageClosed.svg";
  var image2 = document.getElementById("door2");
  image2.src = "garageClosed.svg";
  var image3 = document.getElementById("door3");
  image3.src = "garageClosed.svg";
  if (curUser.notifyClosed) {
    alert("Door1 closed!!")
  }
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
    var image2 = document.getElementById("door2");
    var image3 = document.getElementById("door3");
    timerTimeout1 = setTimeout(
      function() {
        clearTimeout(openTimeout);
        clearTimeout(closeTimeout);
        curUser.door = "closing";
        image.src = "downArrow.gif";
        image2.src = "downArrow.gif";
        image3.src = "downArrow.gif";
      }, closeTime * 60000 - 5000);
    timerTimeout2 = setTimeout(
      closeDoor, closeTime * 60000
    );
    timerTimeout3 = setTimeout(
      function() {
        document.getElementById("timerEnable").checked = false;
      }, closeTime * 60000 - 5000);
  }

}

function deactivateTimer() {
  clearTimeout(timerTimeout1);
  clearTimeout(timerTimeout2);
  clearTimeout(timerTimeout3);
}

function notifyWhenClosed() {
  curUser.notifyClosed = document.getElementById("doorClosedNotification").checked;
}

function notifyWhenOpen() {
  curUser.notifyOpen = document.getElementById("doorOpenNotification").checked;
}

function notifyOpenTooLong() {
  curUser.notifyOpenTooLong = document.getElementById("doorLeftOpenNotification").checked;
  if (curUser.notifyOpenTooLong && curUser.door == 'open') {
    var curDate = new Date().getTime();
    var howLong = document.getElementById("howLong").value;
    if (howLong < 0) {
      alert("Invalid Interval. Please check your interval.");
    } else {
      curUser.howLong = howLong;
      var deadline = curDate.valueOf() + curUser.howLong * 60000;
      tooLongInterval = setInterval(function() {
        var curDate2 = new Date().getTime();
        if (curDate2.valueOf() > deadline) {
          alert("Door is open for more than specified period!!");
          document.getElementById("doorLeftOpenNotification").checked = false;
          clearInterval(tooLongInterval);
        }
      }, 3000);
    }
  } else {
    clearInterval(tooLongInterval);
  }
}

document.getElementById("timerEnable").addEventListener("change", toggleTimer, false);
document.getElementById("doorOpenNotification").addEventListener("change", notifyWhenOpen, false);
document.getElementById("doorClosedNotification").addEventListener("change", notifyWhenClosed, false);
document.getElementById("doorLeftOpenNotification").addEventListener("change", notifyOpenTooLong, false);
