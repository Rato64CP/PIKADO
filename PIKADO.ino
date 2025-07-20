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
    igraZavrsena = false;

    // Glavna igračka petlja
    while (!igraZavrsena) {
      ocitajTipke();
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
      }

      detektirajPromasaj(); // ako postoji implementacija
      delay(10);
    }

    // Čekaj da korisnik pokrene novu igru
    while (igraZavrsena) {
      ocitajTipke();
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
        igraZavrsena = false;
      }
      delay(50);
    }
  }

  delay(50); // debounce
}
