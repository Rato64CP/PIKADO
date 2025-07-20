#include "game_3inline.h"
#include "game.h"
#include "config.h"

bool pogodci[6][21]; // [igrač][broj 1-20], indeks 0 se ne koristi

void inicijalizirajIgru_3inline() {
    for (int i = 0; i < brojIgraca; i++) {
        for (int b = 1; b <= 20; b++) {
            pogodci[i][b] = false;
        }
    }
    trenutniIgrac = 0;
    Serial.println("Igra 3-in-line započinje!");
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_3inline(const String& nazivMete) {
    int broj = 0;

    if (nazivMete.startsWith("Triple ") || nazivMete.startsWith("Double ") || nazivMete.startsWith("Simple ")) {
        broj = nazivMete.substring(nazivMete.indexOf(' ') + 1).toInt();
    } else if (nazivMete.indexOf("25") != -1) {
        Serial.println("Pogodak u 25 ne vrijedi za 3-in-line.");
        sljedeciIgrac_3inline();
        return;
    } else {
        broj = nazivMete.toInt(); // fallback
    }

    if (broj < 1 || broj > 20) {
        Serial.println("Nevažeći broj: " + String(broj));
        sljedeciIgrac_3inline();
        return;
    }

    Igrac& igrac = igraci[trenutniIgrac];

    if (!pogodci[trenutniIgrac][broj]) {
        pogodci[trenutniIgrac][broj] = true;
        Serial.println(igrac.ime + " je pogodio broj " + String(broj));
    } else {
        Serial.println("Broj " + String(broj) + " je već pogođen.");
    }

    // Provjera uzastopnih pogodaka
    int uzastopni = 0;
    for (int b = 1; b <= 20; b++) {
        if (pogodci[trenutniIgrac][b]) {
            uzastopni++;
            if (uzastopni >= 3) {
                Serial.println(igrac.ime + " je pobijedio s 3 uzastopna broja!");
                return; // kraj igre
            }
        } else {
            uzastopni = 0;
        }
    }

    sljedeciIgrac_3inline();
}

void resetirajIgru_3inline() {
    for (int i = 0; i < brojIgraca; i++) {
        for (int b = 1; b <= 20; b++) {
            pogodci[i][b] = false;
        }
    }
    trenutniIgrac = 0;
    Serial.println("Igra 3-in-line je resetirana.");
}

void sljedeciIgrac_3inline() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}
