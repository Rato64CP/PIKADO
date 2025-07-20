#include "game_501.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_501() {
    Serial.println("Igra 501 još nije implementirana.");
}

void obradiPogodak_501(const String& nazivMete) {
    Serial.println("Pogođeno u 501: " + nazivMete);
}

void resetirajIgru_501() {
    Serial.println("Reset igre 501");
}

void sljedeciIgrac_501() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
