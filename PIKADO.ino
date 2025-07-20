#include <Arduino.h>
#include "config.h"
#include "detection.h"
#include "buttons.h"
#include "zaruljice.h"
#include "game.h"

// Definicija globalnih varijabli za odabir
int odabranaIgra = -1;
int odabraniBrojIgraca = -1;
bool stanjeZaruljica[18] = {false};
unsigned long zadnjeBlinkanje = 0;
bool blinkStanje = false;

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

  postaviZaruljice(stanjeZaruljica);
}

void setup() {
  Serial.begin(9600);
  inicijalizirajTipke();
  inicijalizirajZaruljice();
  inicijalizirajMete();
  pinMode(PIN_BUZZER, OUTPUT);

  Serial.println("Dobrodošli u PIKADO aparat!");

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

  // Odabir igre
  for (int i = IGRA_301; i <= IGRA_3INLINE; i++) {
    if (tipkaStisnuta(i)) {
      odabranaIgra = i;
      Serial.print("Odabrana igra: "); Serial.println(i);
    }
  }

  // Odabir broja igrača
  for (int i = IGRAC_1; i <= IGRAC_6; i++) {
    if (tipkaStisnuta(i)) {
      odabraniBrojIgraca = i - IGRAC_1 + 1;
      Serial.print("Odabrano igrača: "); Serial.println(odabraniBrojIgraca);
    }
  }

  // Ažuriraj žaruljice
  for (int i = 0; i < 18; i++) stanjeZaruljica[i] = false;
  if (odabranaIgra != -1) stanjeZaruljica[odabranaIgra] = true;
  if (odabraniBrojIgraca != -1)
    stanjeZaruljica[IGRAC_1 + odabraniBrojIgraca - 1] = true;

  postaviZaruljice(stanjeZaruljica);

  // Kada su obje opcije odabrane → pokreni igru
  if (odabranaIgra != -1 && odabraniBrojIgraca != -1) {
    inicijalizirajIgrace(odabraniBrojIgraca);
    aktivnaIgra = static_cast<TipIgre>(odabranaIgra);
    pokreniAktivnuIgru();
    osvjeziZaruljiceIgra();
    cekanjeNovogIgraca = false;
    brojStrelica = 0;
    igraZavrsena = false;

    // Glavna igračka petlja
    while (!igraZavrsena) {
      ocitajTipke();
      osvjeziZaruljiceIgra();
      if (tipkaStisnuta(IGRA_RESET)) {
        resetirajAktivnuIgru();
        odabranaIgra = -1;
        odabraniBrojIgraca = -1;
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
