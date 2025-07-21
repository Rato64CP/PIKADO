#pragma once
#include <Arduino.h>
#include "notes.h"

struct Ton {
    uint16_t frekvencija; // Hz, 0 = pauza
    uint16_t trajanje;    // trajanje u milisekundama
};

void svirajMelodiju(const Ton* melodija, size_t duljina);

void svirajUvodnuMelodiju();
void svirajZvukBacanja();
void svirajZvukPromasaja();
void svirajZvukVadenja();
void svirajZvukNovogIgraca();
void svirajZvukPobjede();
void svirajZvukTipke();
