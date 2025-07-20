#include "game.h"
#include "game_301.h"
#include "game_501.h"
#include "game_shanghai.h"
#include "game_hangman.h"
#include "game_roulette.h"
#include "game_scram.h"
#include "game_cricket.h"
#include "game_3inline.h"
#include "config.h"  

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
    }
    trenutniIgrac = 0;
}

void sljedeciIgrac() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void krajPoteza() {
    cekanjeNovogIgraca = true;
    brojStrelica = 0;
    Serial.println("Izvadi strelice i pritisni NEW PLAYER.");
}

void pokreniAktivnuIgru() {
    switch (aktivnaIgra) {
        case Igra_301:      inicijalizirajIgru_301(); break;
        case Igra_501:      inicijalizirajIgru_501(); break;
        case Igra_Shanghai: inicijalizirajIgru_shanghai(); break;
        case Igra_Hangman:  inicijalizirajIgru_hangman(); break;
        case Igra_Roulette: inicijalizirajIgru_roulette(); break;
        case Igra_Scram:    inicijalizirajIgru_scram(); break;
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
        case Igra_Scram:    obradiPogodak_scram(nazivMete); break;
        case Igra_Cricket:  obradiPogodak_cricket(nazivMete); break;
        case Igra_3Inline:  obradiPogodak_3inline(nazivMete); break;
    }
}

void zavrsiIgru() {
    igraZavrsena = true;
    tone(PIN_BUZZER, 1000, 500);  // kratki zvuk kao signal pobjede
    Serial.println("Igra završena. Pritisni NEW PLAYER ili RESET za novu igru.");
}

void resetirajAktivnuIgru() {
    switch (aktivnaIgra) {
        case Igra_301:      resetirajIgru_301(); break;
        case Igra_501:      resetirajIgru_501(); break;
        case Igra_Shanghai: resetirajIgru_shanghai(); break;
        case Igra_Hangman:  resetirajIgru_hangman(); break;
        case Igra_Roulette: resetirajIgru_roulette(); break;
        case Igra_Scram:    resetirajIgru_scram(); break;
        case Igra_Cricket:  resetirajIgru_cricket(); break;
        case Igra_3Inline:  resetirajIgru_3inline(); break;
    }
}
