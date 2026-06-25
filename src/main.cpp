#include <Arduino.h>

#include "infrastructure/sensors/MoistureSensor.h"
#include "infrastructure/sensors/NPKSensor.h"
#include "infrastructure/display/OledDisplay.h"
#include "infrastructure/comm/SerialLogger.h"

// Soil moisture (ya existente)
MoistureSensor soilSensor(7, A0);

// NPK nuevo módulo
NPKSensor npk(2, 3, 4, 5);

// OLED (ya existente)
OledDisplay screen;

void setup() {
    Serial.begin(115200);

    soilSensor.begin();
    npk.begin();
    screen.begin();
}

void loop() {

    // 🌱 Soil moisture
    auto soil = soilSensor.read();

    // 🌾 NPK
    auto npkData = npk.read();

    // 📡 SERIAL MONITOR (todo junto)
    Serial.print("[SOIL] ADC=");
    Serial.print(soil.raw);
    Serial.print(" Humedad=");
    Serial.print(soil.percent);
    Serial.println("%");

    SerialLogger::printNPK(npkData);

    delay(2000);
}