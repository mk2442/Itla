#define DW1  14
#define DW2  27
#define DW3  26
#define DW4  25
#define DW5  33
#define DW6  32
#define DW7  15
#define DW8  4
1
const int dwPins[] = {DW1, DW2, DW3, DW4, DW5, DW6, DW7, DW8};
const char* dwNames[] = {"DW1", "DW2", "DW3", "DW4", "DW5", "DW6", "DW7", "DW8"};

void apagarTodos() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(dwPins[i], LOW);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  for (int i = 0; i < 8; i++) {
    pinMode(dwPins[i], OUTPUT);
    digitalWrite(dwPins[i], LOW);
  }

  Serial.println("=================================");
  Serial.println("  TEST SALIDAS DW (OPTOCOPLADOR)");
  Serial.println("  RESTRICCION: SOLO 1 ACTIVO");
  Serial.println("=================================");
  Serial.println("Envia: 1-8 para activar DW");
  Serial.println("Envia: 0 para apagar todo");
  Serial.println("Envia: t para prueba automatica");
  Serial.println("=================================");
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "0") {
      apagarTodos();
      Serial.println(">> Todos apagados");
    }
    else if (cmd == "t") {
      Serial.println(">> Prueba automatica:");
      for (int i = 0; i < 8; i++) {
        apagarTodos();
        delay(100);

        digitalWrite(dwPins[i], HIGH);
        Serial.print("  ");
        Serial.print(dwNames[i]);
        Serial.print(" (GPIO ");
        Serial.print(dwPins[i]);
        Serial.println(") = ON");
        delay(1000);

        apagarTodos();
        delay(200);
      }
      Serial.println(">> Prueba completada");
    }
    else {
      int num = cmd.toInt();
      if (num >= 1 && num <= 8) {
        int idx = num - 1;

        apagarTodos();
        delay(100);

        digitalWrite(dwPins[idx], HIGH);

        Serial.print(">> ");
        Serial.print(dwNames[idx]);
        Serial.print(" (GPIO ");
        Serial.print(dwPins[idx]);
        Serial.println(") = ON");
      }
      else {
        Serial.println(">> Comando invalido (usa 0-8 o t)");
      }
    }
  }
}