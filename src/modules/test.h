#pragma once
#include <Arduino.h>

// Provjerava je li tipka RESET drzena odredeni broj milisekundi
bool resetHeld(unsigned long ms);

// Ulazi u testni mod dok se ne pritisne RESET 5 sekundi ili ne ugasi uredjaj
void testMode();
