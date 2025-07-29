#include "../modules/lcd_display.h"
#include "game.h"
#include "../games/game_301.h"
#include "../games/game_501.h"
#include "../games/game_shanghai.h"
#include "../games/game_hangman.h"
#include "../games/game_roulette.h"
#include "../games/game_701.h"
#include "../games/game_cricket.h"
#include "../games/game_3inline.h"
#include "config.h"
#include "../modules/melodies.h"
#include "../modules/scoreboard.h"

bool DOUBLE_IN = false;
bool DOUBLE_OUT = false;

Igrac igraci[6];
int brojIgraca = 0;
int trenutniIgrac = 0;
TipIgre aktivnaIgra = Igra_301;
bool igraZavrsena = false;
bool cekanjeNovogIgraca = false;
uint8_t brojStrelica = 0;

void inicijalizirajIgrace(int broj) {
    brojIgraca = constrain(broj, 1, 6);
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].ime = "Igrac " + String(i + 1);
        igraci[i].bodovi = 0;
        igraci[i].prethodniBodovi = 0;
        igraci[i].jeAktiviran = false;
    }
    trenutniIgrac = 0;
    ocistiDisplay();
}

void provjeriDoubleInZavrsen() {
    if (!DOUBLE_IN) return;
    for (int i = 0; i < brojIgraca; i++) {
        if (!igraci[i].jeAktiviran) return;
    }
    DOUBLE_IN = false;
}

void sljedeciIgrac() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    svirajImeIgraca(trenutniIgrac);
}

void krajPoteza() {
    cekanjeNovogIgraca = true;
    brojStrelica = 0;
    logPoruka("Izvadi strelice i stisni NEW.");
    svirajZvukVadenja();
}

void pokreniAktivnuIgru() {
    switch (aktivnaIgra) {
        case Igra_301:      inicijalizirajIgru_301(); break;
        case Igra_501:      inicijalizirajIgru_501(); break;
        case Igra_Shanghai: inicijalizirajIgru_shanghai(); break;
        case Igra_Hangman:  inicijalizirajIgru_hangman(); break;
        case Igra_Roulette: inicijalizirajIgru_roulette(); break;
        case Igra_701:    inicijalizirajIgru_701(); break;
        case Igra_Cricket:  inicijalizirajIgru_cricket(); break;
        case Igra_3Inline:  inicijalizirajIgru_3inline(); break;
    }
}

void obradiPogodak(const String& nazivMete) {
    switch (aktivnaIgra) {
        case Igra_301:      obradiPogodak_301(nazivMete); break;
        case Igra_501:      obradiPogodak_501(nazivMete); break;
        case Igra_Shanghai: obradiPogodak_shanghai(nazivMete); break;
        case Igra_Hangman:  obradiPogodak_hangman(nazivMete); break;
        case Igra_Roulette: obradiPogodak_roulette(nazivMete); break;
        case Igra_701:    obradiPogodak_701(nazivMete); break;
        case Igra_Cricket:  obradiPogodak_cricket(nazivMete); break;
        case Igra_3Inline:  obradiPogodak_3inline(nazivMete); break;
    }
}

void zavrsiIgru() {
    igraZavrsena = true;
    svirajZvukPobjede();
    logPoruka("Igra gotova. Odaberi novu igru.");
}

void resetirajAktivnuIgru() {
    cekanjeNovogIgraca = false;
    brojStrelica = 0;
    switch (aktivnaIgra) {
        case Igra_301:      resetirajIgru_301(); break;
        case Igra_501:      resetirajIgru_501(); break;
        case Igra_Shanghai: resetirajIgru_shanghai(); break;
        case Igra_Hangman:  resetirajIgru_hangman(); break;
        case Igra_Roulette: resetirajIgru_roulette(); break;
        case Igra_701:    resetirajIgru_701(); break;
        case Igra_Cricket:  resetirajIgru_cricket(); break;
        case Igra_3Inline:  resetirajIgru_3inline(); break;
    }
}
