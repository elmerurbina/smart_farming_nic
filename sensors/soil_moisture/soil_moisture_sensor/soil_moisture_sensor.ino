const int powerPin = 7;
const int sensorPin = A0;

void setup() {
    pinMode(powerPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(powerPin, HIGH);
    delay(10);

    int valor = analogRead(sensorPin);

    digitalWrite(powerPin, LOW);

    Serial.println(valor);

    delay(1000);
}