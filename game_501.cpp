#include "game_501.h"
#include "game.h"
#include "config.h"

int vrijednostMete_501(const String& naziv) {
    if (naziv.startsWith("Triple ")) return 3 * naziv.substring(7).toInt();
    if (naziv.startsWith("Double ")) return 2 * naziv.substring(7).toInt();
    if (naziv.startsWith("Simple ")) return naziv.substring(7).toInt();
    if (naziv.indexOf("25") != -1) return (naziv.indexOf("Double") != -1) ? 50 : 25;
    return 0;
}

void inicijalizirajIgru_501() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 501;
        igraci[i].prethodniBodovi = 501;
    }
    trenutniIgrac = 0;
    Serial.println("Igra 501 započinje!");
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_501(const String& nazivMete) {
    int vrijednost = vrijednostMete_501(nazivMete);
    Igrac& igrac = igraci[trenutniIgrac];
    igrac.prethodniBodovi = igrac.bodovi;

    int bodoviNakonPogotka = igrac.bodovi - vrijednost;

    Serial.print("Pogođeno: ");
    Serial.print(nazivMete);
    Serial.print(" (");
    Serial.print(vrijednost);
    Serial.println(" bodova)");

    if (BOUNCE_OUT && bodoviNakonPogotka < 0) {
        Serial.println("Bust! Prelazak preko 0 nije dozvoljen.");
        igrac.bodovi = igrac.prethodniBodovi;
        sljedeciIgrac();
        return;
    }

    if (bodoviNakonPogotka == 0) {
        if (DOUBLE_OUT) {
            if (nazivMete.startsWith("Double")) {
                Serial.println(igrac.ime + " je pobijedio!");
                // ovdje možeš završiti igru
            } else {
                Serial.println("Završetak mora biti s Double!");
                igrac.bodovi = igrac.prethodniBodovi;
                sljedeciIgrac();
            }
        } else {
            Serial.println(igrac.ime + " je pobijedio!");
            // ovdje možeš završiti igru
        }
        return;
    }

    igrac.bodovi = bodoviNakonPogotka;
    Serial.println(igrac.ime + ": " + String(igrac.bodovi) + " bodova");
    sljedeciIgrac();
}

void resetirajIgru_501() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 501;
        igraci[i].prethodniBodovi = 501;
    }
    trenutniIgrac = 0;
    Serial.println("Igra 501 je resetirana.");
}

void sljedeciIgrac_501() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    Serial.println("Na potezu: " + igraci[trenutniIgrac].ime);
}