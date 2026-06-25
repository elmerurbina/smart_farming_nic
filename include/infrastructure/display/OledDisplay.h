#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "infrastructure/sensors/MoistureSensor.h"

class OledDisplay {
public:
    OledDisplay();

    void begin();
    void render(MoistureData data);

private:
    Adafruit_SSD1306 display;
    int graph[128];
};