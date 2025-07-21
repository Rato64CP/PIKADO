#include "melodies.h"
#include "config.h"

static void pusti(const Ton* melodija, size_t duljina) {
    for (size_t i = 0; i < duljina; ++i) {
        if (melodija[i].frekvencija == 0) {
            delay(melodija[i].trajanje);
        } else {
            tone(PIN_BUZZER, melodija[i].frekvencija, melodija[i].trajanje);
            delay(static_cast<unsigned long>(melodija[i].trajanje * 1.3));
        }
    }
    noTone(PIN_BUZZER);
}

void svirajMelodiju(const Ton* melodija, size_t duljina) { pusti(melodija, duljina); }

// ----------------------- Definicije melodija -----------------------

static const Ton introMelody[] = {
    {NOTE_C4, 150}, {NOTE_E4, 150}, {NOTE_G4, 300}
};

void svirajUvodnuMelodiju() { pusti(introMelody, sizeof(introMelody) / sizeof(Ton)); }

static const Ton zvukBacanje[] = {
    {NOTE_A4, 100}, {0, 50}, {NOTE_A4, 100}
};
void svirajZvukBacanja() { pusti(zvukBacanje, sizeof(zvukBacanje) / sizeof(Ton)); }

static const Ton zvukPromasaj[] = {
    {NOTE_C4, 200}, {NOTE_B4, 400}
};
void svirajZvukPromasaja() { pusti(zvukPromasaj, sizeof(zvukPromasaj) / sizeof(Ton)); }

static const Ton zvukVadenje[] = {
    {NOTE_G4, 150}, {NOTE_E4, 150}
};
void svirajZvukVadenja() { pusti(zvukVadenje, sizeof(zvukVadenje) / sizeof(Ton)); }

static const Ton zvukNoviIgrac[] = {
    {NOTE_D4, 150}, {NOTE_G4, 300}
};
void svirajZvukNovogIgraca() { pusti(zvukNoviIgrac, sizeof(zvukNoviIgrac) / sizeof(Ton)); }

static const Ton zvukPobjeda[] = {
    {NOTE_G4, 150}, {NOTE_A4, 150}, {NOTE_B4, 150}, {NOTE_C5, 300}
};
void svirajZvukPobjede() { pusti(zvukPobjeda, sizeof(zvukPobjeda) / sizeof(Ton)); }

static const Ton zvukTipka[] = {
    {NOTE_E4, 100}
};
void svirajZvukTipke() { pusti(zvukTipka, sizeof(zvukTipka) / sizeof(Ton)); }
