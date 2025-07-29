#include "zaruljice.h"
#include "../core/pins.h"

// Pin assignments for the UCN5821 shift register (270 Ω series resistors)

void inicijalizirajZaruljice() {
  pinMode(PIN_LED_DATA, OUTPUT);
  pinMode(PIN_LED_CLK, OUTPUT);
  pinMode(PIN_LED_LATCH, OUTPUT);
}

// Mapping from enum Tipka index to shift register output bit
// Indices 0-7 -> first UCN5821, 8-15 -> second, 16+ -> third
static const uint8_t LED_MAP[18] = {
  17, // IGRA_301         -> chip3 OUT2
  11, // IGRA_501         -> chip2 OUT4
   6, // IGRA_SHANGHAI    -> chip1 OUT7
   3, // IGRA_HANGMAN     -> chip1 OUT4
   4, // IGRA_ROULETTE    -> chip1 OUT5
   5, // IGRA_701         -> chip1 OUT6
   0, // IGRA_CRICKET     -> chip1 OUT1
   1, // IGRA_3INLINE     -> chip1 OUT2
   2, // IGRA_NEW_PLAYER  -> chip1 OUT3
   7, // IGRA_RESET       -> chip1 OUT8
  14, // IGRAC_1          -> chip2 OUT7
  10, // IGRAC_2          -> chip2 OUT3
   9, // IGRAC_3          -> chip2 OUT2
   8, // IGRAC_4          -> chip2 OUT1
  16, // IGRAC_5          -> chip3 OUT1
  15, // IGRAC_6          -> chip2 OUT8
  13, // OSTALO_OUT_TEAM  -> chip2 OUT6 (Double OUT)
  12  // OSTALO_IN_CUTTHROAT -> chip2 OUT5 (Double IN)
};

void postaviZaruljice(bool stanja[18]) {
  byte bajtovi[3] = {0};

  for (int i = 0; i < 18; i++) {
    if (stanja[i]) {
      uint8_t bit = LED_MAP[i];
      bajtovi[bit / 8] |= (1 << (7 - (bit % 8))); // MSB first
    }
  }

  digitalWrite(PIN_LED_LATCH, LOW);
  // Send bytes in reverse order so the last chip in the chain receives its
  // data first (Chip3 -> Chip2 -> Chip1)
  for (int i = 2; i >= 0; i--) {
    shiftOut(PIN_LED_DATA, PIN_LED_CLK, MSBFIRST, bajtovi[i]);
  }
  digitalWrite(PIN_LED_LATCH, HIGH);
}
