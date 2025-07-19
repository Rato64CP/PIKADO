#pragma once
#include <Arduino.h>

struct Igrac {
    String ime;
    int bodovi;
    int prethodniBodovi;
};

enum TipIgre { Igra_301, Igra_501, Igra_Shanghai };

extern Igrac igraci[6];
extern int brojIgraca;
extern int trenutniIgrac;
extern TipIgre aktivnaIgra;

void inicijalizirajIgrace(int broj);
void sljedeciIgrac();
