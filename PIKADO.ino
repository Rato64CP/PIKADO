#include <Arduino.h>
#include "src/core/config.h"
#include "src/modules/detection.h"
#include "src/modules/buttons.h"
#include "src/modules/zaruljice.h"
#include "src/core/game.h"
#include "src/modules/melodies.h"
#include "src/modules/scoreboard.h"
#include "src/modules/lcd_display.h"
#include "src/modules/error.h"
#include "src/modules/test.h"

// Definicija globalnih varijabli za odabir
int odabranaIgra = -1;
int odabraniBrojIgraca = -1;
bool stanjeZaruljica[18] = {false};
unsigned long zadnjeBlinkanje = 0;
bool blinkStanje = false;

// Odabir dodatnih pravila za 301/501
bool doubleInOdabran = false;
bool doubleOutOdabran = false;

const int redoslijedIgara[8] = {IGRA_3INLINE, IGRA_HANGMAN, IGRA_701, IGRA_301, IGRA_501, IGRA_CRICKET, IGRA_SHANGHAI, IGRA_ROULETTE};
const int redoslijedIgraca[6] = {IGRAC_1, IGRAC_2, IGRAC_3, IGRAC_4, IGRAC_5, IGRAC_6};
unsigned long zadnjeMijenjanje = 0;
int indeksIgre = 0;
int indeksIgraca = 0;
bool prvaTipkaPritisnuta = false;
bool igraPokrenuta = false;
bool porukaStartPrikazana = false;
bool startBlink = false;

static String nazivIgre(int tipka) {
  switch (tipka) {
    case IGRA_301:      return "301";
    case IGRA_501:      return "501";
    case IGRA_701:      return "701";
    case IGRA_SHANGHAI: return "Shanghai";
    case IGRA_HANGMAN:  return "Hangman";
    case IGRA_ROULETTE: return "Roulette";
    case IGRA_CRICKET:  return "Cricket";
    case IGRA_3INLINE:  return "3-in-line";
    default:            return String(tipka);
  }
}

// -------------------- Automaticki "sleep" nakon neaktivnosti --------------------
const unsigned long IDLE_TIMEOUT = 10UL * 60UL * 1000UL; // 10 min
const unsigned long IDLE_BLINK_INTERVAL = 5000UL;        // 5 sec
static unsigned long zadnjaInterakcija = 0;
static unsigned long zadnjiBlinkIdle = 0;
static bool idleMode = false;
static bool idleBlink = false;

// Test mode helpers - declared in test.h
bool resetHeld(unsigned long ms);
void testMode();
void provjeriTestMod();

bool biloKojaTipkaStisnuta();
void registrirajInterakciju();
static void azurirajNeaktivnost();

void osvjeziZaruljiceIgra() {
  for (int i = 0; i < 18; i++) stanjeZaruljica[i] = false;
  stanjeZaruljica[odabranaIgra] = true;

  int idxIgraca = IGRAC_1 + trenutniIgrac;
  if (!cekanjeNovogIgraca && brojStrelica == 0) {
    unsigned long sada = millis();
    if (sada - zadnjeBlinkanje > 500) {
      zadnjeBlinkanje = sada;
      blinkStanje = !blinkStanje;
    }
    stanjeZaruljica[idxIgraca] = blinkStanje;
  } else {
    stanjeZaruljica[idxIgraca] = true;
  }

  // Treperi lampica NEW_PLAYER dok se cekaju izbacene strelice
  if (cekanjeNovogIgraca) {
    unsigned long sada = millis();
    if (sada - zadnjeBlinkanje > 500) {
      zadnjeBlinkanje = sada;
      blinkStanje = !blinkStanje;
    }
    stanjeZaruljica[IGRA_NEW_PLAYER] = blinkStanje;
  } else {
    stanjeZaruljica[IGRA_NEW_PLAYER] = false;
  }

  // Prikazi odabrane DOUBLE IN/OUT opcije
  stanjeZaruljica[OSTALO_IN_CUTTHROAT] = DOUBLE_IN;
  stanjeZaruljica[OSTALO_OUT_TEAM] = DOUBLE_OUT;

  // Ako je aktivna greska, blinkaj RESET lampicom
  azurirajGresku();
  if (greskaAktivna()) {
    stanjeZaruljica[IGRA_RESET] = greskaBlinkStanje();
  }

  postaviZaruljice(stanjeZaruljica);
}

bool biloKojaTipkaStisnuta() {
  for (int i = 0; i < BROJ_TIPKI; i++) {
    if (tipkaStisnuta(i)) return true;
  }
  return false;
}

void registrirajInterakciju() {
  zadnjaInterakcija = millis();
  if (idleMode) {
    idleMode = false;
    idleBlink = false;
    osvjeziSveBodove();
    postaviZaruljice(stanjeZaruljica);
  }
}

