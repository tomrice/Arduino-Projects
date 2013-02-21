// include the Esplora library
#include <Esplora.h>


void setup() {
  Serial.begin(9600);
}

void loop() {
  int bright = Esplora.readLightSensor()/8;
  delay(1000);
  int slider = Esplora.readSlider()/8;
  delay(1000);
  
  slider = 127 - slider;
  int RGBBright = slider + bright;
  Esplora.writeRGB(0, RGBBright, 0);
  
  if (slider == 0) {
    Esplora.noTone();
  }
  else {
    Esplora.tone(slider*10);
  }
  
  Serial.print("Amb Light: ");
  Serial.print(bright);
  Serial.print("    Slider: ");
  Serial.print(slider);
  Serial.print("    LED Bright: ");
  Serial.println(RGBBright);
}
