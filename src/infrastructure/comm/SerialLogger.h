#pragma once
#include <Arduino.h>
#include "infrastructure/sensors/NPKSensor.h"

class SerialLogger {
public:
    static void printNPK(const NPKData& data);
};