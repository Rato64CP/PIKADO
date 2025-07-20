#include "buttons.h"

const uint8_t pinoviTipki[BROJ_TIPKI] = {
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31,  // IGRA
  32, 33, 34, 35, 36, 37,                 // IGRACI
  38, 39                                  // OSTALO
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