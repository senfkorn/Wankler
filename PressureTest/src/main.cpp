#include <Arduino.h>

#define Filter 10

void setup() {
  Serial.begin(115200);
}

void loop() {

  float Sensor = 0;

  for(int i = 0; i < Filter; i++){
      Sensor += analogRead(0);
  }
  Sensor = Sensor / Filter;
  Serial.println(Sensor);

}