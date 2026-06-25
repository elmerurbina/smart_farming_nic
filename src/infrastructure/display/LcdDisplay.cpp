#include "LcdDisplay.h"

LcdDisplay::LcdDisplay(uint8_t address, uint8_t cols, uint8_t rows)
    : lcd(address, cols, rows) {}

void LcdDisplay::begin() {

    // ⚠️ NO Wire.begin() aquí

    lcd.init();
    delay(50);
    lcd.backlight();
    delay(100);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Iniciando sistema");

    lcd.setCursor(0, 1);
    lcd.print("Sensores IoT");

    delay(2000);
    lcd.clear();
}

void LcdDisplay::render(MoistureData data, byte n, byte p, byte k) {

    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(data.percent);
    lcd.print("%   ");

    lcd.setCursor(0, 1);
    lcd.print("ADC: ");
    lcd.print(data.raw);
    lcd.print("     ");

    lcd.setCursor(0, 2);
    lcd.print("N:");
    lcd.print(n);
    lcd.print(" P:");
    lcd.print(p);
    lcd.print(" K:");
    lcd.print(k);
    lcd.print("   ");

    lcd.setCursor(0, 3);

    if (data.percent < 30) {
        lcd.print("Suelo SECO        ");
    } else if (data.percent < 70) {
        lcd.print("Humedad MEDIA     ");
    } else {
        lcd.print("Humedad ALTA      ");
    }
}