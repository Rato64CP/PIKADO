#pragma once
#include <Arduino.h>

// Funkcija prima polje stanja po redoslijedu enum-a Tipka (0-17)
// te ih mapira na odgovarajuce izlaze UCN5821 registri
void inicijalizirajZaruljice();
void postaviZaruljice(bool stanja[18]);
