#include <Arduino.h>
#include <Wire.h>

#include "infrastructure/sensors/MoistureSensor.h"
#include "infrastructure/sensors/NPKSensor.h"
#include "infrastructure/display/LcdDisplay.h"
#include "infrastructure/comm/SerialLogger.h"

// 🌱 Sensor de humedad
MoistureSensor soilSensor(7, A0);

// 🌾 NPK RS485
NPKSensor npk(2, 3, 4, 5);

// 📟 LCD
LcdDisplay screen;

void setup() {

    Serial.begin(115200);

    // ⚠️ IMPORTANTE: I2C primero
    Wire.begin();
    delay(50);

    // Inicialización sensores
    soilSensor.begin();
    npk.begin();

    // LCD
    screen.begin();

    Serial.println("Sistema IoT iniciado correctamente");
}

void loop() {

    // 🌱 humedad
    auto soil = soilSensor.read();

    // 🌾 NPK
    auto npkData = npk.read();

    // 📡 debug serial
    Serial.println("===== LECTURAS =====");

    Serial.print("[SOIL] ADC=");
    Serial.print(soil.raw);
    Serial.print(" Humedad=");
    Serial.print(soil.percent);
    Serial.println("%");

    SerialLogger::printNPK(npkData);

    Serial.println("====================");

    // 📟 LCD
    screen.render(
        soil,
        npkData.n,
        npkData.p,
        npkData.k
    );

    delay(2000);
}