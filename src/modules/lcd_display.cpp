#include "lcd_display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 16, 2);

void inicijalizirajLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void ispisiNaLCD(const String &poruka) {
    size_t len = poruka.length();
    size_t offset = 0;
    while (offset < len) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(poruka.substring(offset, offset + 16));
        if (offset + 16 < len) {
            lcd.setCursor(0, 1);
            lcd.print(poruka.substring(offset + 16, offset + 32));
        }
        offset += 32;
        if (offset < len) {
            delay(3000);
        }
    }
}

void logPoruka(const String &poruka) {
    Serial.println(poruka);
    ispisiNaLCD(poruka);
}
