#include "../modules/lcd_display.h"
#include "game_cricket.h"
#include "../core/game.h"
#include "../core/config.h"
#include "../modules/scoreboard.h"

const int BROJEVI[7] = {15, 16, 17, 18, 19, 20, 25}; // validni brojevi
static int pogodci[6][7];   // [igrac][broj index]
static int bodoviCricket[6];

void inicijalizirajIgru_cricket() {
    for (int i = 0; i < brojIgraca; i++) {
        for (int j = 0; j < 7; j++) pogodci[i][j] = 0;
        bodoviCricket[i] = 0;
        igraci[i].bodovi = 0;
    }
    trenutniIgrac = 0;
    logPoruka("Igra CRICKET zapocinje!");
    logPoruka("Pogodi 15-20 i bull (25).");
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    osvjeziSveBodove();
}

int indeksBroja(int broj) {
    for (int i = 0; i < 7; i++) {
        if (BROJEVI[i] == broj) return i;
    }
    return -1;
}

bool sviZatvorili(int brojIndex) {
    for (int i = 0; i < brojIgraca; i++) {
        if (pogodci[i][brojIndex] < 3) return false;
    }
    return true;
}

void obradiPogodak_cricket(const String& nazivMete) {
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

    int idx = indeksBroja(broj);
    if (idx == -1) {
        logPoruka("Broj " + String(broj) + " nije vazeci u Cricketu.");
        sljedeciIgrac_cricket();
        return;
    }

    int& p = pogodci[trenutniIgrac][idx];
    int pogodakaPrije = p;
    p += mnozitelj;

    if (p > 3) {
        int visak = p - 3;
        p = 3;

        if (!sviZatvorili(idx)) {
            bodoviCricket[trenutniIgrac] += BROJEVI[idx] * visak;
            igraci[trenutniIgrac].bodovi = bodoviCricket[trenutniIgrac];
            logPoruka(String("Visak +") + String(BROJEVI[idx] * visak) +
                       " bod. Uk:" + String(bodoviCricket[trenutniIgrac]));
            prikaziBodove(trenutniIgrac, igraci[trenutniIgrac].bodovi);
        } else {
            logPoruka("Broj zatvoren - nema bodova.");
        }
    } else if (p > pogodakaPrije) {
        logPoruka(String("Dodano ") + String(mnozitelj) + "x" + String(broj) +
                       " (uk " + String(p) + ")");
    }

    // Provjera je li sve zatvoreno kod ovog igraca
    bool sveZatvoreno = true;
    for (int i = 0; i < 7; i++) {
        if (pogodci[trenutniIgrac][i] < 3) {
            sveZatvoreno = false;
            break;
        }
    }

    if (sveZatvoreno) {
        // provjeri je li bodovno ispred svih
        bool vodi = true;
        for (int i = 0; i < brojIgraca; i++) {
            if (i != trenutniIgrac && bodoviCricket[i] > bodoviCricket[trenutniIgrac]) {
                vodi = false;
                break;
            }
        }
        if (vodi) {
            logPoruka("Igrac " + igraci[trenutniIgrac].ime + " je zatvorio sve brojeve i vodi u bodovima!");
            logPoruka("POBJEDA!");
            zavrsiIgru();
            return;
        }
    }

    sljedeciIgrac_cricket();
}

void sljedeciIgrac_cricket() {
    trenutniIgrac = (trenutniIgrac + 1) % brojIgraca;
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
}

void resetirajIgru_cricket() {
    inicijalizirajIgru_cricket();
}
