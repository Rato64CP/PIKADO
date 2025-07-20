#include "game_hangman.h"
#include "game.h"
#include "config.h"

void inicijalizirajIgru_hangman() {
    Serial.println("Igra HANGMAN još nije implementirana.");
}

void obradiPogodak_hangman(const String& nazivMete) {
    Serial.println("Pogođeno u HANGMAN: " + nazivMete);
}

void resetirajIgru_hangman() {
    Serial.println("Reset igre HANGMAN");
}

void sljedeciIgrac_hangman() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
