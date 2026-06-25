#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>

struct NPKData {
    uint8_t n;
    uint8_t p;
    uint8_t k;
};

class NPKSensor {
public:
    NPKSensor(uint8_t ro, uint8_t di, uint8_t re, uint8_t de);

    void begin();
    NPKData read();

private:
    SoftwareSerial mod;

    uint8_t RO, DI, RE, DE;

    const byte n_query[8] = {0x01,0x03,0x00,0x1e,0x00,0x01,0xe4,0x0c};
    const byte p_query[8] = {0x01,0x03,0x00,0x1f,0x00,0x01,0xb5,0xcc};
    const byte k_query[8] = {0x01,0x03,0x00,0x20,0x00,0x01,0x85,0xc0};

    uint8_t readValue(const byte query[8]);
};