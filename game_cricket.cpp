#include "game_cricket.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_cricket() {
    Serial.println("Igra CRICKET još nije implementirana.");
}

void obradiPogodak_cricket(const String& nazivMete) {
    Serial.println("Pogođeno u CRICKET: " + nazivMete);
}

void resetirajIgru_cricket() {
    Serial.println("Reset igre CRICKET");
}

void sljedeciIgrac_cricket() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
