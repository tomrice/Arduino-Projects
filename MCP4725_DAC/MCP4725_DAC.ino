#include <Wire.h>
#include <Serial.h>

byte ON = 255; // All bits high will give maximum output, Vcc, which is 5V.
byte OFF = 0; // All bits low will give minimum output, GND, which is 0V.
byte Program = 64; // See below for more details, but this sets the DAC register to receive new data
byte Device = 96; // This hardwired into the IC and the BoB, in other words, it is a given.


void setup() {
  Wire.begin();
  Serial.begin(9600);
}



void loop() {
  Wire.beginTransmission(Device);
  Wire.write(Program);
  Wire.write(ON);
  Wire.write(ON); // Needed twice, since the 4 lowest bits (of 12) are in the fourth byte
  Wire.endTransmission();

  delay(30);
  Serial.println("on");
  
  Wire.beginTransmission(Device);
  Wire.write(Program);
  Wire.write(OFF);
  Wire.write(OFF); // Needed twice, since the 4 lowest bits (of 12) are in the fourth byte
  Wire.endTransmission();

  delay(10);
  Serial.println("off");
}

