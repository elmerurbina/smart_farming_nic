#include <Arduino.h>
#include "infrastructure/sensors/MoistureSensor.h"
#include "infrastructure/display/OledDisplay.h"

MoistureSensor sensor(7, A0);
OledDisplay screen;

void setup() {
    Serial.begin(115200);

    sensor.begin();
    screen.begin();
}

void loop() {

    MoistureData data = sensor.read();

    Serial.print("ADC=");
    Serial.print(data.raw);
    Serial.print(" Humedad=");
    Serial.print(data.percent);
    Serial.println("%");

    // STREAM DATA (plotter)
    Serial.print("Sensor:");
    Serial.print(data.raw);
    Serial.print(",");
    Serial.print("Humedad:");
    Serial.println(data.percent);

    // UI LAYER
    screen.render(data);

    delay(500);
}