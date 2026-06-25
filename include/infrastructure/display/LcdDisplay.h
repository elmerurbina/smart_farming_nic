#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "infrastructure/sensors/MoistureSensor.h"

class LcdDisplay {
public:
    LcdDisplay(uint8_t address = 0x27, uint8_t cols = 20, uint8_t rows = 4);

    void begin();
    void render(MoistureData data, byte n, byte p, byte k);

private:
    LiquidCrystal_I2C lcd;
};