#pragma once
#include <Arduino.h>

// Zajednički pinovi
// Novi raspored zajedničkih pinova nakon prenamjene ploče
constexpr uint8_t COM_A15 = A15;  // bijela žica
constexpr uint8_t COM_A14 = A14;  // crna žica
constexpr uint8_t COM_A12 = A12;
constexpr uint8_t COM_A13 = A13;

// Pin za mikrofon
constexpr uint8_t PIN_MIKROFON = A0;
constexpr int THRESHOLD_PROMASAJ = 600;

// Pravila igre
constexpr bool BOUNCE_OUT = true;
extern bool DOUBLE_OUT;
extern bool DOUBLE_IN;

// Pinovi za JQ6500 MP3 modul (koristi se Serial1)
constexpr uint8_t PIN_JQ6500_TX = 18; // TX1 -> RX modula
constexpr uint8_t PIN_JQ6500_RX = 19; // RX1 -> TX modula
