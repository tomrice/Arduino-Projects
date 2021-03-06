#include <x10.h>
#include <x10constants.h>


// RFID reader
#define TAG_LEN 12
char tag[12] = {'0', 'F', '0', '3', '0', '3', '7', '1', '8', '5'};
char code[12];
//char prevCode[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int bytesread = 0; 
int ledPin = 13; // Connect LED to pin 13
int rfidPin = 2; // RFID enable pin connected to digital pin 2
int val=0; 

// X10 Control unit
int zcPin = 9;
int dataPin = 8;
int rxPin = 7;
int repeat = 1;
boolean LightsOn = false;

 
void setup()
{
  Serial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
  
  // X10 Module
  pinMode(zcPin,INPUT);
  pinMode(dataPin,OUTPUT);
  x10.begin(rxPin, dataPin, zcPin); // 9 is 0xing pin; 8 is data pin
 
  // RFID 
  pinMode(rfidPin,OUTPUT);   // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
  pinMode(ledPin,OUTPUT); // Set ledPin to output
  digitalWrite(rfidPin, LOW); // Activate the RFID reader
  
  blink();  // All variables are set, notify user ready to operate
  Serial.println("Setup complete, all lights OFF.");
}


void loop()
{
    if(Serial.available() > 0) 
    {	    // if data available from reader 
      if((val = Serial.read()) == 10) 
      {   // check for header 
	bytesread = 0; 
	while(bytesread<10) 
        {		  // read 10 digit code 
	  if( Serial.available() > 0) 
          { 
	    val = Serial.read(); 
	    if((val == 10)||(val == 13)) 
            { // if header or stop bytes before the 10 digit reading 
		break;			     // stop reading 
	    } 
	    code[bytesread] = val;	   // add the digit		
	    bytesread++;			 // ready to read next digit  
	  } 
	} 
	
        if(bytesread >= 10) 
        {		  // if 10 digit read is complete
            Serial.flush();
	    if(strcmp(code, tag) == 0) 
            {
	      Serial.print("Tag matches: ");
	      Serial.println(code);
              if (LightsOn == false)
              {
	        blink();
                x10.beginTransmission(L);
                x10.beginTransmission(UNIT_1);
                LightsOn = true;
                Serial.println("Lights ON.");
                x10.write(ON);
              }
           
             else
             {
	       blink();
               x10.beginTransmission(L);
               x10.beginTransmission(UNIT_1);
               LightsOn = false;
               Serial.println("Lights OFF.");
               x10.write(OFF);
             }
             
             digitalWrite(rfidPin, HIGH);
             delay(3000);
             Serial.flush();
             digitalWrite(rfidPin, LOW); 
	    }
    
	 
           else 
           {
	     Serial.print(code);
	     Serial.println(" does not match");
             digitalWrite(rfidPin, HIGH);
             delay(3000);
             Serial.flush();
             digitalWrite(rfidPin, LOW); 
	   }
           

        }

	bytesread = 0; 
	delay(500);			     // wait for a second 
    }
  }
}


/***************************
* Function: blink
****************************/
void blink()
{  
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}
