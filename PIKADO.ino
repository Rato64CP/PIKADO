#include <Arduino.h>
#include "config.h"
#include "detection.h"
#include "buttons.h"
#include "game.h"
#include "game_301.h"

void setup() {
  Serial.begin(9600);
  inicijalizirajTipke();

  Serial.println("Odaberi broj igrača pritiskom na tipku (1–6):");
  while (brojIgraca == 0) {
    int odabir = provjeriOdabirIgraca();
    if (odabir > 0) {
      inicijalizirajIgrace(odabir);
      aktivnaIgra = Igra_301;
      inicijalizirajIgru_301();
    }
  }

  inicijalizirajMete();
}

void loop() {
  skenirajMete();        // poziva obradiPogodak_301(...)
  detektirajPromasaj();  // reagira ako netko promaši
  delay(10);
}