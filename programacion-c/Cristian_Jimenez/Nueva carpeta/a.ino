#include <Arduino.h>

// Define el pin del LED (GPIO 2)
const int pinLED = 2;

void setup() {
  // Configura el pin como salida
  pinMode(pinLED, OUTPUT);
  // Inicializa la comunicación serial
  Serial.begin(115200);
  Serial.println("ESP32 iniciado");
}

void loop() {
  // Enciende el LED
  digitalWrite(pinLED, HIGH);
  Serial.println("LED encendido");
  delay(1000); // Espera 1 segundo
  
  // Apaga el LED
  digitalWrite(pinLED, LOW);
  Serial.println("LED apagado");
  delay(1000); // Espera 1 segundo
}