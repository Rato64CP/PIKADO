#include <Arduino.h>
#include "config.h"
#include "detection.h"
#include "buttons.h"
#include "zaruljice.h"
#include "game.h"
#include "melodies.h"
#include "scoreboard.h"

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

  // Treperi lampica NEW_PLAYER dok se čekaju izbačene strelice
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

  // Prikaži odabrane DOUBLE IN/OUT opcije
  stanjeZaruljica[OSTALO_IN_CUTTHROAT] = DOUBLE_IN;
  stanjeZaruljica[OSTALO_OUT_TEAM] = DOUBLE_OUT;

  postaviZaruljice(stanjeZaruljica);
}

void setup() {
  Serial.begin(9600);
  inicijalizirajTipke();
  inicijalizirajZaruljice();
  inicijalizirajMete();
  inicijalizirajDisplay();
  inicijalizirajZvuk();

  Serial.println("Dobrodošli u PIKADO aparat!");
  svirajUvodnuMelodiju();

  // Test žaruljica
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 18; j++) stanjeZaruljica[j] = i % 2;
    postaviZaruljice(stanjeZaruljica);
    delay(300);
  }
  for (int j = 0; j < 18; j++) stanjeZaruljica[j] = false;
  postaviZaruljice(stanjeZaruljica);

  Serial.println("Odaberi igru pritiskom na tipku (301, 501...)");
  Serial.println("Zatim odaberi broj igrača pritiskom na tipku (1–6)");
}

void loop() {
  ocitajTipke();

  // -------------------- ODABIR IGRE --------------------
  if (odabranaIgra == -1) {
    for (int i = IGRA_301; i <= IGRA_3INLINE; i++) {
      if (tipkaStisnuta(i)) {
        odabranaIgra = i;
        Serial.print("Odabrana igra: "); Serial.println(i);
        svirajZvukTipke();
      }
    }

    unsigned long sada = millis();
    if (sada - zadnjeMijenjanje > 500) {
      zadnjeMijenjanje = sada;
      indeksIgre = (indeksIgre + 1) % 8;
    }

    for (int i = 0; i < 18; i++) stanjeZaruljica[i] = false;
    stanjeZaruljica[redoslijedIgara[indeksIgre]] = true;
    postaviZaruljice(stanjeZaruljica);
    delay(50);
    return;
  }

  // -------------------- ODABIR BROJA IGRACA --------------------
  if (odabraniBrojIgraca == -1) {
    for (int i = IGRAC_1; i <= IGRAC_6; i++) {
      if (tipkaStisnuta(i)) {
        odabraniBrojIgraca = i - IGRAC_1 + 1;
        Serial.print("Odabrano igraca: "); Serial.println(odabraniBrojIgraca);
        svirajZvukTipke();
      }
    }

    // Omogući odabir DOUBLE IN/OUT za igre 301, 501 i 701
    if (odabranaIgra == IGRA_301 || odabranaIgra == IGRA_501 || odabranaIgra == IGRA_701) {
      if (tipkaStisnuta(OSTALO_IN_CUTTHROAT)) doubleInOdabran = true;
      if (tipkaStisnuta(OSTALO_OUT_TEAM))   doubleOutOdabran = true;
    }

    unsigned long sada = millis();
    if (sada - zadnjeMijenjanje > 500) {
      zadnjeMijenjanje = sada;
      indeksIgraca = (indeksIgraca + 1) % 6;
    }

    for (int i = 0; i < 18; i++) stanjeZaruljica[i] = false;
    stanjeZaruljica[odabranaIgra] = true;
    stanjeZaruljica[redoslijedIgraca[indeksIgraca]] = true;
    stanjeZaruljica[OSTALO_IN_CUTTHROAT] = doubleInOdabran;
    stanjeZaruljica[OSTALO_OUT_TEAM] = doubleOutOdabran;
    postaviZaruljice(stanjeZaruljica);
    delay(50);
    return;
  }

  // -------------------- POCETAK IGRE --------------------
  if (odabranaIgra != -1 && odabraniBrojIgraca != -1) {
    // Postavi globalne opcije DOUBLE IN/OUT prema odabiru
    if (odabranaIgra == IGRA_301 || odabranaIgra == IGRA_501 || odabranaIgra == IGRA_701) {
      DOUBLE_IN = doubleInOdabran;
      DOUBLE_OUT = doubleOutOdabran;
    } else {
      DOUBLE_IN = false;
      DOUBLE_OUT = false;
    }

    if (DOUBLE_IN)  Serial.println("DOUBLE IN aktiviran");
    if (DOUBLE_OUT) Serial.println("DOUBLE OUT aktiviran");

    inicijalizirajIgrace(odabraniBrojIgraca);
    aktivnaIgra = static_cast<TipIgre>(odabranaIgra);
    pokreniAktivnuIgru();
    osvjeziZaruljiceIgra();
    cekanjeNovogIgraca = false;
    brojStrelica = 0;
    igraZavrsena = false;
    svirajZvukBacanja();
    svirajImeIgraca(trenutniIgrac);

    // Glavna igračka petlja
    while (!igraZavrsena) {
      ocitajTipke();
      osvjeziZaruljiceIgra();
      if (tipkaStisnuta(IGRA_RESET)) {
        resetirajAktivnuIgru();
        odabranaIgra = -1;
        odabraniBrojIgraca = -1;
        doubleInOdabran = false;
        doubleOutOdabran = false;
        DOUBLE_IN = false;
        DOUBLE_OUT = false;
        igraZavrsena = true;
        break;
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

    // Čekaj da korisnik pokrene novu igru
    while (igraZavrsena) {
      ocitajTipke();
      osvjeziZaruljiceIgra();
      if (tipkaStisnuta(IGRA_RESET)) {
        resetirajAktivnuIgru();
        odabranaIgra = -1;
        odabraniBrojIgraca = -1;
        doubleInOdabran = false;
        doubleOutOdabran = false;
        DOUBLE_IN = false;
        DOUBLE_OUT = false;
        break;
      }
      if (tipkaStisnuta(IGRA_NEW_PLAYER)) {
        resetirajAktivnuIgru();
        inicijalizirajIgrace(odabraniBrojIgraca);
        pokreniAktivnuIgru();
        cekanjeNovogIgraca = false;
        brojStrelica = 0;
        igraZavrsena = false;
      }
      delay(50);
    }
  }

  delay(50); // debounce
}
