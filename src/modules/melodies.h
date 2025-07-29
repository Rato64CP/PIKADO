#pragma once
#include <Arduino.h>

void inicijalizirajZvuk();
void svirajUvodnuMelodiju();
void svirajZvukPromasaja();
void svirajZvukVadenja();
void svirajZvukPobjede();
void svirajZvukTipke();
void svirajZvukNepostavljenaIgra();
void svirajZvukBust();
// Pusti MP3 datoteku sa snimljenim imenom igraca (0-5)
void svirajImeIgraca(uint8_t index);
// Reproduciraj najavu pogodene mete
void svirajZvukMete(const String& nazivMete);
void svirajZvukRouletteStart();
void najaviCiljaniBroj(int broj);
void svirajZvukTargetHit();
void svirajZvukRouletteOver();
void svirajZvukShanghai();
void svirajZvukTryAgain();
