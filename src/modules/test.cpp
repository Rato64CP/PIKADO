#include "test.h"
#include "buttons.h"
#include "zaruljice.h"
#include "detection.h"
#include "lcd_display.h"
#include "error.h"

bool resetHeld(unsigned long ms) {
  unsigned long start = millis();
  while (tipkaStisnuta(IGRA_RESET)) {
    if (millis() - start >= ms) return true;
    ocitajTipke();
    delay(10);
  }
  return false;
}

void testMode() {
  logPoruka("Dobrodosli u test mod");
  bool led[18] = {false};
  bool prev[18] = {false};
  unsigned long holdStart[18] = {0};
  postaviZaruljice(led);
  while (true) {
    ocitajTipke();

    if (tipkaStisnuta(IGRA_RESET)) {
      if (holdStart[IGRA_RESET] == 0) holdStart[IGRA_RESET] = millis();
      if (millis() - holdStart[IGRA_RESET] >= 5000) {
        logPoruka("Izlaz iz test moda");
        for (int i = 0; i < 18; i++) led[i] = false;
        postaviZaruljice(led);
        delay(500);
        return;
      }
    } else {
      holdStart[IGRA_RESET] = 0;
    }

    for (int i = 0; i < BROJ_TIPKI; i++) {
      if (i == IGRA_RESET) continue;
      bool cur = tipkaStisnuta(i);
      if (cur && !prev[i]) {
        logPoruka(String("Tipka ") + String(i));
        holdStart[i] = millis();
      } else if (cur) {
        if (millis() - holdStart[i] >= 2000) {
          led[i] = !led[i];
          postaviZaruljice(led);
          holdStart[i] = millis();
        }
      } else {
        holdStart[i] = 0;
      }
      prev[i] = cur;
    }

    String hit = detektirajZonuTest();
    if (hit != "") {
      if (hit == "MIC") logPoruka("Promasaj (MIC)");
      else logPoruka(hit);
    }

    delay(10);
  }
}

static unsigned long testHoldStart = 0;

void provjeriTestMod() {
  if (tipkaStisnuta(IGRA_RESET)) {
    if (testHoldStart == 0) testHoldStart = millis();
    if (millis() - testHoldStart >= 5000) {
      testHoldStart = 0;
      testMode();
    }
  } else {
    testHoldStart = 0;
  }
}
