#pragma once
#include <Arduino.h>

void inicijalizirajMete();
void detektirajPromasaj();
String detektirajZonu();
bool detektirajBacanjeBezIgre();
// Pozvati kada je detektirana ikakva radnja (tipka ili pogodak)
void registrirajInterakciju();
