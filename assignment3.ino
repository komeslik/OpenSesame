// This #include statement was automatically added by the Particle IDE.
#include "GarageHardware.h"
#include"GarageHardware.h"

SYSTEM_THREAD(ENABLED)

long deltaTime = 0;
long lastReleased = 0;
bool pressed = false;
long lastOpened = 0;
long lastNoFault = 0;
bool fault = false;
bool remotePressed = false;

int waitTime=1000;

Timer closeTimer(waitTime, timerToggle, true);

typedef enum {
        Open = 0,
        Closed,
        Closing,
        Opening,
        WaitOpening,
        WaitClosing
    } State;
    
State currentState;

State nextState(State state){
  switch(state){
    case Open:
        // digitalWrite(redPin, LOW);
        // digitalWrite(greenPin, HIGH);
        // digitalWrite(bluePin, LOW);
    
        if(isButtonPressed() && millis()-lastReleased>100 && !pressed){
            pressed = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            startMotorClosing();
            state = Closing;
            Particle.publish("myDoorState", "Closing", 60, PRIVATE);
            Particle.variable("initialState", "Closing");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            startMotorClosing();
            state = Closing;
            Particle.publish("myDoorState", "Closing", 60, PRIVATE);
            Particle.variable("initialState", "Closing");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
    case Closed:
        if(isButtonPressed() && millis()-lastReleased>100 && !pressed){
            pressed = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
                
            startMotorOpening();
            state = Opening; 
            Particle.publish("myDoorState", "Opening", 60, PRIVATE);
            Particle.variable("initialState", "Opening");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            
            startMotorOpening();
            state = Opening; 
            Particle.publish("myDoorState", "Opening", 60, PRIVATE);
            Particle.variable("initialState", "Opening");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
    case Closing:
        if((isButtonPressed() && millis()-lastReleased>100 && !pressed) || (isFaultActive() && millis()-lastNoFault>100 && !fault)){
            pressed = true;
            fault = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
                
            stopMotor();
            state=WaitClosing;
            Particle.publish("myDoorState", "WaitClosing", 60, PRIVATE);
            Particle.variable("initialState", "WaitClosing");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            Serial.println("stop"); 
            stopMotor();
            state=WaitClosing;
            Particle.publish("myDoorState", "WaitClosing", 60, PRIVATE);
            Particle.variable("initialState", "WaitClosing");
            break;
        }
        if(isDoorFullyClosed()){
            Serial.println("stop"); 
            stopMotor();
            state = Closed;
            Particle.publish("myDoorState", "Closed", 60, PRIVATE);
            Particle.variable("initialState", "Closed");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
    case Opening:
        if((isButtonPressed() && millis()-lastReleased>100 && !pressed) || (isFaultActive() && millis()-lastNoFault>100 && !fault)){
            pressed = true;
            fault = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            Serial.println("stop"); 
            stopMotor();
            state=WaitOpening;
            Particle.publish("myDoorState", "WaitOpening", 60, PRIVATE);
            Particle.variable("initialState", "WaitOpening");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            Serial.println("stop"); 
            stopMotor();
            state=WaitOpening;
            Particle.publish("myDoorState", "WaitOpening", 60, PRIVATE);
            Particle.variable("initialState", "WaitOpening");
            break;
        }
        if(isDoorFullyOpen()){
            lastOpened=millis();
            Serial.println("stop"); 
            stopMotor();
            state = Open;
            Particle.publish("myDoorState", "Open", 60, PRIVATE);
            Particle.variable("initialState", "Open");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
    case WaitOpening:
        if(isButtonPressed() && millis()-lastReleased>100 && !pressed){
            pressed = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
                
            startMotorClosing();
            state = Closing; 
            Particle.publish("myDoorState", "Closing", 60, PRIVATE);
            Particle.variable("initialState", "Closing");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            
            startMotorClosing();
            state = Closing; 
            Particle.publish("myDoorState", "Closing", 60, PRIVATE);
            Particle.variable("initialState", "Closing");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
    case WaitClosing:
        if(isButtonPressed() && millis()-lastReleased>100 && !pressed){
            pressed = true;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
                
            startMotorOpening();
            state = Opening;
            Particle.publish("myDoorState", "Opening", 60, PRIVATE);
            Particle.variable("initialState", "Opening");
            break;
        }
        if(remotePressed){
            remotePressed = false;
            Serial.print("current time:");
            Serial.println(millis());
            Serial.print("last released at:");
            Serial.println(lastReleased);
            
            startMotorOpening();
            state = Opening;
            Particle.publish("myDoorState", "Opening", 60, PRIVATE);
            Particle.variable("initialState", "Opening");
            break;
        }
        if(!isButtonPressed()){
            pressed = false;
            lastReleased = millis();
        }
        if(!isFaultActive()){
            fault = false;
            lastNoFault = millis();
        }
        break;
  }
  return state;
}

void setup()
{
    Particle.function("doorToggle", doorToggle);
    Particle.subscribe("myDoorState", myHandler, MY_DEVICES);
    Particle.subscribe("remoteButton", doorButtonHandler, MY_DEVICES);
    Particle.subscribe("timeout", timeoutHandler, MY_DEVICES);

    
    if(isDoorFullyClosed()){
        Particle.variable("initialState", "Closed");
        currentState = Closed;
    }else if(isDoorFullyOpen()){
        Particle.variable("initialState", "Open");
        currentState = Open;    
    }else{
        Particle.variable("initialState", "WaitOpening");
        currentState = WaitOpening;
    }

    setupHardware();
}

void loop()
{
  // Nothing to do here
  //Serial.println(isButtonPressed());
//   if (isButtonPressed()){
//       startMotorOpening();
//   }
    if(isFaultActive()){
        setLight(true);
    }else if((currentState==Open || currentState==Closed) && millis()-lastOpened>5000){
        setLight(false);
    }else{
       setLight(true);
    }
  
    if(!isButtonPressed()){
          lastReleased = millis();
    }
  //Serial.println(digitalRead(onboardLED));
  currentState = nextState(currentState);
  //Serial.println(currentState);
}

int doorToggle(String command) {
    if (command=="open" && currentState == Closed) {
        startMotorOpening();
        currentState = Opening;
        return 1; 
    } 
    else if (command=="close" && currentState == Open) {
        startMotorClosing();
        currentState = Closing;
        return 0;
  }
  else { 
    return -1;
  }
}

void myHandler(const char *event, const char *data)
{
  Serial.print(event);
  Serial.print(", data: ");
  if (data){
    if(strcmp(data,"Open")==0){
        isDoorFullyOpen();
        currentState = Open;
        Particle.variable("initialState", "Open");
        Serial.println(data);
    } 
    if(strcmp(data,"Closed")==0){
        isDoorFullyClosed();
        currentState = Closed;
        Particle.variable("initialState", "Closed");
        Serial.println(data);
    }
    if(strcmp(data,"Closing")==0) {
        startMotorClosing();
        currentState = Closing;
        Particle.variable("initialState", "Closing");
        Serial.println(data);
    }
    if(strcmp(data,"Opening")==0){
        startMotorOpening();
        currentState = Opening;
        Particle.variable("initialState", "Opening");
        Serial.println(data);
    }
    if(strcmp(data,"WaitOpening")==0){
        Serial.println("stop"); 
        stopMotor();
        currentState = WaitOpening;
        Particle.variable("initialState", "WaitOpening");
        Serial.println(data);
    }
    if(strcmp(data,"WaitClosing")==0){
        Serial.println("stop"); 
        stopMotor();
        currentState = WaitClosing;
        Particle.variable("initialState", "WaitClosing");
        Serial.println(data);
    }
  }
  else
    Serial.println("NULL");
}

void doorButtonHandler(const char *event, const char *data)
{
    Serial.println("remotePress");
    if(strcmp(data, "true")==0){
        remotePressed = true;    
    }
}

void timeoutHandler(const char *event, const char *data)
{
    Serial.println(data);
    String timestr(data);
    waitTime = timestr.toInt();
    Serial.println(waitTime);
    if(waitTime<0){
        closeTimer.stop();
    }else{
        closeTimer.changePeriod(waitTime);
        closeTimer.start();
    }
}

void timerToggle(){
    Serial.println("timer starts now");
    if(isDoorFullyOpen()){
        startMotorClosing();
        currentState = Closing;
        Particle.publish("myDoorState", "Closing", 60, PRIVATE);
        Particle.variable("initialState", "Closing");
    }
} 
    
    
    
    
    