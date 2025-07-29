#pragma once
#include <Arduino.h>

void inicijalizirajLCD();
void ispisiNaLCD(const String &poruka);
void logPoruka(const String &poruka);
void ispisiDvijeLinije(const String &red1, const String &red2);
void logPorukaDvijeLinije(const String &r1, const String &r2);
