#include "game_shanghai.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_shanghai() {
    Serial.println("Igra SHANGHAI još nije implementirana.");
}

void obradiPogodak_shanghai(const String& nazivMete) {
    Serial.println("Pogođeno u SHANGHAI: " + nazivMete);
}

void resetirajIgru_shanghai() {
    Serial.println("Reset igre SHANGHAI");
}

void sljedeciIgrac_shanghai() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
