/*
  Control de Stepper 28BYJ-48 con ESP32 Super Mini
  Driver: ULN2003
  Terminal serial para enviar comandos directamente.

  CONEXIONES (ajusta según tu cableado):
  ULN2003 IN1 -> GPIO 1
  ULN2003 IN2 -> GPIO 2
  ULN2003 IN3 -> GPIO 3
  ULN2003 IN4 -> GPIO 4
  ULN2003 VCC -> 5V (externo recomendado, no del ESP32 si es posible)
  ULN2003 GND -> GND común con el ESP32

  COMANDOS (escríbelos en el Monitor Serial a 115200 baudios y presiona Enter):
    M <pasos>     -> Mueve N pasos. Positivo = adelante, negativo = atrás.
                     Ej: M 500   |   M -200
    V <rpm>       -> Cambia la velocidad en RPM (ej: V 12)
    S             -> Detiene el motor y libera las bobinas (ahorra energía/evita calentamiento)
    R             -> Gira continuamente hacia adelante hasta nuevo comando
    L             -> Gira continuamente hacia atrás hasta nuevo comando
    H             -> Muestra la ayuda
*/

#include <Arduino.h>

// ---------- Configuración de pines ----------
#define IN1 1
#define IN2 2
#define IN3 3
#define IN4 4

// Secuencia de medio paso (más torque y suavidad) - 8 pasos
const uint8_t stepSequence[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

// El 28BYJ-48 tiene ~4096 medios pasos por vuelta (con reductor interno 1:64 aprox.)
const int STEPS_PER_REV = 4096;

int currentStep = 0;          // índice dentro de stepSequence (0-7)
float rpm = 10.0;             // velocidad por defecto
unsigned long stepDelayUs;    // delay entre medios pasos, calculado a partir de rpm

// Modo de giro continuo
enum RunMode { STOP, FORWARD_CONT, BACKWARD_CONT };
RunMode runMode = STOP;

unsigned long lastStepTime = 0;

void setPins(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
}

void releaseCoils() {
  setPins(0, 0, 0, 0);
}

void calcDelay() {
  // pasos por minuto = STEPS_PER_REV * rpm
  // delay entre pasos (us) = (60,000,000 us / pasos por minuto)
  if (rpm <= 0) rpm = 1;
  float stepsPerMinute = STEPS_PER_REV * rpm;
  stepDelayUs = (unsigned long)(60000000.0 / stepsPerMinute);
}

void doStep(int direction) {
  // direction: 1 = adelante, -1 = atrás
  currentStep += direction;
  if (currentStep > 7) currentStep = 0;
  if (currentStep < 0) currentStep = 7;

  setPins(stepSequence[currentStep][0],
          stepSequence[currentStep][1],
          stepSequence[currentStep][2],
          stepSequence[currentStep][3]);
}

void moveSteps(long steps) {
  int direction = (steps >= 0) ? 1 : -1;
  long totalSteps = abs(steps);

  Serial.print("Moviendo ");
  Serial.print(totalSteps);
  Serial.println(direction > 0 ? " pasos adelante..." : " pasos atras...");

  for (long i = 0; i < totalSteps; i++) {
    doStep(direction);
    delayMicroseconds(stepDelayUs);
  }

  releaseCoils();
  Serial.println("Movimiento completado.");
}

void printHelp() {
  Serial.println();
  Serial.println("=== Comandos disponibles ===");
  Serial.println("M <pasos>   Mueve N pasos (positivo=adelante, negativo=atras). Ej: M 500");
  Serial.println("V <rpm>     Cambia velocidad en RPM. Ej: V 12");
  Serial.println("S           Detiene y libera bobinas");
  Serial.println("R           Giro continuo hacia adelante");
  Serial.println("L           Giro continuo hacia atras");
  Serial.println("H           Muestra esta ayuda");
  Serial.println("=============================");
  Serial.println();
}

void processCommand(String cmd) {
  cmd.trim();
  if (cmd.length() == 0) return;

  char letter = toupper(cmd.charAt(0));
  String rest = cmd.substring(1);
  rest.trim();

  switch (letter) {
    case 'M': {
      runMode = STOP;
      long steps = rest.toInt();
      moveSteps(steps);
      break;
    }
    case 'V': {
      float newRpm = rest.toFloat();
      if (newRpm > 0) {
        rpm = newRpm;
        calcDelay();
        Serial.print("Velocidad ajustada a ");
        Serial.print(rpm);
        Serial.println(" RPM");
      } else {
        Serial.println("Valor de RPM invalido.");
      }
      break;
    }
    case 'S': {
      runMode = STOP;
      releaseCoils();
      Serial.println("Motor detenido y bobinas liberadas.");
      break;
    }
    case 'R': {
      runMode = FORWARD_CONT;
      Serial.println("Giro continuo hacia adelante. Envia 'S' para detener.");
      break;
    }
    case 'L': {
      runMode = BACKWARD_CONT;
      Serial.println("Giro continuo hacia atras. Envia 'S' para detener.");
      break;
    }
    case 'H': {
      printHelp();
      break;
    }
    default:
      Serial.println("Comando no reconocido. Envia 'H' para ver la ayuda.");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  releaseCoils();

  calcDelay();

  Serial.println();
  Serial.println("Control Stepper 28BYJ-48 - ESP32 Super Mini listo.");
  printHelp();
}

void loop() {
  // Leer comandos de la terminal serial
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    processCommand(cmd);
  }

  // Manejo de giro continuo (no bloqueante)
  if (runMode != STOP) {
    unsigned long now = micros();
    if (now - lastStepTime >= stepDelayUs) {
      lastStepTime = now;
      doStep(runMode == FORWARD_CONT ? 1 : -1);
    }
  }
}
