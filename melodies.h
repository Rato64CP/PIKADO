#pragma once
#include <Arduino.h>

void inicijalizirajZvuk();
void svirajUvodnuMelodiju();
void svirajZvukBacanja();
void svirajZvukPromasaja();
void svirajZvukVadenja();
void svirajZvukPobjede();
void svirajZvukTipke();
void svirajZvukNepostavljenaIgra();
// Pusti MP3 datoteku sa snimljenim imenom igrača (0-5)
void svirajImeIgraca(uint8_t index);
