var openTimeout;
var closeTimeout;
var timerTimeout1;
var timerTimeout2;
var timerTimeout3;
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
}
function closeDoor(){
    var image = document.getElementById("door1");
    image.src = "garageClosed.svg";
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
document.getElementById("timerEnable").addEventListener("change", toggleTimer, false);