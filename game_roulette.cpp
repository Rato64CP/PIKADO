#include "game_roulette.h"
#include "game.h"
#include "config.h"

int runda = 1;
int strelica = 1;
int ciljaniBroj[6];  // ciljani broj po igraču
int bodoviRoulette[6];  // ukupni bodovi

void inicijalizirajIgru_roulette() {
    runda = 1;
    strelica = 1;
    for (int i = 0; i < brojIgraca; i++) {
        ciljaniBroj[i] = random(1, 21);  // 1–20
        bodoviRoulette[i] = 0;
        Serial.println("Igrač " + String(i) + " ciljani broj: " + String(ciljaniBroj[i]));
    }
    trenutniIgrac = 0;
    Serial.println("Igra ROULETTE započinje!");
    Serial.println("Runda 1 – Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_roulette(const String& nazivMete) {
    int broj = 0;
    int mnozitelj = 1;

    if (nazivMete.startsWith("Triple ")) {
        broj = nazivMete.substring(7).toInt();
        mnozitelj = 3;
    } else if (nazivMete.startsWith("Double ")) {
        broj = nazivMete.substring(7).toInt();
        mnozitelj = 2;
    } else if (nazivMete.startsWith("Simple ")) {
        broj = nazivMete.substring(7).toInt();
        mnozitelj = 1;
    } else {
        Serial.println("Nepoznata meta: " + nazivMete);
        return;
    }

    if (broj == ciljaniBroj[trenutniIgrac]) {
        bodoviRoulette[trenutniIgrac] += broj * mnozitelj;
        Serial.println("Pogođen vlastiti broj! +" + String(broj * mnozitelj) +
                       " bodova. Ukupno: " + String(bodoviRoulette[trenutniIgrac]));
    } else {
        Serial.println("Promašaj – nije tvoj broj.");
    }

    strelica++;

    if (strelica > 3) {
        strelica = 1;
        trenutniIgrac++;

        if (trenutniIgrac >= brojIgraca) {
            trenutniIgrac = 0;
            runda++;

            if (runda > 5) {
                Serial.println("Kraj igre ROULETTE!");
                int pobjednik = 0;
                int najvise = bodoviRoulette[0];
                for (int i = 0; i < brojIgraca; i++) {
                    Serial.println("Igrač " + String(i) + ": " + String(bodoviRoulette[i]) + " bodova");
                    if (bodoviRoulette[i] > najvise) {
                        najvise = bodoviRoulette[i];
                        pobjednik = i;
                    }
                }
                Serial.println("Pobjednik je IGRAČ " + String(pobjednik) + "!");
                zavrsiIgru();
                return;
            }

            Serial.println("Runda " + String(runda));
        }

        Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
    }
}

void resetirajIgru_roulette() {
    inicijalizirajIgru_roulette();
}

void sljedeciIgrac_roulette() {
    // nije potrebno – koristi se interna rotacija
}
