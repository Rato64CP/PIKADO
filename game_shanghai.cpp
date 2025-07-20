#include "game_shanghai.h"
#include "game.h"
#include "config.h"

int runda = 1;
int strelica = 1;
int bodoviPoIgracu[6];
bool pogodjenoSimple[6];
bool pogodjenoDouble[6];
bool pogodjenoTriple[6];

void inicijalizirajIgru_shanghai() {
    runda = 1;
    strelica = 1;
    for (int i = 0; i < brojIgraca; i++) {
        bodoviPoIgracu[i] = 0;
        pogodjenoSimple[i] = false;
        pogodjenoDouble[i] = false;
        pogodjenoTriple[i] = false;
    }
    trenutniIgrac = 0;
    Serial.println("Igra SHANGHAI započinje!");
    Serial.print("Runda "); Serial.print(runda);
    Serial.println(": Pogađa se broj " + String(runda));
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_shanghai(const String& nazivMete) {
    int broj = 0;
    int mnozitelj = 0;

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

    if (broj != runda) {
        Serial.println("Promašaj! Važeći broj u ovoj rundi je " + String(runda));
    } else {
        bodoviPoIgracu[trenutniIgrac] += broj * mnozitelj;
        if (mnozitelj == 1) pogodjenoSimple[trenutniIgrac] = true;
        if (mnozitelj == 2) pogodjenoDouble[trenutniIgrac] = true;
        if (mnozitelj == 3) pogodjenoTriple[trenutniIgrac] = true;

        Serial.println("Pogođeno " + String(broj) + " × " + String(mnozitelj) +
                       " = +" + String(broj * mnozitelj));
    }

    strelica++;

    if (strelica > 3) {
        // Provjera Shanghai
        if (pogodjenoSimple[trenutniIgrac] &&
            pogodjenoDouble[trenutniIgrac] &&
            pogodjenoTriple[trenutniIgrac]) {
            Serial.println(igraci[trenutniIgrac].ime + " je napravio SHANGHAI i pobijedio!");
            return; // završava igra
        }

        // Reset za sljedećeg igrača
        pogodjenoSimple[trenutniIgrac] = false;
        pogodjenoDouble[trenutniIgrac] = false;
        pogodjenoTriple[trenutniIgrac] = false;

        strelica = 1;
        trenutniIgrac++;

        if (trenutniIgrac >= brojIgraca) {
            trenutniIgrac = 0;
            runda++;
            if (runda > 20) {
                Serial.println("Kraj igre!");
                // Odredi pobjednika
                int najvise = -1;
                int pobjednik = -1;
                for (int i = 0; i < brojIgraca; i++) {
                    Serial.println(igraci[i].ime + ": " + String(bodoviPoIgracu[i]) + " bodova");
                    if (bodoviPoIgracu[i] > najvise) {
                        najvise = bodoviPoIgracu[i];
                        pobjednik = i;
                    }
                }
                Serial.println("Pobjednik je " + igraci[pobjednik].ime + "!");
                return;
            } else {
                Serial.print("Runda "); Serial.print(runda);
                Serial.println(": Pogađa se broj " + String(runda));
            }
        }

        Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
    }
}

void resetirajIgru_shanghai() {
    inicijalizirajIgru_shanghai();
}

void sljedeciIgrac_shanghai() {
    // Ne koristi se u ovoj igri jer je logika već u obradi
}