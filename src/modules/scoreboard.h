#pragma once
#include <Arduino.h>

void inicijalizirajDisplay();
void prikaziBodove(uint8_t igrac, int bodovi);
void osvjeziSveBodove();
// Postavlja sve module na prikaz "---"
void ocistiDisplay();
// Privremeno prikazi ciljani broj na displayu igraca
void prikaziCilj(uint8_t igrac, int broj, unsigned long trajanjeMs);
// Gasi sve segmente na svim modulima
void ugasiDisplay();
// Blinka zadani broj na odabranom modulu
void blinkBroj(uint8_t igrac, int broj, uint8_t ponavljanja, unsigned int trajanjeMs);
