#include "MoistureSensor.h"

MoistureSensor::MoistureSensor(int powerPin, int analogPin) {
    _powerPin = powerPin;
    _analogPin = analogPin;
}

void MoistureSensor::begin() {
    pinMode(_powerPin, OUTPUT);
    digitalWrite(_powerPin, LOW);
}

MoistureData MoistureSensor::read() {

    MoistureData data;

    digitalWrite(_powerPin, HIGH);
    delay(500);

    data.raw = analogRead(_analogPin);

    digitalWrite(_powerPin, LOW);

    data.percent = map(data.raw, 0, 1023, 0, 100);
    data.percent = constrain(data.percent, 0, 100);

    return data;
}