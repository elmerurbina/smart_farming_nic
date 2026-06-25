#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int powerPin = 7;
const int sensorPin = A0;

// Historial para gráfica OLED
int graphData[128];

void setup() {

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);

  Serial.begin(115200);

  // Inicializar historial
  for (int i = 0; i < 128; i++) {
    graphData[i] = 0;
  }

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED no encontrada");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Iniciando");
  display.display();

  delay(2000);
}

void loop() {

  // Encender sensor
  digitalWrite(powerPin, HIGH);

  delay(500);

  int lectura = analogRead(sensorPin);

  // Apagar sensor
  digitalWrite(powerPin, LOW);

  // Convertir a porcentaje
  int humedad = map(lectura, 0, 1023, 0, 100);
  humedad = constrain(humedad, 0, 100);

  // =====================
  // MONITOR SERIAL
  // =====================
  Serial.print("Lectura=");
  Serial.print(lectura);
  Serial.print(" Humedad=");
  Serial.print(humedad);
  Serial.println("%");

  // =====================
  // SERIAL PLOTTER
  // =====================
  Serial.print("Sensor:");
  Serial.print(lectura);

  Serial.print(",");

  Serial.print("Humedad:");
  Serial.println(humedad);

  // =====================
  // ACTUALIZAR HISTORIAL
  // =====================
  for (int i = 0; i < 127; i++) {
    graphData[i] = graphData[i + 1];
  }

  graphData[127] = humedad;

  // =====================
  // OLED
  // =====================
  display.clearDisplay();

  // Título
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Monitor Humedad");

  // Valor
  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(humedad);
  display.println("%");

  // Lectura ADC
  display.setTextSize(1);
  display.setCursor(0, 34);
  display.print("ADC:");
  display.println(lectura);

  // Gráfica
  for (int x = 0; x < 127; x++) {

    int y1 = map(graphData[x], 0, 100, 63, 40);
    int y2 = map(graphData[x + 1], 0, 100, 63, 40);

    display.drawLine(x, y1, x + 1, y2, SSD1306_WHITE);
  }

  display.display();

  delay(500);
}