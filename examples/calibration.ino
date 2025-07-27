#include <Arduino.h>
#include "src/core/config.h"

struct Meta {
  const char* naziv;
  uint8_t pinAktivan;
  uint8_t pinZajednicki;
};

const Meta mete[] = {
  // === Common A15 ===
  {"Triple 17", A7, COM_A15}, {"Double 17", A0, COM_A15}, {"Simple 17", A1, COM_A15},
  {"Triple 3", A6, COM_A15},  {"Double 3", 51, COM_A15},  {"Simple 3", 53, COM_A15},
  {"Triple 19", A5, COM_A15}, {"Double 19", 47, COM_A15}, {"Simple 19", 49, COM_A15},
  {"Triple 7", A4, COM_A15},  {"Double 7", 43, COM_A15},  {"Simple 7", 45, COM_A15},
  {"Triple 16", A3, COM_A15}, {"Double 16", 41, COM_A15}, {"Simple 16", 39, COM_A15},

  // === Common A14 ===
  {"Triple 6", A6, COM_A14},  {"Double 6", 51, COM_A14},  {"Simple 6", 53, COM_A14},
  {"Triple 10", A5, COM_A14}, {"Double 10", 47, COM_A14}, {"Simple 10", 49, COM_A14},
  {"Triple 15", A4, COM_A14}, {"Double 15", 43, COM_A14}, {"Simple 15", 45, COM_A14},
  {"Triple 2", A3, COM_A14},  {"Double 2", 41, COM_A14},  {"Simple 2", 39, COM_A14},
  {"25 (Double)", A2, COM_A14},
  {"Triple 13", A7, COM_A14}, {"Double 13", A0, COM_A14}, {"Simple 13", A1, COM_A14},

  // === Common A12 ===
  {"Triple 8", A7, COM_A12},  {"Double 8", A0, COM_A12},  {"Simple 8", A1, COM_A12},
  {"Triple 14", A5, COM_A12}, {"Double 14", 47, COM_A12}, {"Simple 14", 49, COM_A12},
  {"Triple 9", A4, COM_A12},  {"Double 9", 43, COM_A12},  {"Simple 9", 45, COM_A12},
  {"Triple 11", A6, COM_A12}, {"Double 11", 51, COM_A12}, {"Simple 11", 53, COM_A12},
  {"Triple 12", A3, COM_A12}, {"Double 12", 41, COM_A12}, {"Simple 12", 39, COM_A12},

  // === Common A13 ===
  {"Triple 5", A7, COM_A13},  {"Double 5", A0, COM_A13},  {"Simple 5", A1, COM_A13},
  {"Triple 20", A6, COM_A13}, {"Double 20", 51, COM_A13}, {"Simple 20", 53, COM_A13},
  {"Triple 1", A5, COM_A13},  {"Double 1", 47, COM_A13},  {"Simple 1", 49, COM_A13},
  {"Triple 18", A4, COM_A13}, {"Double 18", 43, COM_A13}, {"Simple 18", 45, COM_A13},
  {"Triple 4", A3, COM_A13},  {"Double 4", 41, COM_A13},
  {"25 (Simple)", A2, COM_A13},
  {"Simple 4", 39, COM_A13}
};

void setup() {
  Serial.begin(9600);
  for (const auto& meta : mete) {
    pinMode(meta.pinAktivan, INPUT_PULLUP);
    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }
  Serial.println(F("Dartboard calibration - hit a target"));
}

static const Meta* scanForHit() {
  for (const auto& meta : mete) {
    pinMode(meta.pinZajednicki, OUTPUT);
    digitalWrite(meta.pinZajednicki, LOW);
    pinMode(meta.pinAktivan, INPUT_PULLUP);
    if (digitalRead(meta.pinAktivan) == LOW) {
      delay(300);
      while (digitalRead(meta.pinAktivan) == LOW);
      delay(300);
      pinMode(meta.pinZajednicki, INPUT_PULLUP);
      return &meta;
    }
    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }
  return nullptr;
}

void loop() {
  const Meta* pogodjena = scanForHit();
  if (pogodjena) {
    Serial.print(pogodjena->naziv);
    Serial.print(F(" | active="));
    Serial.print(pogodjena->pinAktivan);
    Serial.print(F(" com="));
    Serial.println(pogodjena->pinZajednicki);
    delay(500); // give some time to see output
  }
}

