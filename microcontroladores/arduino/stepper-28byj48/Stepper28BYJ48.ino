/*
 * Controlador Stepper 28BYJ-48 + ESP32 Super Mini
 * Terminal serial para envio de comandos
 *
 * Driver: ULN2003
 * Modo: Half-step (8 pasos por ciclo, 4096 pasos/rev)
 *
 * Conexion:
 *   IN1 -> GPIO 18
 *   IN2 -> GPIO 19
 *   IN3 -> GPIO 21
 *   IN4 -> GPIO 22
 *   VCC -> 5V (fuente externa recomendada)
 *   GND -> GND comun
 */

#include <Arduino.h>

// ======================== CONFIGURACION DE PINES ========================
#define PIN_IN1 18
#define PIN_IN2 19
#define PIN_IN3 21
#define PIN_IN4 22

// ======================== PARAMETROS DEL MOTOR ==========================
#define STEPS_PER_REV     4096   // Pasos porrevolucion (half-step)
#define MAX_SPEED_RPM     15     // Velocidad maxima segura (RPM)
#define DEFAULT_SPEED_RPM 8      // Velocidad por defecto

// ======================== SECUENCIA HALF-STEP ===========================
// 8 pasos para secuencia half-step (mas suave que full-step)
const uint8_t HALF_STEP[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

// ======================== VARIABLES GLOBALES ============================
volatile long stepPosition = 0;   // Posicion actual en pasos
volatile bool motorRunning = false;
volatile bool motorDirection = true;  // true = CW, false = CCW
volatile int motorSpeedRPM = DEFAULT_SPEED_RPM;

int stepIndex = 0;                // Indice actual en la secuencia
bool continuousMode = false;      // Modo rotacion continua

// ======================== FUNCIONES DEL MOTOR ===========================

void setCoils(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  digitalWrite(PIN_IN1, a);
  digitalWrite(PIN_IN2, b);
  digitalWrite(PIN_IN3, c);
  digitalWrite(PIN_IN4, d);
}

void disableCoils() {
  setCoils(0, 0, 0, 0);
}

// Calcula delay en microsegundos entre pasos segun RPM
unsigned long stepDelayFromRPM(int rpm) {
  if (rpm <= 0) rpm = 1;
  if (rpm > MAX_SPEED_RPM) rpm = MAX_SPEED_RPM;
  // half-step: 8 micro-pasos por paso, 4096 pasos/rev
  // delay = 60s / (rpm * 4096) = tiempo entre cada micro-paso
  unsigned long us = 60000000UL / ((unsigned long)rpm * STEPS_PER_REV);
  return us;
}

// Ejecuta un solo paso en la direccion indicada
void doStep(bool clockwise) {
  if (clockwise) {
    stepIndex = (stepIndex + 1) % 8;
    stepPosition++;
  } else {
    stepIndex = (stepIndex - 1 + 8) % 8;
    stepPosition--;
  }
  setCoils(
    HALF_STEP[stepIndex][0],
    HALF_STEP[stepIndex][1],
    HALF_STEP[stepIndex][2],
    HALF_STEP[stepIndex][3]
  );
}

// Mueve N pasos (positivo = CW, negativo = CCW)
void moveSteps(long steps) {
  bool dir = (steps > 0);
  long count = abs(steps);
  unsigned long delayUs = stepDelayFromRPM(motorSpeedRPM);

  motorRunning = true;
  for (long i = 0; i < count; i++) {
    doStep(dir);
    delayMicroseconds(delayUs);
  }
  disableCoils();
  motorRunning = false;
}

// Mueve a una posicion absoluta en pasos
void moveToPosition(long target) {
  long diff = target - stepPosition;
  moveSteps(diff);
}

// Mueve a un angulo en grados (0-360)
void moveToAngle(float angle) {
  long targetSteps = (long)((angle / 360.0) * STEPS_PER_REV);
  moveToPosition(targetSteps);
}

// ======================== TERMINAL SERIAL ===============================

void printHelp() {
  Serial.println(F("========================================"));
  Serial.println(F("  Controlador 28BYJ-48 - ESP32 Mini"));
  Serial.println(F("========================================"));
  Serial.println(F("Comandos:"));
  Serial.println(F("  help              - Muestra esta ayuda"));
  Serial.println(F("  status            - Muestra estado actual"));
  Serial.println(F("  pos               - Muestra posicion actual"));
  Serial.println(F("  home              - Regresa a posicion 0"));
  Serial.println(F("  speed <rpm>       - Velocidad (1-15 RPM)"));
  Serial.println(F("  move <pasos>      - Mueve N pasos (+/-)"));
  Serial.println(F("  angle <grados>    - Mueve a angulo (0-360)"));
  Serial.println(F("  cw                - Giro horario continuo"));
  Serial.println(F("  ccw               - Giro antihorario continuo"));
  Serial.println(F("  stop              - Detiene el motor"));
  Serial.println(F("  steps/rev         - Muestra pasos por rev"));
  Serial.println(F("  reset             - Resetea posicion a 0"));
  Serial.println(F("========================================"));
}

void printStatus() {
  Serial.println(F("--- Estado del Motor ---"));
  Serial.print(F("  Posicion:    "));
  Serial.print(stepPosition);
  Serial.print(F(" pasos ("));
  float deg = (float)stepPosition / STEPS_PER_REV * 360.0;
  Serial.print(deg, 1);
  Serial.println(F(" grados)"));
  Serial.print(F("  Velocidad:   "));
  Serial.print(motorSpeedRPM);
  Serial.println(F(" RPM"));
  Serial.print(F("  Estado:      "));
  Serial.println(motorRunning ? F("Moviendo") : F("Detenido"));
  Serial.print(F("  Modo:        "));
  Serial.println(continuousMode ? F("Continuo") : F("Pasos"));
  Serial.print(F("  Pasos/rev:   "));
  Serial.println(STEPS_PER_REV);
}

// Procesa un comando recibido por serial
void processCommand(String cmd) {
  cmd.trim();
  cmd.toLowerCase();

  if (cmd.length() == 0) return;

  // Separar comando y argumento
  int spaceIdx = cmd.indexOf(' ');
  String command = (spaceIdx > 0) ? cmd.substring(0, spaceIdx) : cmd;
  String argStr = (spaceIdx > 0) ? cmd.substring(spaceIdx + 1) : "";
  argStr.trim();

  // --- help ---
  if (command == "help" || command == "h" || command == "?") {
    printHelp();
  }
  // --- status ---
  else if (command == "status" || command == "st") {
    printStatus();
  }
  // --- pos ---
  else if (command == "pos" || command == "p") {
    Serial.print(F("Pos: "));
    Serial.print(stepPosition);
    Serial.print(F(" | "));
    float deg = (float)stepPosition / STEPS_PER_REV * 360.0;
    Serial.print(deg, 1);
    Serial.println(F(" deg"));
  }
  // --- home ---
  else if (command == "home" || command == "home") {
    Serial.print(F("Regresando a home..."));
    long diff = 0 - stepPosition;
    Serial.print(F(" ("));
    Serial.print(diff);
    Serial.println(F(" pasos)"));
    continuousMode = false;
    moveToPosition(0);
    disableCoils();
    Serial.println(F("OK - En home"));
  }
  // --- speed ---
  else if (command == "speed" || command == "spd") {
    if (argStr.length() == 0) {
      Serial.print(F("Velocidad actual: "));
      Serial.print(motorSpeedRPM);
      Serial.println(F(" RPM"));
      return;
    }
    int spd = argStr.toInt();
    if (spd < 1) spd = 1;
    if (spd > MAX_SPEED_RPM) spd = MAX_SPEED_RPM;
    motorSpeedRPM = spd;
    Serial.print(F("Velocidad: "));
    Serial.print(motorSpeedRPM);
    Serial.println(F(" RPM"));
  }
  // --- move ---
  else if (command == "move" || command == "m") {
    if (argStr.length() == 0) {
      Serial.println(F("Uso: move <pasos> (ej: move 1024, move -2048)"));
      return;
    }
    long steps = argStr.toInt();
    if (steps == 0) {
      Serial.println(F("Numero de pasos invalido"));
      return;
    }
    continuousMode = false;
    Serial.print(F("Moviendo "));
    Serial.print(steps);
    Serial.println(F(" pasos..."));
    moveSteps(steps);
    disableCoils();
    Serial.print(F("OK - Pos: "));
    Serial.println(stepPosition);
  }
  // --- angle ---
  else if (command == "angle" || command == "a") {
    if (argStr.length() == 0) {
      Serial.println(F("Uso: angle <grados> (ej: angle 90, angle -45)"));
      return;
    }
    float angle = argStr.toFloat();
    continuousMode = false;
    Serial.print(F("Moviendo a "));
    Serial.print(angle, 1);
    Serial.println(F(" grados..."));
    moveToAngle(angle);
    disableCoils();
    Serial.print(F("OK - Pos: "));
    Serial.print(stepPosition);
    Serial.print(F(" ("));
    float deg = (float)stepPosition / STEPS_PER_REV * 360.0;
    Serial.print(deg, 1);
    Serial.println(F(" deg)"));
  }
  // --- cw ---
  else if (command == "cw") {
    continuousMode = true;
    motorDirection = true;
    motorRunning = true;
    Serial.println(F("Rotacion continua HORARIA (cw) - 'stop' para detener"));
    unsigned long delayUs = stepDelayFromRPM(motorSpeedRPM);
    while (continuousMode) {
      doStep(true);
      delayMicroseconds(delayUs);
      // Check serial for stop command
      if (Serial.available()) {
        String check = Serial.readStringUntil('\n');
        check.trim();
        check.toLowerCase();
        if (check == "stop" || check == "s") {
          continuousMode = false;
          break;
        }
      }
    }
    disableCoils();
    motorRunning = false;
    Serial.println(F("Motor detenido"));
    Serial.print(F("Pos: "));
    Serial.println(stepPosition);
  }
  // --- ccw ---
  else if (command == "ccw") {
    continuousMode = true;
    motorDirection = false;
    motorRunning = true;
    Serial.println(F("Rotacion continua ANTIHORARIA (ccw) - 'stop' para detener"));
    unsigned long delayUs = stepDelayFromRPM(motorSpeedRPM);
    while (continuousMode) {
      doStep(false);
      delayMicroseconds(delayUs);
      if (Serial.available()) {
        String check = Serial.readStringUntil('\n');
        check.trim();
        check.toLowerCase();
        if (check == "stop" || check == "s") {
          continuousMode = false;
          break;
        }
      }
    }
    disableCoils();
    motorRunning = false;
    Serial.println(F("Motor detenido"));
    Serial.print(F("Pos: "));
    Serial.println(stepPosition);
  }
  // --- stop ---
  else if (command == "stop" || command == "s") {
    continuousMode = false;
    motorRunning = false;
    disableCoils();
    Serial.println(F("Motor detenido"));
    Serial.print(F("Pos: "));
    Serial.println(stepPosition);
  }
  // --- reset ---
  else if (command == "reset" || command == "rst") {
    stepPosition = 0;
    disableCoils();
    Serial.println(F("Posicion reseteada a 0"));
  }
  // --- steps/rev ---
  else if (command == "steps/rev" || command == "spr") {
    Serial.print(F("Pasos por revolucion: "));
    Serial.println(STEPS_PER_REV);
  }
  // --- Comando desconocido ---
  else {
    Serial.print(F("Comando desconocido: '"));
    Serial.print(command);
    Serial.println(F("' - Escribe 'help' para ver comandos"));
  }
}

// ======================== SETUP =========================================
void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }

  // Configurar pines de salida
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  disableCoils();

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("  Stepper 28BYJ-48 - ESP32 Super Mini"));
  Serial.println(F("========================================"));
  Serial.print(F("Pines: IN1=GPIO"));
  Serial.print(PIN_IN1);
  Serial.print(F(" IN2=GPIO"));
  Serial.print(PIN_IN2);
  Serial.print(F(" IN3=GPIO"));
  Serial.print(PIN_IN3);
  Serial.print(F(" IN4=GPIO"));
  Serial.println(PIN_IN4);
  Serial.print(F("Pasos/rev: "));
  Serial.println(STEPS_PER_REV);
  Serial.print(F("Velocidad: "));
  Serial.print(motorSpeedRPM);
  Serial.println(F(" RPM"));
  Serial.println(F("Escribe 'help' para ver comandos"));
  Serial.println(F("========================================"));
  Serial.print(F("> "));
}

// ======================== LOOP ==========================================
String inputBuffer = "";

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        Serial.println();
        processCommand(inputBuffer);
        inputBuffer = "";
        Serial.print(F("\n> "));
      }
    } else if (c == '\b' || c == 127) {
      // Backspace
      if (inputBuffer.length() > 0) {
        inputBuffer.remove(inputBuffer.length() - 1);
        Serial.print(F("\b \b"));
      }
    } else if (c >= 32 && c < 127) {
      inputBuffer += c;
      Serial.print(c);  // Echo
    }
  }
}
