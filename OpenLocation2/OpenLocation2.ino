/*
Title:   Open Location
Based on SeeedStudio Bluetooth module wwritten by Steve Chang.
and the LiquidTWI library by FalconFour of Adafruit Forums
*/
 
#include <SoftwareSerial.h>   //Software Serial Port
#include <Wire.h>
#include <LiquidTWI.h>
#include <Servo.h>

#define RxD 6
#define TxD 7
#define OutPin 13
#define ServoLock 90
#define ServoUnlock 5
#define DEBUG_ENABLED  1

boolean LockStatus = true;

SoftwareSerial blueToothSerial(RxD,TxD);
LiquidTWI lcd(0);
Servo myServo;
 
 
void setup() 
{ 
  lcd.begin(40, 4);
  lcd.print("Open Location v1.1");
  lcd.setCursor(0, 1);
  lcd.print("Searching for BT...");
  //Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(OutPin, OUTPUT);
  digitalWrite(OutPin, LOW);
  myServo.attach(9);
  myServo.write(ServoLock);
  delay(150);
  setupBlueToothConnection();
  
} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      //Serial.print(recvChar);
      
      if (recvChar == 'A') {
        if (LockStatus == false) {
          digitalWrite(OutPin, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Open Location v1.1");
          lcd.setCursor(0, 1);
          lcd.print("Box is Locked");
          lcd.setBacklight(0);
          myServo.write(ServoLock);
          delay(150);
          LockStatus = true;
          lcd.setBacklight(1);
        }
      }
      
      else if (recvChar == 'B') {
        if (LockStatus == true) {
          digitalWrite(OutPin, HIGH);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Open Location v1.1");
          lcd.setCursor(0, 1);
          lcd.print("Box is Unlocked");
          lcd.setBacklight(0);
          myServo.write(ServoUnlock);
          delay(15);
          LockStatus = false;
          lcd.setBacklight(1);
        }
      }
    }
    
    /*if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
      recvChar  = Serial.read();
      blueToothSerial.print(recvChar);
    }*/
  }
} 
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  //Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush(); 
}




