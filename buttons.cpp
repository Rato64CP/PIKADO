#include "buttons.h"
#include <Arduino.h>

const uint8_t gumbi[] = {2, 3, 4, 5, 6, 7}; // tipke za 1–6 igrača

void inicijalizirajTipke() {
  for (uint8_t pin : gumbi) {
    pinMode(pin, INPUT_PULLUP);
  }
}

int provjeriOdabirIgraca() {
  for (uint8_t i = 0; i < sizeof(gumbi); i++) {
    if (digitalRead(gumbi[i]) == LOW) {
      delay(20); // debounce
      if (digitalRead(gumbi[i]) == LOW) return i + 1;
    }
  }
  return 0;
}