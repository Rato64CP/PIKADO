#pragma once
#include <Arduino.h>

void inicijalizirajMete();
void detektirajPromasaj();
String detektirajZonu();
// Returns reason for a pre-game throw: "MIC" or "COM_* -- pin"
String detektirajBacanjeBezIgre();
// Pozvati kada je detektirana ikakva radnja (tipka ili pogodak)
void registrirajInterakciju();
// Detekcija pogotka ili promasaja bez ikakvih game side-effecta.
// Vraca naziv mete ili "MIC" za promasaj.
String detektirajZonuTest();
