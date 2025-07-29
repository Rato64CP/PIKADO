#include "zaruljice.h"

// Prilagodi ove pinove prema stvarnom ozicenju
// Pin assignments for the UCN5821 shift register (270 Ω series resistors)
const int PIN_DATA = 2;
const int PIN_CLK  = 3;
const int PIN_LATCH = 4;

void inicijalizirajZaruljice() {
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
}

void postaviZaruljice(bool stanja[18]) {
  byte bajtovi[3] = {0};

  for (int i = 0; i < 18; i++) {
    if (stanja[i]) {
      bajtovi[i / 8] |= (1 << (7 - (i % 8))); // MSB first
    }
  }

  digitalWrite(PIN_LATCH, LOW);
  for (int i = 0; i < 3; i++) {
    shiftOut(PIN_DATA, PIN_CLK, MSBFIRST, bajtovi[i]);
  }
  digitalWrite(PIN_LATCH, HIGH);
}
