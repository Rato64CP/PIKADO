#include "zaruljice.h"
#include "../core/pins.h"

// Pin assignments for the UCN5821 shift register (270 Ω series resistors)

void inicijalizirajZaruljice() {
  pinMode(PIN_LED_DATA, OUTPUT);
  pinMode(PIN_LED_CLK, OUTPUT);
  pinMode(PIN_LED_LATCH, OUTPUT);
}

void postaviZaruljice(bool stanja[18]) {
  byte bajtovi[3] = {0};

  for (int i = 0; i < 18; i++) {
    if (stanja[i]) {
      bajtovi[i / 8] |= (1 << (7 - (i % 8))); // MSB first
    }
  }

  digitalWrite(PIN_LED_LATCH, LOW);
  for (int i = 0; i < 3; i++) {
    shiftOut(PIN_LED_DATA, PIN_LED_CLK, MSBFIRST, bajtovi[i]);
  }
  digitalWrite(PIN_LED_LATCH, HIGH);
}
