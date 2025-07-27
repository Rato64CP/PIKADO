#include "buttons.h"

// Pins 20 (SDA) and 21 (SCL) moraju ostati slobodni za I2C (LCD)
// Novi raspored tipki nakon prilagodbe ploče
const uint8_t pinoviTipki[BROJ_TIPKI] = {
  36, 34, 30, 40, 28, 38, 32, 42, 46, 44,  // IGRA / OPCIJE
  37, 35, 33, 31, 29, 27,                 // IGRACI
  50, 52                                   // PRAVILA (Double OUT / IN)
};

bool stanjaTipki[BROJ_TIPKI];

void inicijalizirajTipke() {
  for (int i = 0; i < BROJ_TIPKI; i++) {
    pinMode(pinoviTipki[i], INPUT_PULLUP);  // ako koristiš tipke na masu
    stanjaTipki[i] = false;
  }
}

void ocitajTipke() {
  for (int i = 0; i < BROJ_TIPKI; i++) {
    bool trenutno = digitalRead(pinoviTipki[i]) == LOW;  // LOW znači stisnuta
    stanjaTipki[i] = trenutno;
  }
}

bool tipkaStisnuta(int indeks) {
  if (indeks < 0 || indeks >= BROJ_TIPKI) return false;
  return stanjaTipki[indeks];
}
