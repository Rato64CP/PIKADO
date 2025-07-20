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
// Kada je BOUNCE_OUT uključen, prelazak ispod nule poništava potez ("bust")
constexpr bool BOUNCE_OUT = true;
// Kada je DOUBLE_OUT uključen, igrač mora završiti pogođeni niz na dvostrukom polju
constexpr bool DOUBLE_OUT = false;
