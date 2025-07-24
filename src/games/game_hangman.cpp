#include "modules/lcd_display.h"
#include "games/game_hangman.h"
#include "core/game.h"
#include "core/config.h"
#include "modules/scoreboard.h"

bool pogodjeniBrojevi[21];       // 1–20
int greske[6];                  // broj grešaka po igraču
int bodoviHangman[6];           // bodovi po igraču
const int MAX_GRESAKA = 6;

void inicijalizirajIgru_hangman() {
    for (int i = 1; i <= 20; i++) pogodjeniBrojevi[i] = false;
    for (int i = 0; i < brojIgraca; i++) {
        greske[i] = 0;
        bodoviHangman[i] = 0;
        igraci[i].bodovi = 0;
    }
    trenutniIgrac = 0;
    logPoruka("Igra HANGMAN započinje!");
    logPoruka("Pogodi brojeve 1–20 bez ponavljanja.");
    logPoruka("Svaki igrač ima najviše 6 grešaka.");
    logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
    osvjeziSveBodove();
}

void obradiPogodak_hangman(const String& nazivMete) {
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

    if (broj < 1 || broj > 20) {
        logPoruka("Broj izvan raspona.");
        return;
    }

    if (pogodjeniBrojevi[broj]) {
        greske[trenutniIgrac]++;
        logPoruka("Već pogođeni broj – greška! (" + String(greske[trenutniIgrac]) + "/" + String(MAX_GRESAKA) + ")");

        if (greske[trenutniIgrac] >= MAX_GRESAKA) {
            logPoruka(igraci[trenutniIgrac].ime + " je izgubio (više od 6 grešaka)!");
            // Opcionalno: provjeri je li ostao samo 1 igrač aktivan
            return;
        }
    } else {
        pogodjeniBrojevi[broj] = true;
        int bodovi = broj * mnozitelj;
        bodoviHangman[trenutniIgrac] += bodovi;
        igraci[trenutniIgrac].bodovi = bodoviHangman[trenutniIgrac];
        logPoruka("Pogođeno " + String(broj) + " × " + String(mnozitelj) +
                       " = +" + String(bodovi) + " bodova (Ukupno: " + String(bodoviHangman[trenutniIgrac]) + ")");
        prikaziBodove(trenutniIgrac, igraci[trenutniIgrac].bodovi);
    }

    sljedeciIgrac_hangman();
}

void sljedeciIgrac_hangman() {
    int prethodni = trenutniIgrac;
    for (int i = 1; i <= brojIgraca; i++) {
        int sljedeci = (prethodni + i) % brojIgraca;
        if (greske[sljedeci] < MAX_GRESAKA) {
            trenutniIgrac = sljedeci;
            logPoruka("Na potezu: " + igraci[trenutniIgrac].ime);
            return;
        }
    }

    logPoruka("Nema više aktivnih igrača. Kraj igre!");
    // Prikaži rezultat
    int najvise = -1;
    int pobjednik = -1;
    for (int i = 0; i < brojIgraca; i++) {
        logPoruka("Igrač " + String(i) + ": " + String(bodoviHangman[i]) + " bodova");
        if (bodoviHangman[i] > najvise) {
            najvise = bodoviHangman[i];
            pobjednik = i;
        }
    }
    if (pobjednik != -1) {
        logPoruka("Pobjednik je IGRAČ " + String(pobjednik) + "!");
    }
    zavrsiIgru();
}

void resetirajIgru_hangman() {
    inicijalizirajIgru_hangman();
}
