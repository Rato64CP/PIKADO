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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(poruka.substring(0, 16));
    if (poruka.length() > 16) {
        lcd.setCursor(0, 1);
        lcd.print(poruka.substring(16, 32));
    }
}

void logPoruka(const String &poruka) {
    Serial.println(poruka);
    ispisiNaLCD(poruka);
}