static void azurirajNeaktivnost() {
  unsigned long sada = millis();
  if (!idleMode && sada - zadnjaInterakcija >= IDLE_TIMEOUT) {
    idleMode = true;
    idleBlink = false;
    ugasiDisplay();
    bool sveFalse[18] = {false};
    postaviZaruljice(sveFalse);
    zadnjiBlinkIdle = sada;
  }

  if (idleMode) {
    if (!idleBlink && sada - zadnjiBlinkIdle >= IDLE_BLINK_INTERVAL) {
      ocistiDisplay();
      idleBlink = true;
      zadnjiBlinkIdle = sada;
    } else if (idleBlink && sada - zadnjiBlinkIdle >= 500) {
      ugasiDisplay();
      idleBlink = false;
      zadnjiBlinkIdle = sada;
    }
  }
}

// Obrada pritiska tipke RESET. Prvi pritisak restartira trenutnu igru s istim
// postavkama. Ako se drugi pritisak dogodi unutar 1.5 sekunde, vraca se na
// pocetni izbornik.
static void obradiReset() {
  static unsigned long zadnjiReset = 0;
  static bool cekaDrugi = false;
  unsigned long sada = millis();

  bool dvostruki = cekaDrugi && (sada - zadnjiReset <= 1500);
  zadnjiReset = sada;
  cekaDrugi = !dvostruki;

  if (dvostruki) {
    // Povratak na izbornik
    resetirajAktivnuIgru();
    odabranaIgra = -1;
    odabraniBrojIgraca = -1;
    doubleInOdabran = false;
    doubleOutOdabran = false;
    DOUBLE_IN = false;
    DOUBLE_OUT = false;
    porukaStartPrikazana = false;
    igraPokrenuta = false;
    igraZavrsena = true;
  } else {
    // Ponovno pokretanje iste igre
    resetirajAktivnuIgru();
    inicijalizirajIgrace(odabraniBrojIgraca);
    pokreniAktivnuIgru();
    cekanjeNovogIgraca = false;
    brojStrelica = 0;
    igraZavrsena = false;
    svirajImeIgraca(trenutniIgrac);
  }

  // Pricekaj otpustanje tipke kako bismo izbjegli vise okidanja
  while (tipkaStisnuta(IGRA_RESET)) {
    ocitajTipke();
    delay(10);
  }
}

void setup() {
  Serial.begin(9600);
  inicijalizirajTipke();
  inicijalizirajLCD();
  inicijalizirajZaruljice();
  inicijalizirajMete();
  inicijalizirajDisplay();
  inicijalizirajZvuk();

  logPoruka("Dobrodosli!");
  svirajUvodnuMelodiju();
  delay(2000);

  // Test zaruljica
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 18; j++) stanjeZaruljica[j] = i % 2;
    postaviZaruljice(stanjeZaruljica);
    delay(300);
  }
  for (int j = 0; j < 18; j++) stanjeZaruljica[j] = false;
  postaviZaruljice(stanjeZaruljica);

  ocitajTipke();
  if (tipkaStisnuta(IGRA_RESET) && resetHeld(5000)) {
    testMode();
  }

  logPoruka("Odaberite igru i broj igraca");
}

