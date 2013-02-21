#include <x10.h>
#include <x10constants.h>


#define TAG_LEN 12

char tag[12] = {'0', 'F', '0', '3', '0', '3', '7', '1', '8', '5'};
char code[12]; 
int bytesread = 0; 
int ledPin = 13; // Connect LED to pin 13
int rfidEnablePin = 8; // RFID enable pin connected to digital pin 8
int val=0; 

// X10 Control unit
int zcPin = 2;
int dataPin = 4;
int rxPin = 3;
boolean LightsOn = false;

void setup() { 

Serial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
pinMode(rfidEnablePin,OUTPUT);   // Set digital pin 8 as OUTPUT to connect it to the RFID /ENABLE pin 
pinMode(ledPin,OUTPUT); // Set ledPin to output
digitalWrite(rfidEnablePin, LOW); // Activate the RFID reader 

pinMode(zcPin,INPUT);
pinMode(dataPin,OUTPUT);
x10.begin(rxPin, dataPin, zcPin); // 2 is 0xing pin; 4 is data pin
  
Serial.println("Initialization complete.");
blink(ledPin);
} 



 void loop() { 

  if(Serial.available() > 0) {	    // if data available from reader 
    if((val = Serial.read()) == 10) {   // check for header 
	bytesread = 0; 
	while(bytesread<10) {		  // read 10 digit code 
	  if( Serial.available() > 0) { 
	    val = Serial.read(); 
	    if((val == 10)||(val == 13)) { // if header or stop bytes before the 10 digit reading 
		break;			     // stop reading 
	    } 
	    code[bytesread] = val;	   // add the digit		
	    bytesread++;			 // ready to read next digit  
	  } 
	}
         digitalWrite(rfidEnablePin, HIGH); 
         Serial.flush();
         delay(7000);
         
	if(bytesread >= 10) {		  // if 10 digit read is complete 

	 if(strcmp(code, tag) == 0) {
	   Serial.print("Tag matches: ");
	   Serial.println(code);
           Serial.println("Hello, Michael.");
           if (LightsOn == false)
           {
              blink(ledPin);
              x10.beginTransmission(L);
              x10.write(UNIT_1);
              x10.write(ON);
              delay(500);
              x10.endTransmission();
              LightsOn = true;
              Serial.println("Lights ON.");
           }

           else  // Lights are off, so turn them ON
           {
              blink(ledPin);
              x10.beginTransmission(L);
              x10.write(UNIT_1);
              x10.write(OFF);
              delay(500);
              x10.endTransmission();
              LightsOn = false;
              Serial.println("Lights OFF.");
           }

	 }
	 else {
	   Serial.print(code);
	   Serial.println(" does not match");
	 }
	 
	} 
	bytesread = 0; 
	delay(500);			     // wait for a second 
        Serial.flush();
        digitalWrite(rfidEnablePin, LOW);
    } 
  } 
} 

void blink(int ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
}


 


