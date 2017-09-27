var openTimeout;
var closeTimeout;
var timerTimeout1;
var timerTimeout2;
var timerTimeout3;

var notifyClosed = false;
var notifyOpen = false;
var notifyOpenTooLong = false;

function doorToggle(){
    var image = document.getElementById("door1");
    if(image.src.match("garageClosed")||image.src.match("downArrow")){
        clearTimeout(closeTimeout);
        clearTimeout(openTimeout);
        image.src="upArrow.gif";
        openTimeout = setTimeout(openDoor, 5000);
    }else{
        clearTimeout(openTimeout);
        clearTimeout(closeTimeout);
        image.src = "downArrow.gif";
        closeTimeout = setTimeout(closeDoor, 5000);
    }
}
function openDoor(){
    var image = document.getElementById("door1");
    image.src = "garageOpen.svg";
    if(notifyOpen){
        alert("Door1 open!!")
    }
}
function closeDoor(){
    var image = document.getElementById("door1");
    image.src = "garageClosed.svg";
    if(notifyClosed){
        alert("Door1 closed!!")
    }
}

/////////////////////////////////////

function toggleTimer(){
    if(document.getElementById("timerEnable").checked){
        activateTimer();
    }else{
        deactivateTimer();
    }
}
function activateTimer(){
    var closeTime=document.getElementById("closeTime").value;
    if(closeTime<0) {
        alert("Invalid Door Close Time. Please check your timer.");       
    }else{
        var image = document.getElementById("door1");        
        timerTimeout1 = setTimeout(
            function(){
            clearTimeout(openTimeout);
            clearTimeout(closeTimeout);
            image.src = "downArrow.gif";
            }, closeTime*60000-5000 );
        timerTimeout2 = setTimeout(
            closeDoor, closeTime*60000
        );
        timerTimeout3 = setTimeout(
            function(){
                document.getElementById("timerEnable").checked = false; 
            }, closeTime*60000-5000 );            
    }

}
function deactivateTimer(){
    clearTimeout(timerTimeout1);
    clearTimeout(timerTimeout2);
    clearTimeout(timerTimeout3);
}
function notifyWhenClosed(){
    notifyClosed = document.getElementById("doorClosedNotification").checked;
}
function notifyWhenOpen(){
    notifyOpen = document.getElementById("doorOpenNotification").checked;
}
function notifyOpenTooLong(){
    notifyOpenTooLong = document.getElementById("doorLeftOpenNotification").checked;
}
document.getElementById("timerEnable").addEventListener("change", toggleTimer, false);
document.getElementById("doorOpenNotification").addEventListener("change", notifyWhenOpen, false);
document.getElementById("doorClosedNotification").addEventListener("change", notifyWhenClosed, false);
document.getElementById("doorLeftOpenNotification").addEventListener("change", notifyOpenTooLong, false);