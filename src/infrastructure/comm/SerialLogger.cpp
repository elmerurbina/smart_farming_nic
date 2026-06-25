#include "SerialLogger.h"

void SerialLogger::printNPK(const NPKData& d) {
    Serial.print("[NPK] N:");
    Serial.print(d.n);

    Serial.print(" P:");
    Serial.print(d.p);

    Serial.print(" K:");
    Serial.println(d.k);
}