#pragma once
#include <Arduino.h>

struct MoistureData {
    int raw;
    int percent;
};

class MoistureSensor {
public:
    MoistureSensor(int powerPin, int analogPin);

    void begin();
    MoistureData read();

private:
    int _powerPin;
    int _analogPin;
};