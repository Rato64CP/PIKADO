#include "config.h"
#include "detection.h"

void setup() {
  Serial.begin(9600);
  inicijalizirajMete();
}

void loop() {
  skenirajMete();
  detektirajPromasaj();
  delay(10);  // mala pauza da rastereti petlju
}