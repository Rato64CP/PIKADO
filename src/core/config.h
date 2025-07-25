#pragma once
#include <Arduino.h>

// Zajednički pinovi
constexpr uint8_t COM_45 = 45;
constexpr uint8_t COM_47 = 47;
constexpr uint8_t COM_A1 = A1;
constexpr uint8_t COM_A2 = A2;

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
