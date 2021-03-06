/* Arduino Interface to the PSC05 X10 Receiver.                       BroHogan 3/24/09
 * SETUP: X10 PSC05/TW523 RJ11 to Arduino (timing for 60Hz)
 * - RJ11 pin 1 (BLK) -> Pin 2 (Interrupt 0) = Zero Crossing
 * - RJ11 pin 2 (RED) -> GND
 * - RJ11 pin 3 (GRN) -> Pin 4 = Arduino receive
 * - RJ11 pin 4 (YEL) -> Pin 5 = Arduino transmit (via X10 Lib)
 * NOTES:
 * - Must detach interrup when transmitting with X10 Lib 
 */

#include "WProgram.h"                  // this is needed to compile with Rel. 0013
#include <x10.h>                       // X10 lib is used for transmitting X10
#include <x10constants.h>              // X10 Lib constants

#define RPT_SEND 2 
#define ZCROSS_PIN     11               // BLK pin 1 of PSC05
#define RCVE_PIN       10               // GRN pin 3 of PSC05
#define TRANS_PIN      8               // YEL pin 4 of PSC05

#define LED_PIN        13              // for testing 
#define BUTTON         7

x10 SX10= x10(ZCROSS_PIN,TRANS_PIN,RCVE_PIN,LED_PIN);// set up a x10 library instance:
boolean lightsOn = false;
int val = 1;

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.print("x10 receive/send test");
  pinMode(BUTTON, INPUT);
  pinMode(ZCROSS_PIN, INPUT);
  pinMode(TRANS_PIN, OUTPUT);
  pinMode(RCVE_PIN, INPUT);
  
  SX10.write(HOUSE_A, UNIT_3,RPT_SEND);
  SX10.write(HOUSE_A, ON, RPT_SEND);
  Serial.print("Lights OFF");
  
}

// A simple test program that demonstrates integrated send/receive
// prints X10 input, then sets D5 on/off if unit code on input was 1
void loop()
{
  val = digitalRead(BUTTON);
  if (val == LOW) 
    { 
      //SX10.debug();
      if (lightsOn == false)
      {
        SX10.write(HOUSE_A, UNIT_3,RPT_SEND);
        SX10.write(HOUSE_A, ON, RPT_SEND);
        lightsOn = true;
        Serial.println("Lights ON");
      }
      
      else
      {
        SX10.write(HOUSE_A,UNIT_3,RPT_SEND);
        SX10.write(HOUSE_A,OFF,RPT_SEND);
        lightsOn = false;
        Serial.println("Lights OFF");
      }
    }
    
  SX10.debug();
} 



