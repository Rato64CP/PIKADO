#include "game_3inline.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_3inline() {
    Serial.println("Igra 3INLINE još nije implementirana.");
}

void obradiPogodak_3inline(const String& nazivMete) {
    Serial.println("Pogođeno u 3INLINE: " + nazivMete);
}

void resetirajIgru_3inline() {
    Serial.println("Reset igre 3INLINE");
}

void sljedeciIgrac_3inline() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
