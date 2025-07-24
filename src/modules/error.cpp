#include "error.h"
#include "lcd_display.h"

static bool aktivna = false;
static bool blinkStanje = false;
static unsigned long zadnjeBlinkanje = 0;

void signalGreska(const String &poruka) {
    logPoruka(String("GRESKA: ") + poruka);
    aktivna = true;
    blinkStanje = true;
    zadnjeBlinkanje = millis();
}

void obrisiGresku() {
    aktivna = false;
    blinkStanje = false;
}

bool greskaAktivna() { return aktivna; }

bool greskaBlinkStanje() { return blinkStanje; }

void azurirajGresku() {
    if (!aktivna) return;
    unsigned long sada = millis();
    if (sada - zadnjeBlinkanje >= 500) {
        zadnjeBlinkanje = sada;
        blinkStanje = !blinkStanje;
    }
}
