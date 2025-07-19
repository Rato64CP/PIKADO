#include "game.h"

Igrac igraci[6];
int brojIgraca = 0;
int trenutniIgrac = 0;
TipIgre aktivnaIgra = Igra_301;

void inicijalizirajIgrace(int broj) {
    brojIgraca = constrain(broj, 1, 6);
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].ime = "Igrac " + String(i + 1);
        igraci[i].bodovi = 301;
        igraci[i].prethodniBodovi = 301;
    }
    trenutniIgrac = 0;
}

void sljedeciIgrac() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
