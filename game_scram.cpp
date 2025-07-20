#include "game_scram.h"
#include "game.h"
#include "config.h"

int faza = 1;
bool zakljucaniBrojevi[21];  // 1–20
int pogodjeniBrojevi = 0;
int bodovi[2] = {0, 0}; // index 0: igrač A, 1: igrač B

void inicijalizirajIgru_scram() {
    brojIgraca = 2; // hardkodirano
    trenutniIgrac = 0;
    faza = 1;
    pogodjeniBrojevi = 0;
    for (int i = 1; i <= 20; i++) zakljucaniBrojevi[i] = false;
    bodovi[0] = 0;
    bodovi[1] = 0;

    Serial.println("Igra SCRAM (faza 1):");
    Serial.println("Igrač 0 je BLOCKER – pokušava zaključati sve brojeve.");
    Serial.println("Igrač 1 je SCORER – skuplja bodove.");
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_scram(const String& nazivMete) {
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

    if (broj < 1 || broj > 20) {
        Serial.println("Broj izvan raspona.");
        return;
    }

    if (faza == 1) {
        // BLOCKER
        if (trenutniIgrac == 0) {
            if (!zakljucaniBrojevi[broj]) {
                zakljucaniBrojevi[broj] = true;
                pogodjeniBrojevi++;
                Serial.println("Zaključan broj " + String(broj) + " (" + String(pogodjeniBrojevi) + "/20)");

                if (pogodjeniBrojevi == 20) {
                    Serial.println("Svi brojevi zaključani! Zamjena uloga.");
                    // Zamjena uloga
                    faza = 2;
                    trenutniIgrac = 1;
                    pogodjeniBrojevi = 0;
                    for (int i = 1; i <= 20; i++) zakljucaniBrojevi[i] = false;
                    Serial.println("Igrač 1 je sada BLOCKER. Igrač 0 SCORER.");
                    return;
                }
            } else {
                Serial.println("Broj " + String(broj) + " je već zaključan.");
            }
        }
        // SCORER
        else {
            if (!zakljucaniBrojevi[broj]) {
                bodovi[1] += broj * mnozitelj;
                Serial.println("SCORER pogodio " + String(broj) + " × " + String(mnozitelj) +
                               " = +" + String(broj * mnozitelj) + " bodova. (Ukupno: " + String(bodovi[1]) + ")");
            } else {
                Serial.println("Broj " + String(broj) + " je zaključan – nema bodova.");
            }
        }
    }

    else if (faza == 2) {
        // BLOCKER
        if (trenutniIgrac == 1) {
            if (!zakljucaniBrojevi[broj]) {
                zakljucaniBrojevi[broj] = true;
                pogodjeniBrojevi++;
                Serial.println("Zaključan broj " + String(broj) + " (" + String(pogodjeniBrojevi) + "/20)");

                if (pogodjeniBrojevi == 20) {
                    Serial.println("Kraj igre! Računamo rezultate...");
                    Serial.println("Igrač 0: " + String(bodovi[0]) + " bodova");
                    Serial.println("Igrač 1: " + String(bodovi[1]) + " bodova");
                    if (bodovi[0] > bodovi[1])
                        Serial.println("Pobjednik je IGRAČ 0!");
                    else if (bodovi[1] > bodovi[0])
                        Serial.println("Pobjednik je IGRAČ 1!");
                    else
                        Serial.println("Neriješeno!");
                    zavrsiIgru();
                    return;
                }
            } else {
                Serial.println("Broj " + String(broj) + " je već zaključan.");
            }
        }
        // SCORER
        else {
            if (!zakljucaniBrojevi[broj]) {
                bodovi[0] += broj * mnozitelj;
                Serial.println("SCORER pogodio " + String(broj) + " × " + String(mnozitelj) +
                               " = +" + String(broj * mnozitelj) + " bodova. (Ukupno: " + String(bodovi[0]) + ")");
            } else {
                Serial.println("Broj " + String(broj) + " je zaključan – nema bodova.");
            }
        }
    }

    // Sljedeći igrač
    trenutniIgrac = (trenutniIgrac + 1) % 2;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void resetirajIgru_scram() {
    inicijalizirajIgru_scram();
}

void sljedeciIgrac_scram() {
    // Ne koristi se jer je logika u obradi
}
