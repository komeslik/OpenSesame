#include"GarageHardware.h"

// TODO: Define any variables or constants here
const int onboardLED = D7;

const int redPin = A4;
const int greenPin = D0;
const int bluePin = D1;

const int button = D3;
const int closedSignal = D4;
const int openSignal = D5;
const int fault = D6;

/**
 * Setup the door hardware (all I/O should be configured here)
 *
 * This routine should be called only once from setup()
 */
void setupHardware() {
    // TODO: Setup your simulated hardware
    Serial.begin(9600);
    pinMode(onboardLED, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(button, INPUT_PULLUP);
    
    digitalWrite(onboardLED, LOW);
    
    if(isDoorFullyClosed()){
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
    }else if(isDoorFullyOpen()){
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);    
    }else{
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);  
    }
    
    
}


/**
 * Return true if the door open/close button is pressed
 *
 * Note: this is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if buttons is currently pressed, false otherwise
 */
bool isButtonPressed() {
  // TODO: Your code to simulate a button press.
  //       Use an actual button.
  return (!digitalRead(button)==1);
  return false;
}

/**
 * Return true if the door is fully closed
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is completely closed, false otherwise
 */
bool isDoorFullyClosed() {
  // TODO: Your code to simulate the closed switch
  //       Use a button, switch, or wired (connected to 3V or GND)
    bool result = digitalRead(closedSignal);
    // if(result){
    //     digitalWrite(redPin, HIGH);
    //     digitalWrite(greenPin, LOW);
    //     digitalWrite(bluePin, LOW);
    // }
  return result;
}

/**
 * Return true if the door has experienced a fault
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is has experienced a fault
 */
bool isFaultActive() {
  // TODO: Your code to simulate the fault
  //       Use a button, switch, or wired (connected to 3V or GND)
  return digitalRead(fault);
}

/**
 * Return true if the door is fully open
 *
 * Note: This is directly based on hardware.  No debouncing or
 *       other processing is performed.
 *
 * return  true if the door is completely open, false otherwise
 */
bool isDoorFullyOpen() {
  // TODO: Your code to simulate the opened switch
  //       Use a button, switch, or wired (connected to 3V or GND)
  bool result = digitalRead(openSignal);
//   if(result){
//     digitalWrite(redPin, LOW);
//     digitalWrite(greenPin, HIGH);
//     digitalWrite(bluePin, LOW);
//     }
    return result;
}

/**
 * This function will start the motor moving in a direction that opens the door.
 *
 * Note: This is a non-blocking function.  It will return immediately
 *       and the motor will continue to opperate until stopped or reversed.
 *
 * return void
 */
void startMotorOpening() {
  // TODO: Your code to simulate the motor opening
  //       Use an individual LED
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  
}

/**
 * This function will start the motor moving in a direction closes the door.
 *
 * Note: This is a non-blocking function.  It will return immediately
 *       and the motor will continue to opperate until stopped or reversed.
 *
 * return void
 */
void startMotorClosing() {
  // TODO: Your code to simulate the motor closing
  //       Use an individual LED
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
}

/**
 * This function will stop all motor movement.
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
void stopMotor() {
  // TODO: Your code to simulate the motor being stopped
  //       Should impact the opening/closing LEDs
    digitalWrite(bluePin, LOW);
    if(!isDoorFullyClosed()&&!isDoorFullyOpen()){
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, LOW);
    }else if(isDoorFullyOpen()){
        digitalWrite(redPin, LOW);
    }else if(isDoorFullyClosed()){
        digitalWrite(greenPin, LOW);
    }
    
}

/**
 * This function will control the state of the light on the opener.
 *
 * Parameter: on: true indicates the light should enter the "on" state;
 *                false indicates the light should enter the "off" state
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
void setLight(boolean on) {
  // TODO: Your code to simulate the light
  //       Use an individual LED
    digitalWrite(onboardLED, on);
}


/**
 * This function will control the state of the light on the opener.
 * (OPTIONAL:  This is only needed for the extra credit part of assignment 3)
 *
 * Parameter: cycle (0-100).  0 indicates completely Off, 100 indicates completely on.
 *            intermediate values are the duty cycle (as a percent)
 *
 * Note: This is a non-blocking function.  It will return immediately.
 *
 * return void
 */
void setLightPWM(int cyclePct) {
  // TODO: Your code to simulate the light
  //       Use an individual LED
}
