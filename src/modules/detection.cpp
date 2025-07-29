#include "lcd_display.h"
#include "detection.h"
#include "../core/config.h"
#include "melodies.h"
#include "../core/game.h"

// Struktura za metu
struct Meta {
  const char* naziv;
  uint8_t pinAktivan;
  uint8_t pinZajednicki;
};

// Helper to convert a pin number to a human readable label
static String nazivPina(uint8_t pin) {
  if (pin == COM_A15) return String("COM_A15");
  if (pin == COM_A14) return String("COM_A14");
  if (pin == COM_A12) return String("COM_A12");
  if (pin == COM_A13) return String("COM_A13");

  if (pin >= A0 && pin <= A15) {
    return String("A") + String(pin - A0);
  }

  return String(pin);
}

// Definicija svih meta
const Meta mete[] = {
  // === Common A15 ===
  {"Triple 12", 41, COM_A15}, {"Double 12", A7, COM_A15}, {"Simple 12", A6, COM_A15},
  {"Triple 9", 43, COM_A15},  {"Double 9", A5, COM_A15},  {"Simple 9", A4, COM_A15},
  {"Triple 14", 45, COM_A15}, {"Double 14", A3, COM_A15}, {"Simple 14", A2, COM_A15},
  {"Triple 11", 47, COM_A15}, {"Double 11", A1, COM_A15}, {"Simple 11", A0, COM_A15},
  {"Triple 8", 49, COM_A15},  {"Double 8", 35, COM_A15},  {"Simple 8", 37, COM_A15},

  // === Common A14 ===
  {"Triple 4", 41, COM_A14},  {"Double 4", A7, COM_A14},  {"Simple 4", A6, COM_A14},
  {"Triple 18", 43, COM_A14}, {"Double 18", A5, COM_A14}, {"Simple 18", A4, COM_A14},
  {"Triple 1", 45, COM_A14},  {"Double 1", A3, COM_A14},  {"Simple 1", A2, COM_A14},
  {"Triple 20", 47, COM_A14}, {"Double 20", A1, COM_A14}, {"Simple 20", A0, COM_A14},
  {"Triple 5", 49, COM_A14},  {"Double 5", 35, COM_A14},  {"Simple 5", 37, COM_A14},
  {"25 (Simple)", 39, COM_A14},

  // === Common A13 ===
  {"Triple 2", 41, COM_A13},  {"Double 2", A7, COM_A13},  {"Simple 2", A6, COM_A13},
  {"Triple 15", 43, COM_A13}, {"Double 15", A5, COM_A13}, {"Simple 15", A4, COM_A13},
  {"Triple 10", 45, COM_A13}, {"Double 10", A3, COM_A13}, {"Simple 10", A2, COM_A13},
  {"Triple 6", 47, COM_A13},  {"Double 6", A1, COM_A13},  {"Simple 6", A0, COM_A13},
  {"Triple 13", 49, COM_A13}, {"Double 13", 35, COM_A13}, {"Simple 13", 37, COM_A13},
  {"25 (Double)", 39, COM_A13},

  // === Common A12 ===
  {"Triple 16", 41, COM_A12}, {"Double 16", A7, COM_A12}, {"Simple 16", A6, COM_A12},
  {"Triple 7", 43, COM_A12},  {"Double 7", A5, COM_A12},  {"Simple 7", A4, COM_A12},
  {"Triple 19", 45, COM_A12}, {"Double 19", A3, COM_A12}, {"Simple 19", A2, COM_A12},
  {"Triple 3", 47, COM_A12},  {"Double 3", A1, COM_A12},  {"Simple 3", A0, COM_A12},
  {"Triple 17", 49, COM_A12}, {"Double 17", 35, COM_A12}, {"Simple 17", 37, COM_A12}
};

void inicijalizirajMete() {
  for (const auto& meta : mete) {
    pinMode(meta.pinAktivan, INPUT_PULLUP);
    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }
  pinMode(PIN_MIKROFON, INPUT);
}

// Helper that scans all targets and returns the hit one
static const Meta* scanForHit() {
  for (const auto& meta : mete) {
    pinMode(meta.pinZajednicki, OUTPUT);
    digitalWrite(meta.pinZajednicki, LOW);
    pinMode(meta.pinAktivan, INPUT_PULLUP);

    if (digitalRead(meta.pinAktivan) == LOW) {
      // Debounce the sensor
      delay(300);
      while (digitalRead(meta.pinAktivan) == LOW)
        ;
      delay(300);

      pinMode(meta.pinZajednicki, INPUT_PULLUP);
      return &meta;
    }

    pinMode(meta.pinZajednicki, INPUT_PULLUP);
  }

  return nullptr;
}


String detektirajZonu() {
    const Meta* pogodjena = scanForHit();
    if (pogodjena) {
        registrirajInterakciju();
        String naziv = String(pogodjena->naziv);
        svirajZvukMete(naziv);
        return naziv;
    }
  return String("");
}

void detektirajPromasaj() {
  static unsigned long zadnjeVrijeme = 0;
  int zbroj = 0;
  for (int i = 0; i < 3; i++) {
    zbroj += analogRead(PIN_MIKROFON);
    delay(1);
  }
  int vrijednost = zbroj / 3;

  if (vrijednost > THRESHOLD_PROMASAJ && millis() - zadnjeVrijeme > 300) {
    logPoruka("Promasaj detektiran!");
    svirajZvukPromasaja();
    registrirajInterakciju();
    brojStrelica++;
    if (brojStrelica >= 3) {
      krajPoteza();
    }
    zadnjeVrijeme = millis();
  }
}

String detektirajBacanjeBezIgre() {
  // Provjera pogodene mete
  const Meta* meta = scanForHit();
  if (meta != nullptr) {
    return nazivPina(meta->pinZajednicki) + " -- " + nazivPina(meta->pinAktivan);
  }

  // Provjera promasaja preko mikrofona
  static unsigned long zadnjeVrijeme = 0;
  int zbroj = 0;
  for (int i = 0; i < 3; i++) {
    zbroj += analogRead(PIN_MIKROFON);
    delay(1);
  }
  int vrijednost = zbroj / 3;

  if (vrijednost > THRESHOLD_PROMASAJ && millis() - zadnjeVrijeme > 300) {
    zadnjeVrijeme = millis();
    return String("MIC");
  }

  return String("");
}
