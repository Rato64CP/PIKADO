#include "modules/lcd_display.h"
#include "games/game_roulette.h"
#include "core/game.h"
#include "core/config.h"
#include "modules/scoreboard.h"
#include "modules/melodies.h"

static int runda = 1;
static int strelica = 1;
int ciljaniBroj[6];  // ciljani broj po igraču
int bodoviRoulette[6];  // ukupni bodovi

void inicijalizirajIgru_roulette() {
    runda = 1;
    strelica = 1;
    for (int i = 0; i < brojIgraca; i++) {
        ciljaniBroj[i] = random(1, 21);  // 1–20
        bodoviRoulette[i] = 0;
        igraci[i].bodovi = 0;
        logPoruka("Igrač " + String(i) + " ciljani broj: " + String(ciljaniBroj[i]));
    }
    trenutniIgrac = 0;
    logPoruka("Igra ROULETTE započinje!");
    svirajZvukRouletteStart();
    logPoruka("Runda 1 – Na potezu: " + igraci[trenutniIgrac].ime);
    prikaziCilj(trenutniIgrac, ciljaniBroj[trenutniIgrac], 1500);
    najaviCiljaniBroj(ciljaniBroj[trenutniIgrac]);
    osvjeziSveBodove();
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
        logPoruka("Nepoznata meta: " + nazivMete);
        return;
    }

    if (broj == ciljaniBroj[trenutniIgrac]) {
        bodoviRoulette[trenutniIgrac] += broj * mnozitelj;
        igraci[trenutniIgrac].bodovi = bodoviRoulette[trenutniIgrac];
        logPoruka("Pogođen vlastiti broj! +" + String(broj * mnozitelj) +
                       " bodova. Ukupno: " + String(bodoviRoulette[trenutniIgrac]));
        prikaziBodove(trenutniIgrac, igraci[trenutniIgrac].bodovi);
        svirajZvukTargetHit();
    } else {
        logPoruka("Promašaj – nije tvoj broj.");
        svirajZvukPromasaja();
    }

    strelica++;

    if (strelica > 3) {
        strelica = 1;
        trenutniIgrac++;

        if (trenutniIgrac >= brojIgraca) {
            trenutniIgrac = 0;
            runda++;

            if (runda > 5) {
                logPoruka("Kraj igre ROULETTE!");
                svirajZvukRouletteOver();
                int pobjednik = 0;
                int najvise = bodoviRoulette[0];
                for (int i = 0; i < brojIgraca; i++) {
                    logPoruka("Igrač " + String(i) + ": " + String(bodoviRoulette[i]) + " bodova");
                    if (bodoviRoulette[i] > najvise) {
                        najvise = bodoviRoulette[i];
                        pobjednik = i;
                    }
                }
                logPoruka("Pobjednik je IGRAČ " + String(pobjednik) + "!");
                zavrsiIgru();
                return;
            }

            logPoruka("Runda " + String(runda));
        }

        logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
        prikaziCilj(trenutniIgrac, ciljaniBroj[trenutniIgrac], 1500);
        najaviCiljaniBroj(ciljaniBroj[trenutniIgrac]);
    }
}

void resetirajIgru_roulette() {
    inicijalizirajIgru_roulette();
}

void sljedeciIgrac_roulette() {
    // nije potrebno – koristi se interna rotacija
}
