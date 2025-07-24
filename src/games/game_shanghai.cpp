#include "../modules/lcd_display.h"
#include "game_shanghai.h"
#include "../core/game.h"
#include "../core/config.h"
#include "../modules/scoreboard.h"
#include "../modules/melodies.h"

static int runda = 1;
static int strelica = 1;
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
        igraci[i].bodovi = 0;
    }
    trenutniIgrac = 0;
    logPoruka("Igra SHANGHAI započinje!");
    String msg = "Runda " + String(runda) + ": Pogađa se broj " + String(runda);
    logPoruka(msg);
    prikaziCilj(trenutniIgrac, runda, 1500);
    najaviCiljaniBroj(runda);
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    osvjeziSveBodove();
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
        logPoruka("Nepoznata meta: " + nazivMete);
        return;
    }

    if (broj != runda) {
        logPoruka("Promašaj! Važeći broj u ovoj rundi je " + String(runda));
        svirajZvukPromasaja();
    } else {
        bodoviPoIgracu[trenutniIgrac] += broj * mnozitelj;
        igraci[trenutniIgrac].bodovi = bodoviPoIgracu[trenutniIgrac];
        prikaziBodove(trenutniIgrac, igraci[trenutniIgrac].bodovi);
        if (mnozitelj == 1) pogodjenoSimple[trenutniIgrac] = true;
        if (mnozitelj == 2) pogodjenoDouble[trenutniIgrac] = true;
        if (mnozitelj == 3) pogodjenoTriple[trenutniIgrac] = true;

        svirajZvukTargetHit();

        logPoruka("Pogođeno " + String(broj) + " × " + String(mnozitelj) +
                       " = +" + String(broj * mnozitelj));
    }

    strelica++;

    if (strelica > 3) {
        // Provjera Shanghai
        if (pogodjenoSimple[trenutniIgrac] &&
            pogodjenoDouble[trenutniIgrac] &&
            pogodjenoTriple[trenutniIgrac]) {
            logPoruka(igraci[trenutniIgrac].ime + " je napravio SHANGHAI i pobijedio!");
            svirajZvukShanghai();
            zavrsiIgru();
            return; // završava igra
        } else {
            svirajZvukTryAgain();
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
                logPoruka("Kraj igre!");
                // Odredi pobjednika
                int najvise = -1;
                int pobjednik = -1;
                for (int i = 0; i < brojIgraca; i++) {
                    logPoruka(igraci[i].ime + ": " + String(bodoviPoIgracu[i]) + " bodova");
                    if (bodoviPoIgracu[i] > najvise) {
                        najvise = bodoviPoIgracu[i];
                        pobjednik = i;
                    }
                }
                logPoruka("Pobjednik je " + igraci[pobjednik].ime + "!");
                zavrsiIgru();
                return;
            } else {
                String msg = "Runda " + String(runda) + ": Pogađa se broj " + String(runda);
                logPoruka(msg);
                prikaziCilj(trenutniIgrac, runda, 1500);
                najaviCiljaniBroj(runda);
            }
        }

        logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    }
}

void resetirajIgru_shanghai() {
    inicijalizirajIgru_shanghai();
}

void sljedeciIgrac_shanghai() {
    // Ne koristi se u ovoj igri jer je logika već u obradi
}
