#pragma once
#include <Arduino.h>

struct Igrac {
    String ime;
    int bodovi;
    int prethodniBodovi;
    bool jeAktiviran = false;
};

enum TipIgre {
    Igra_301,
    Igra_501,
    Igra_701,
    Igra_Shanghai,
    Igra_Hangman,
    Igra_Roulette,
    Igra_Cricket,
    Igra_3Inline
};

extern Igrac igraci[6];
extern int brojIgraca;
extern int trenutniIgrac;
extern TipIgre aktivnaIgra;
extern bool igraZavrsena;
extern bool cekanjeNovogIgraca;
extern uint8_t brojStrelica;

void krajPoteza();

// Zavrsi igru i odsviraj ton na buzzeru
void zavrsiIgru();
// Resetira trenutno aktivnu igru
void resetirajAktivnuIgru();

void inicijalizirajIgrace(int broj);
void sljedeciIgrac();

// Centralne funkcije:
void pokreniAktivnuIgru();
void obradiPogodak(const String& nazivMete);
