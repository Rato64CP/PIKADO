#pragma once
#include <Arduino.h>

class JQ6500 {
public:
    explicit JQ6500(HardwareSerial& serial) : _serial(serial) {}
    void begin() { _serial.begin(9600); }
    void play(uint16_t index) {
        uint8_t packet[] = {0x7E, 0x04, 0x03, uint8_t(index >> 8), uint8_t(index & 0xFF), 0xEF};
        _serial.write(packet, sizeof(packet));
    }
private:
    HardwareSerial& _serial;
};
