#include <Ethernet.h>
#include <SPI.h>

const int sensorPin = 5;
int sensorReading = 0;

byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x0D, 0x07, 0x94 };
byte ip[] = { 
  192, 168, 1, 200 };
byte server[] = {
  50, 62, 248, 1};    // Address for geekcowboy.net server

EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  sensorReading = analogRead(sensorPin);

  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET /php/LightSensorWriteToFile.php?brightness=");
    client.print(sensorReading, DEC);
    client.println(" HTTP/1.1");
    client.println("Host: geekcowboy.net");
    client.println();
  } 
  else {
    Serial.println("connection failed");
  }
}

void loop()
{
  char recvChar;
  if (Serial.available() > 0) {
    // read the incoming byte:
    recvChar = Serial.read();
    if (recvChar == 'R') {
      Serial.println("R Received");
      sensorReading = analogRead(sensorPin);
      if (client.connect(server, 80)) {
        Serial.println("connected");
        client.print("GET /php/LightSensorWriteToFile.php?brightness=");
        client.print(sensorReading, DEC);
        client.println(" HTTP/1.1");
        client.println("Host: geekcowboy.net");
        client.println();
      }
      else {
        Serial.println("connection failed");
      }
    }
  }

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    //Serial.println();
    //Serial.println("disconnecting.");
    client.stop();
  }
}


