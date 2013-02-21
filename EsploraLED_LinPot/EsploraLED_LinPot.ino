// include the Esplora library
#include <Esplora.h>

void setup() {
// nothing to setup
}

void loop() {
  // read the sensor into a variable
  int slider = Esplora.readSlider()/4;

  // convert the sensor readings to light levels
  byte bright  = slider/4;

  // write the light levels to the Red LED
  Esplora.writeRed(bright);

  // add a small delay to keep the LED from flickering:
  delay(10);
}
