#include "game_scram.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_scram() {
    Serial.println("Igra SCRAM još nije implementirana.");
}

void obradiPogodak_scram(const String& nazivMete) {
    Serial.println("Pogođeno u SCRAM: " + nazivMete);
}

void resetirajIgru_scram() {
    Serial.println("Reset igre SCRAM");
}

void sljedeciIgrac_scram() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
