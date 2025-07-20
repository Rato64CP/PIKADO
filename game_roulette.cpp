#include "game_roulette.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_roulette() {
    Serial.println("Igra ROULETTE još nije implementirana.");
}

void obradiPogodak_roulette(const String& nazivMete) {
    Serial.println("Pogođeno u ROULETTE: " + nazivMete);
}

void resetirajIgru_roulette() {
    Serial.println("Reset igre ROULETTE");
}

void sljedeciIgrac_roulette() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
