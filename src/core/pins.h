#pragma once
#include <Arduino.h>

// Shared dartboard common pins
constexpr uint8_t COM_A15 = A15; // bijela zica
constexpr uint8_t COM_A14 = A14; // crna zica
constexpr uint8_t COM_A12 = A12;
constexpr uint8_t COM_A13 = A13;

// Microphone input
constexpr uint8_t PIN_MIKROFON = A8;

// JQ6500 MP3 module (Serial1)
constexpr uint8_t PIN_JQ6500_TX = 18; // TX1 -> RX modula
constexpr uint8_t PIN_JQ6500_RX = 19; // RX1 -> TX modula

// LED lamps shift register (UCN5821)
constexpr uint8_t PIN_LED_DATA  = 2;
constexpr uint8_t PIN_LED_CLK   = 3;
constexpr uint8_t PIN_LED_LATCH = 4;

// MAX7219 scoreboard display
constexpr uint8_t PIN_SCORE_DIN = 9;
constexpr uint8_t PIN_SCORE_CLK = 10;
constexpr uint8_t PIN_SCORE_CS  = 11;

// Button pins (order matches enum Tipka)
static const uint8_t PIN_TIPKE[18] = {
    38, 40, 44, 34, 46, 36, 42, 32, 28, 30,
    33, 31, 29, 27, 25, 23,
    52, 50
};

// Dartboard sensor pins
constexpr uint8_t PIN_SENSOR_A0 = A0;
constexpr uint8_t PIN_SENSOR_A1 = A1;
constexpr uint8_t PIN_SENSOR_A2 = A2;
constexpr uint8_t PIN_SENSOR_A3 = A3;
constexpr uint8_t PIN_SENSOR_A4 = A4;
constexpr uint8_t PIN_SENSOR_A5 = A5;
constexpr uint8_t PIN_SENSOR_A6 = A6;
constexpr uint8_t PIN_SENSOR_A7 = A7;
constexpr uint8_t PIN_SENSOR_35 = 35;
constexpr uint8_t PIN_SENSOR_37 = 37;
constexpr uint8_t PIN_SENSOR_39 = 39;
constexpr uint8_t PIN_SENSOR_41 = 41;
constexpr uint8_t PIN_SENSOR_43 = 43;
constexpr uint8_t PIN_SENSOR_45 = 45;
constexpr uint8_t PIN_SENSOR_47 = 47;
constexpr uint8_t PIN_SENSOR_49 = 49;

// LCD I2C pins (reserved)
constexpr uint8_t PIN_LCD_SDA = 20;
constexpr uint8_t PIN_LCD_SCL = 21;
