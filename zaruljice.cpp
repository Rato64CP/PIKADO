#include "zaruljice.h"

// Prilagodi ove pinove prema stvarnom ožičenju
const int PIN_DATA = 5;
const int PIN_CLK  = 6;
const int PIN_LATCH = 7;

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