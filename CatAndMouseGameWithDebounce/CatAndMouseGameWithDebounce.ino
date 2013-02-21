//////////////////////////////////////////////
// CAT AND MOUSE GAME
// Author: Mike Parks
//
//////////////////////////////////////////////

// INCLUDE LIBRARIES
#include <Esplora.h>

// DECLARE GLOBAL VARIABLES
int Xvalue = 0;
int Yvalue = 0;

int JbuttonStatus = 1023;
int upButtonStatus = 1;
int downButtonStatus = 1;
int rightButtonStatus = 1;
int leftButtonStatus = 1;

// FOR DEBOUNCING INPUTS
unsigned long ButtonTime[4] = {0,0,0,0};    //DOWN = 0, LEFT = 1, UP = 2, RIGHT = 3
unsigned long ButtonTime_Last[4] = {0,0,0,0}; 
unsigned long debounceTime = 175;



//
// SETUP ROUTINE
//
void setup(){
  Serial.begin(9600);
} 


//
// MAIN LOOP
//
void loop()
{
  // READ SENSORS  
  Xvalue = Esplora.readJoystickX();
  Yvalue = Esplora.readJoystickY();
  downButtonStatus = checkButtonStatus(SWITCH_DOWN, 0);
  leftButtonStatus = checkButtonStatus(SWITCH_LEFT, 1);
  upButtonStatus = checkButtonStatus(SWITCH_UP, 2);
  rightButtonStatus = checkButtonStatus(SWITCH_RIGHT, 3);
  JbuttonStatus = Esplora.readJoystickSwitch();
  
 
  // TRANSMIT SENSOR DATA TO PROCESSING
  // VIA SERIAL COMMUNICATIONS LINK
  Serial.print(Xvalue);
  Serial.print(",");
  Serial.print(Yvalue);
  Serial.print(",");
  Serial.print(JbuttonStatus);
  Serial.print(",");
  Serial.print(upButtonStatus);
  Serial.print(",");
  Serial.print(downButtonStatus);
  Serial.print(",");
  Serial.print(rightButtonStatus);
  Serial.print(",");
  Serial.println(leftButtonStatus);
  
  // LET THINGS SETTLE
  delay(30);
}



//
//  READ AND DEBOUNCE THE Up, DOWN, LEFT, RIGHT BUTTONS
//
int checkButtonStatus(int buttonID, int arrayID) {
  int buttonStatus = Esplora.readButton(buttonID);
  if (buttonStatus == 0) {
    ButtonTime[arrayID] = millis();
    if (ButtonTime[arrayID] - ButtonTime_Last[arrayID] > debounceTime) {
      ButtonTime_Last[arrayID] = ButtonTime[arrayID];
      return buttonStatus;

    }
    else {
      return 1;
    }
  }
  else {
    return 1;
  }
}
