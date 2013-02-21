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

int Jbutton = 1023;
int upButton = 1;
int downButton = 1;
int rightButton = 1;
int leftButton = 1;


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
  Jbutton = Esplora.readJoystickSwitch();
  upButton = Esplora.readButton(SWITCH_UP);
  downButton = Esplora.readButton(SWITCH_DOWN);
  rightButton = Esplora.readButton(SWITCH_RIGHT);
  leftButton = Esplora.readButton(SWITCH_LEFT);
 
  // TRANSMIT SENSOR DATA TO PROCESSING
  // VIA SERIAL COMMUNICATIONS LINK
  Serial.print(Xvalue);
  Serial.print(",");
  Serial.print(Yvalue);
  Serial.print(",");
  Serial.print(Jbutton);
  Serial.print(",");
  Serial.print(upButton);
  Serial.print(",");
  Serial.print(downButton);
  Serial.print(",");
  Serial.print(rightButton);
  Serial.print(",");
  Serial.println(leftButton);
  
  // LET THINGS SETTLE
  delay(30);
}
