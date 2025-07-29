#include "buttons.h"
#include "../core/pins.h"

// Pins 20 (SDA) and 21 (SCL) moraju ostati slobodni za I2C (LCD)
// Novi raspored tipki nakon prilagodbe ploce
static const uint8_t* const pinoviTipki = PIN_TIPKE;

bool stanjaTipki[BROJ_TIPKI];

void inicijalizirajTipke() {
  for (int i = 0; i < BROJ_TIPKI; i++) {
    pinMode(pinoviTipki[i], INPUT_PULLUP);  // ako koristis tipke na masu
    stanjaTipki[i] = false;
  }
}

void ocitajTipke() {
  for (int i = 0; i < BROJ_TIPKI; i++) {
    bool trenutno = digitalRead(pinoviTipki[i]) == LOW;  // LOW znaci stisnuta
    stanjaTipki[i] = trenutno;
  }
}

bool tipkaStisnuta(int indeks) {
  if (indeks < 0 || indeks >= BROJ_TIPKI) return false;
  return stanjaTipki[indeks];
}
