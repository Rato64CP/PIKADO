#include "scoreboard.h"
#include "../core/game.h"
#include <LedControl.h>

const uint8_t PIN_DIN = 9;
const uint8_t PIN_CLK = 10;
const uint8_t PIN_CS  = 11;
const uint8_t BROJ_DISPLEJA = 6;

static LedControl lc(PIN_DIN, PIN_CLK, PIN_CS, BROJ_DISPLEJA);

void inicijalizirajDisplay() {
    for (uint8_t i = 0; i < BROJ_DISPLEJA; i++) {
        lc.shutdown(i, false);
        lc.setIntensity(i, 8);
        lc.clearDisplay(i);
    }
}

static void prikaziCrte(uint8_t modul) {
    if (modul >= BROJ_DISPLEJA) return;
    for (uint8_t pos = 0; pos < 3; pos++) {
        lc.setChar(modul, pos, '-', false);
    }
}

static void prikaziBroj(uint8_t modul, int broj) {
    if (modul >= BROJ_DISPLEJA) return;
    broj = constrain(broj, 0, 999);
    int stotine  = broj / 100;
    int desetice = (broj / 10) % 10;
    int jedinice = broj % 10;

    lc.setDigit(modul, 2, jedinice, false);
    lc.setDigit(modul, 1, desetice, false);
    lc.setDigit(modul, 0, stotine, false);
}

void prikaziBodove(uint8_t igrac, int bodovi) {
    prikaziBroj(igrac, bodovi);
}

void osvjeziSveBodove() {
    for (int i = 0; i < brojIgraca; i++) {
        prikaziBodove(i, igraci[i].bodovi);
    }
    for (int i = brojIgraca; i < BROJ_DISPLEJA; i++) {
        prikaziCrte(i);
    }
}

void ocistiDisplay() {
    for (uint8_t i = 0; i < BROJ_DISPLEJA; i++) {
        prikaziCrte(i);
    }
}

void prikaziCilj(uint8_t igrac, int broj, unsigned long trajanjeMs) {
    prikaziBroj(igrac, broj);
    delay(trajanjeMs);
    prikaziBodove(igrac, igraci[igrac].bodovi);
}

void ugasiDisplay() {
    for (uint8_t i = 0; i < BROJ_DISPLEJA; i++) {
        lc.clearDisplay(i);
    }
}

void blinkBroj(uint8_t modul, int broj, uint8_t ponavljanja, unsigned int trajanjeMs) {
    if (modul >= BROJ_DISPLEJA) return;
    for (uint8_t i = 0; i < ponavljanja; i++) {
        prikaziBroj(modul, broj);
        delay(trajanjeMs);
        lc.clearDisplay(modul);
        delay(trajanjeMs);
    }
    prikaziBroj(modul, broj);
}