void loop() {
  ocitajTipke();
  provjeriTestMod();
  bool stisnuta = biloKojaTipkaStisnuta();
  if (stisnuta) {
    registrirajInterakciju();
    if (!prvaTipkaPritisnuta) prvaTipkaPritisnuta = true;
  }
  azurirajNeaktivnost();

  if (!igraPokrenuta) {
    // ----- Prikupljanje odabira -----
    for (int i = IGRA_301; i <= IGRA_3INLINE; i++) {
      if (tipkaStisnuta(i)) {
        odabranaIgra = i;
        String msg = "Odabrana igra: " + nazivIgre(i);
        logPoruka(msg);
        svirajZvukTipke();
        delay(2000);
        if (odabraniBrojIgraca == -1) {
          logPoruka("Odaberite broj igraca");
          porukaStartPrikazana = false;
        } else {
          logPoruka("Pritisnite NEW PLAYER za pocetak igre");
          porukaStartPrikazana = true;
        }
      }
    }

    for (int i = IGRAC_1; i <= IGRAC_6; i++) {
      if (tipkaStisnuta(i)) {
        odabraniBrojIgraca = i - IGRAC_1 + 1;
        if (odabranaIgra != -1) {
          logPorukaDvijeLinije("Igra: " + nazivIgre(odabranaIgra),
                               "Igraci: " + String(odabraniBrojIgraca));
        } else {
          String msg = "Odabrano igraca: " + String(odabraniBrojIgraca);
          logPoruka(msg);
        }
        svirajZvukTipke();
        delay(2000);
        if (odabranaIgra == -1) {
          logPoruka("Odaberite igru");
          porukaStartPrikazana = false;
        } else {
          logPoruka("Pritisnite NEW PLAYER za pocetak igre");
          porukaStartPrikazana = true;
        }
      }
    }

    if (odabranaIgra == IGRA_301 || odabranaIgra == IGRA_501 || odabranaIgra == IGRA_701) {
      if (tipkaStisnuta(OSTALO_IN_CUTTHROAT))  doubleInOdabran = true;
      if (tipkaStisnuta(OSTALO_OUT_TEAM))    doubleOutOdabran = true;
    } else {
      doubleInOdabran = false;
      doubleOutOdabran = false;
    }

    // ----- LED indikacija -----
    for (int i = 0; i < 18; i++) stanjeZaruljica[i] = false;
    unsigned long sada = millis();
    if (!prvaTipkaPritisnuta) {
      if (sada - zadnjeMijenjanje > 500) {
        zadnjeMijenjanje = sada;
        indeksIgre = (indeksIgre + 1) % 8;
        indeksIgraca = (indeksIgraca + 1) % 6;
        startBlink = !startBlink;
      }
      stanjeZaruljica[redoslijedIgara[indeksIgre]] = true;
      stanjeZaruljica[redoslijedIgraca[indeksIgraca]] = true;
      stanjeZaruljica[IGRA_NEW_PLAYER] = startBlink;
      stanjeZaruljica[IGRA_RESET] = startBlink;
      stanjeZaruljica[OSTALO_IN_CUTTHROAT] = startBlink;
      stanjeZaruljica[OSTALO_OUT_TEAM] = startBlink;
    } else {
      if (odabranaIgra != -1) {
        stanjeZaruljica[odabranaIgra] = true;
      }
      if (odabraniBrojIgraca != -1) {
        stanjeZaruljica[IGRAC_1 + odabraniBrojIgraca - 1] = true;
      }
      stanjeZaruljica[OSTALO_IN_CUTTHROAT] = doubleInOdabran;
      stanjeZaruljica[OSTALO_OUT_TEAM] = doubleOutOdabran;
    }
    azurirajGresku();
    if (greskaAktivna()) {
      stanjeZaruljica[IGRA_RESET] = greskaBlinkStanje();
    }
    postaviZaruljice(stanjeZaruljica);

    {
      String razlog = detektirajBacanjeBezIgre();
      if (razlog != "") {
        logPoruka("Bacena strelica prije odabira! (" + razlog + ")");
        svirajZvukNepostavljenaIgra();
      }
    }

    if (!porukaStartPrikazana && odabranaIgra != -1 && odabraniBrojIgraca != -1) {
      logPoruka("Pritisnite NEW PLAYER za pocetak igre");
      porukaStartPrikazana = true;
    }

    // ----- Pokretanje igre -----
    if (odabranaIgra != -1 && odabraniBrojIgraca != -1 && tipkaStisnuta(IGRA_NEW_PLAYER)) {
      igraPokrenuta = true;
      porukaStartPrikazana = false;

      // Postavi globalne opcije DOUBLE IN/OUT prema odabiru
      if (odabranaIgra == IGRA_301 || odabranaIgra == IGRA_501 || odabranaIgra == IGRA_701) {
        DOUBLE_IN = doubleInOdabran;
        DOUBLE_OUT = doubleOutOdabran;
      } else {
        DOUBLE_IN = false;
        DOUBLE_OUT = false;
      }

    if (DOUBLE_IN)  logPoruka("DOUBLE IN aktiviran");
    if (DOUBLE_OUT) logPoruka("DOUBLE OUT aktiviran");

    inicijalizirajIgrace(odabraniBrojIgraca);
    aktivnaIgra = static_cast<TipIgre>(odabranaIgra);
    pokreniAktivnuIgru();
    osvjeziZaruljiceIgra();
    cekanjeNovogIgraca = false;
      brojStrelica = 0;
      igraZavrsena = false;
      svirajImeIgraca(trenutniIgrac);

    // Glavna igracka petlja
    while (!igraZavrsena) {
      ocitajTipke();
      provjeriTestMod();
      if (biloKojaTipkaStisnuta()) registrirajInterakciju();
      azurirajNeaktivnost();
      osvjeziZaruljiceIgra();
      if (tipkaStisnuta(IGRA_RESET)) {
        obradiReset();
        continue;
      }

      if (cekanjeNovogIgraca) {
        if (tipkaStisnuta(IGRA_NEW_PLAYER)) {
          sljedeciIgrac();
          cekanjeNovogIgraca = false;
        }
        delay(10);
        continue;
      }

      String pogodak = detektirajZonu(); // funkcija iz detection.cpp
      if (pogodak != "") {
        obradiPogodak(pogodak);
        if (igraZavrsena) {
          break; // zaustavi obradu ostatka iteracije
        }
      }

      detektirajPromasaj(); // ako postoji implementacija
      delay(10);
    }

    // Cekaj da korisnik pokrene novu igru
    while (igraZavrsena) {
      ocitajTipke();
      provjeriTestMod();
      if (biloKojaTipkaStisnuta()) registrirajInterakciju();
      azurirajNeaktivnost();
      osvjeziZaruljiceIgra();
      if (tipkaStisnuta(IGRA_RESET)) {
        obradiReset();
        if (!igraPokrenuta) break;
        continue;
      }
      if (tipkaStisnuta(IGRA_NEW_PLAYER)) {
        resetirajAktivnuIgru();
        inicijalizirajIgrace(odabraniBrojIgraca);
        pokreniAktivnuIgru();
        cekanjeNovogIgraca = false;
        porukaStartPrikazana = false;
        brojStrelica = 0;
        igraZavrsena = false;
      }
      delay(50);
    }
      igraPokrenuta = false;
    }
  }

  delay(50); // debounce
}
