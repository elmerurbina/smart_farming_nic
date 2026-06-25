#include "NPKSensor.h"

NPKSensor::NPKSensor(uint8_t ro, uint8_t di, uint8_t re, uint8_t de)
    : mod(ro, di), RO(ro), DI(di), RE(re), DE(de) {}

void NPKSensor::begin() {
    mod.begin(4800);
    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
}

uint8_t NPKSensor::readValue(const byte query[8]) {

    while (mod.available()) mod.read();

    digitalWrite(RE, HIGH);
    digitalWrite(DE, HIGH);
    delay(10);

    mod.write(query, 8);
    mod.flush();

    digitalWrite(RE, LOW);
    digitalWrite(DE, LOW);

    unsigned long start = millis();
    while (mod.available() < 7 && (millis() - start < 2000)) {
        delay(1);
    }

    if (mod.available() >= 7) {
        for (int i = 0; i < 7; i++) {
            mod.read();
        }
        return mod.read(); // valor real
    }

    return 0;
}

NPKData NPKSensor::read() {
    NPKData data;

    data.n = readValue(n_query);
    delay(150);

    data.p = readValue(p_query);
    delay(150);

    data.k = readValue(k_query);

    return data;
}