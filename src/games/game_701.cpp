#include "../modules/lcd_display.h"
#include "game_701.h"
#include "../core/game.h"
#include "../core/config.h"
#include "../modules/scoreboard.h"
#include "../modules/melodies.h"

int vrijednostMete_701(const String& naziv) {
    if (naziv.startsWith("Triple ")) return 3 * naziv.substring(7).toInt();
    if (naziv.startsWith("Double ")) return 2 * naziv.substring(7).toInt();
    if (naziv.startsWith("Simple ")) return naziv.substring(7).toInt();
    if (naziv.indexOf("25") != -1) return (naziv.indexOf("Double") != -1) ? 50 : 25;
    return 0;
}

void inicijalizirajIgru_701() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 701;
        igraci[i].prethodniBodovi = 701;
    }
    trenutniIgrac = 0;
    logPoruka("Igra 701 zapocinje!");
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    osvjeziSveBodove();
}

void obradiPogodak_701(const String& nazivMete) {
    int vrijednost = vrijednostMete_701(nazivMete);
    Igrac& igrac = igraci[trenutniIgrac];

    // DOUBLE IN provjera
    if (DOUBLE_IN && !igrac.jeAktiviran) {
        if (!nazivMete.startsWith("Double")) {
            logPoruka("Double IN: treba Double.");
            krajPoteza();
            return;
        }
        igrac.jeAktiviran = true;
        provjeriDoubleInZavrsen();
    }

    igrac.prethodniBodovi = igrac.bodovi;

    int bodoviNakonPogotka = igrac.bodovi - vrijednost;

    String poruka = "Pogodeno: " + nazivMete + " (" + String(vrijednost) + " bodova)";
    logPoruka(poruka);

    if (BOUNCE_OUT && bodoviNakonPogotka < 0) {
        logPoruka("Bust! Prelazak preko 0 nije OK.");
        svirajZvukBust();
        igrac.bodovi = igrac.prethodniBodovi;
        prikaziBodove(trenutniIgrac, igrac.bodovi);
        krajPoteza();
        return;
    }

    if (bodoviNakonPogotka == 0) {
        if (DOUBLE_OUT) {
            if (nazivMete.startsWith("Double")) {
                logPoruka(igrac.ime + " je pobijedio!");
                zavrsiIgru();
            } else {
                logPoruka("Zavrsetak mora biti s Double!");
                igrac.bodovi = igrac.prethodniBodovi;
                krajPoteza();
            }
        } else {
            logPoruka(igrac.ime + " je pobijedio!");
            zavrsiIgru();
        }
        prikaziBodove(trenutniIgrac, igrac.bodovi);
        return;
    }

    igrac.bodovi = bodoviNakonPogotka;
    logPoruka(igrac.ime + ": " + String(igrac.bodovi) + " bodova");
    prikaziBodove(trenutniIgrac, igrac.bodovi);

    brojStrelica++;
    if (brojStrelica >= 3) {
        krajPoteza();
    }
}

void resetirajIgru_701() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 701;
        igraci[i].prethodniBodovi = 701;
    }
    trenutniIgrac = 0;
    logPoruka("Igra 701 je resetirana.");
    osvjeziSveBodove();
}
