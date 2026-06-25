#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- CONFIGURACIÓN DE PINES ---
#define RO 2
#define DI 3
#define RE 4
#define DE 5

LiquidCrystal_I2C lcd(0x27, 20, 4); 
SoftwareSerial mod(RO, DI);

// Mensajes Modbus RTU estándar para sensores NPK
const byte n_query[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte p_query[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte k_query[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11]; 

void setup() {
  Serial.begin(9600);
  mod.begin(4800); // Velocidad estándar de estos sensores NPK
  
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  // Inicialización de Pantalla LCD
  Wire.begin();
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Prueba NPK IoT");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leer los 3 valores de forma secuencial
  byte valN = readSensor(n_query);
  delay(250); // Pausa obligatoria para no saturar el bus RS485
  byte valP = readSensor(p_query);
  delay(250);
  byte valK = readSensor(k_query);

  // --- DEBUG EN MONITOR SERIE ---
  Serial.print("Lecturas -> ");
  Serial.print("N: "); Serial.print(valN); Serial.print(" mg/kg | ");
  Serial.print("P: "); Serial.print(valP); Serial.print(" mg/kg | ");
  Serial.print("K: "); Serial.println(valK); Serial.print(" mg/kg");

  // --- IMPRESIÓN EN PANTALLA LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Nitrogeno: "); lcd.print(valN); lcd.print("    "); // Espacios para limpiar basura previa
  
  lcd.setCursor(0, 1);
  lcd.print("Fosforo:   "); lcd.print(valP); lcd.print("    ");
  
  lcd.setCursor(0, 2);
  lcd.print("Potasio:   "); lcd.print(valK); lcd.print("    ");

  delay(2000); // Esperar 2 segundos antes de la siguiente ráfaga de preguntas
}

byte readSensor(const byte query[]) {
  // Limpiar cualquier residuo en el búfer serial antes de enviar
  while(mod.available()) mod.read();

  // Modo Transmisión: Habilitar envío en el MAX485
  digitalWrite(RE, HIGH);
  digitalWrite(DE, HIGH);
  delay(10);
  
  mod.write(query, 8);
  mod.flush(); // Esperar a que se envíen físicamente todos los bytes

  // Modo Recepción: Escuchar la respuesta del sensor
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
  
  // Esperar a que lleguen al menos 7 bytes (Estructura Modbus: ID, Función, Longitud, Datos, CRC)
  unsigned long start = millis();
  while (mod.available() < 7 && (millis() - start < 3000)) { // Timeout aumentado a 3s
    delay(1);
  }

  // Si llegaron los datos correctos, leer el búfer
  if (mod.available() >= 7) {
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
    }
    return values[4]; // El byte 4 contiene el valor de la variable medida
  }
  
  return 0; // Si entra aquí, es que hubo Timeout (no hay comunicación física)
}