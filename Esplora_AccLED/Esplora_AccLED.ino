// include the Esplora library
#include <Esplora.h>


void setup() {
  Serial.begin(9600);
}

void loop() {
   int x_axis = Esplora.readAccelerometer(X_AXIS)/4;
   int y_axis = Esplora.readAccelerometer(Y_AXIS)/4;
   int z_axis = Esplora.readAccelerometer(Z_AXIS)/4;
   
   x_axis = abs(x_axis);
   y_axis = abs(y_axis);
   z_axis = abs(z_axis);
   
   Esplora.writeRGB(x_axis, y_axis, z_axis);

   Serial.print("x: ");
   Serial.print(x_axis);
   Serial.print("\ty: ");
   Serial.print(y_axis);
   Serial.print("\tz: ");
   Serial.println(z_axis);
 
   delay(500);
}
