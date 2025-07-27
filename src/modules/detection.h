#pragma once
#include <Arduino.h>

void inicijalizirajMete();
void detektirajPromasaj();
String detektirajZonu();
// Returns reason for a pre-game throw ("MIC" for miss or field name)
String detektirajBacanjeBezIgre();
// Pozvati kada je detektirana ikakva radnja (tipka ili pogodak)
void registrirajInterakciju();
