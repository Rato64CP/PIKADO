#include "modules/lcd_display.h"
#include "games/game_301.h"
#include "core/game.h"
#include "core/config.h"
#include "modules/scoreboard.h"
#include "modules/melodies.h"

int vrijednostMete(const String& naziv) {
    if (naziv.startsWith("Triple ")) return 3 * naziv.substring(7).toInt();
    if (naziv.startsWith("Double ")) return 2 * naziv.substring(7).toInt();
    if (naziv.startsWith("Simple ")) return naziv.substring(7).toInt();
    if (naziv.indexOf("25") != -1) return (naziv.indexOf("Double") != -1) ? 50 : 25;
    return 0;
}

void inicijalizirajIgru_301() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 301;
        igraci[i].prethodniBodovi = 301;
    }
    trenutniIgrac = 0;
    logPoruka("Igra 301 započinje!");
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    osvjeziSveBodove();
}

void obradiPogodak_301(const String& nazivMete) {
    int vrijednost = vrijednostMete(nazivMete);
    Igrac& igrac = igraci[trenutniIgrac];

    // DOUBLE IN provjera
    if (DOUBLE_IN && !igrac.jeAktiviran) {
        if (!nazivMete.startsWith("Double")) {
            logPoruka("Double IN: pogodak ne vrijedi jer nije Double.");
            krajPoteza();
            return;
        }
        igrac.jeAktiviran = true;
    }

    igrac.prethodniBodovi = igrac.bodovi;

    int bodoviNakonPogotka = igrac.bodovi - vrijednost;

    String poruka = "Pogođeno: " + nazivMete + " (" + String(vrijednost) + " bodova)";
    logPoruka(poruka);

    if (BOUNCE_OUT && bodoviNakonPogotka < 0) {
        logPoruka("Bust! Prelazak preko 0 nije dozvoljen.");
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
                logPoruka("Završetak mora biti s Double!");
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


void resetirajIgru_301() {
    for (int i = 0; i < brojIgraca; i++) {
        igraci[i].bodovi = 301;
        igraci[i].prethodniBodovi = 301;
    }
    trenutniIgrac = 0;
    logPoruka("Igra je resetirana.");
    osvjeziSveBodove();
}
