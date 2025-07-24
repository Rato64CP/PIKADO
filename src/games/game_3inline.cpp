#include "../modules/lcd_display.h"
#include "game_3inline.h"
#include "../core/game.h"
#include "../core/config.h"
#include "../modules/scoreboard.h"

static bool pogodci[6][21]; // [igrač][broj 1-20], indeks 0 se ne koristi
static uint8_t najduljiNiz[6];

static int izracunajNiz(uint8_t igrac) {
    int uzastopni = 0;
    int maxNiz = 0;
    for (int b = 1; b <= 20; b++) {
        if (pogodci[igrac][b]) {
            uzastopni++;
            if (uzastopni > maxNiz) maxNiz = uzastopni;
        } else {
            uzastopni = 0;
        }
    }
    return maxNiz;
}

void inicijalizirajIgru_3inline() {
    for (int i = 0; i < brojIgraca; i++) {
        for (int b = 1; b <= 20; b++) {
            pogodci[i][b] = false;
        }
        najduljiNiz[i] = 0;
        prikaziBodove(i, 0);
    }
    trenutniIgrac = 0;
    logPoruka("Igra 3-in-line započinje!");
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
}

void obradiPogodak_3inline(const String& nazivMete) {
    int broj = 0;

    if (nazivMete.startsWith("Triple ") || nazivMete.startsWith("Double ") || nazivMete.startsWith("Simple ")) {
        broj = nazivMete.substring(nazivMete.indexOf(' ') + 1).toInt();
    } else if (nazivMete.indexOf("25") != -1) {
        logPoruka("Pogodak u 25 ne vrijedi za 3-in-line.");
        sljedeciIgrac_3inline();
        return;
    } else {
        broj = nazivMete.toInt(); // fallback
    }

    if (broj < 1 || broj > 20) {
        logPoruka("Nevažeći broj: " + String(broj));
        sljedeciIgrac_3inline();
        return;
    }

    Igrac& igrac = igraci[trenutniIgrac];

    if (!pogodci[trenutniIgrac][broj]) {
        pogodci[trenutniIgrac][broj] = true;
        logPoruka(igrac.ime + " je pogodio broj " + String(broj));
    } else {
        logPoruka("Broj " + String(broj) + " je već pogođen.");
    }

    int niz = izracunajNiz(trenutniIgrac);

    if (niz >= 3) {
        logPoruka(igrac.ime + " je pobijedio s 3 uzastopna broja!");
        blinkBroj(trenutniIgrac, 3, 3, 200);
        zavrsiIgru();
        return; // kraj igre
    }

    if (niz > najduljiNiz[trenutniIgrac]) {
        najduljiNiz[trenutniIgrac] = niz;
        blinkBroj(trenutniIgrac, niz, 2, 150);
    } else {
        prikaziBodove(trenutniIgrac, najduljiNiz[trenutniIgrac]);
    }

    sljedeciIgrac_3inline();
}

void resetirajIgru_3inline() {
    for (int i = 0; i < brojIgraca; i++) {
        for (int b = 1; b <= 20; b++) {
            pogodci[i][b] = false;
        }
        najduljiNiz[i] = 0;
        prikaziBodove(i, 0);
    }
    trenutniIgrac = 0;
    logPoruka("Igra 3-in-line je resetirana.");
}

void sljedeciIgrac_3inline() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
}
