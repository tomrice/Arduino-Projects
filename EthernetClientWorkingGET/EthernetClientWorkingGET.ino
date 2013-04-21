#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x07, 0x94 };
byte ip[] = { 192, 168, 1, 200 };
byte server[] = {50, 62, 248, 1};    // Address for geekcowboy.net server

EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /php/test.php?age=23 HTTP/1.1");
    client.println("Host: geekcowboy.net");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}
