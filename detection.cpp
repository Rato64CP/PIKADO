#include "detection.h"
#include "config.h"

// Struktura za metu
struct Meta {
  const char* naziv;
  uint8_t pinAktivan;
  uint8_t pinZajednicki;
};

// Definicija svih meta
const Meta mete[] = {
  // === Common 45 ===
  {"Triple 17", A3, COM_45}, {"Double 17", A10, COM_45}, {"Simple 17", A9, COM_45},
  {"Triple 3", A4, COM_45},  {"Double 3", A12, COM_45},  {"Simple 3", A11, COM_45},
  {"Triple 19", A5, COM_45}, {"Double 19", A14, COM_45}, {"Simple 19", A13, COM_45},
  {"Triple 7", A6, COM_45},  {"Double 7", 53, COM_45},   {"Simple 7", A15, COM_45},
  {"Triple 16", A7, COM_45}, {"Double 16", 49, COM_45},  {"Simple 16", 43, COM_45},

  // === Common 47 ===
  {"Triple 6", A4, COM_47},  {"Double 6", A12, COM_47},  {"Simple 6", A11, COM_47},
  {"Triple 10", A5, COM_47}, {"Double 10", A14, COM_47}, {"Simple 10", A13, COM_47},
  {"Triple 15", A6, COM_47}, {"Double 15", 53, COM_47},  {"Simple 15", A15, COM_47},
  {"Triple 2", A7, COM_47},  {"Double 2", 49, COM_47},   {"Simple 2", 43, COM_47},
  {"25 (Double)", A8, COM_47},
  {"Triple 13", A3, COM_47}, {"Double 13", A10, COM_47}, {"Simple 13", A9, COM_47},

  // === Common A1 ===
  {"Triple 8", A3, COM_A1},  {"Double 8", A10, COM_A1},  {"Simple 8", A9, COM_A1},
  {"Triple 14", A5, COM_A1}, {"Double 14", A14, COM_A1}, {"Simple 14", A13, COM_A1},
  {"Triple 9", A6, COM_A1},  {"Double 9", 53, COM_A1},   {"Simple 9", A15, COM_A1},
  {"Triple 11", A4, COM_A1}, {"Double 11", A12, COM_A1}, {"Simple 11", A11, COM_A1},
  {"Triple 12", A7, COM_A1}, {"Double 12", 49, COM_A1},  {"Simple 12", 43, COM_A1},

  // === Common A2 ===
  {"Triple 5", A3, COM_A2},  {"Double 5", A10, COM_A2},  {"Simple 5", A9, COM_A2},
  {"Triple 20", A4, COM_A2}, {"Double 20", A12, COM_A2}, {"Simple 20", A11, COM_A2},
  {"Triple 1", A5, COM_A2},  {"Double 1", A14, COM_A2},  {"Simple 1", A13, COM_A2},
  {"Triple 18", A6, COM_A2}, {"Double 18", 53, COM_A2},  {"Simple 18", A15, COM_A2},
  {"Triple 4", A7, COM_A2},  {"Double 4", 49, COM_A2},
  {"25 (Simple)", A8, COM_A2},
  {"Simple 4", 43, COM_A2}
};

void inicijalizirajMete() {
  for (const auto& meta : mete) {
    pinMode(meta.pinAktivan, INPUT_PULLUP);
    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }
  pinMode(PIN_MIKROFON, INPUT);
}

void skenirajMete() {
  for (const auto& meta : mete) {
    pinMode(meta.pinZajednicki, OUTPUT);
    digitalWrite(meta.pinZajednicki, LOW);
    pinMode(meta.pinAktivan, INPUT_PULLUP);

    if (digitalRead(meta.pinAktivan) == LOW) {
      // Delegiraj na aktivnu igru
      switch (aktivnaIgra) {
        case Igra_301:
          obradiPogodak_301(meta.naziv);
          break;
        // case Igra_501:
        //   obradiPogodak_501(meta.naziv);
        //   break;
        // case Igra_Shanghai:
        //   obradiPogodak_Shanghai(meta.naziv);
        //   break;
        default:
          Serial.println("Nepoznata igra!");
          break;
      }

      delay(300);  // debounce
      while (digitalRead(meta.pinAktivan) == LOW);
      delay(300);
    }

    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }
}

String detektirajZonu() {
  for (const auto& meta : mete) {
    pinMode(meta.pinZajednicki, OUTPUT);
    digitalWrite(meta.pinZajednicki, LOW);
    pinMode(meta.pinAktivan, INPUT_PULLUP);

    if (digitalRead(meta.pinAktivan) == LOW) {
      delay(300);  // debounce
      while (digitalRead(meta.pinAktivan) == LOW)
        ;
      delay(300);
      pinMode(meta.pinZajednicki, INPUT_PULLUP);
      return String(meta.naziv);
    }

    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }

  return String("");
}

void detektirajPromasaj() {
  int vrijednost = analogRead(PIN_MIKROFON);
  if (vrijednost > THRESHOLD_PROMASAJ) {
    Serial.println("Promašaj detektiran!");
    delay(500);
  }
}
