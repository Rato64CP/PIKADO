#include "game_shangai.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_shangai() {
    Serial.println("Igra SHANGAI još nije implementirana.");
}

void obradiPogodak_shangai(const String& nazivMete) {
    Serial.println("Pogođeno u SHANGAI: " + nazivMete);
}

void resetirajIgru_shangai() {
    Serial.println("Reset igre SHANGAI");
}

void sljedeciIgrac_shangai() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
