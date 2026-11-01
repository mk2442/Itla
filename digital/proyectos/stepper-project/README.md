# Control Stepper 28BYJ-48 con ESP32 Super Mini (VS Code + PlatformIO)

## 1. Instalar requisitos
1. Instala **Visual Studio Code**.
2. Abre la pestaña de Extensiones (`Ctrl+Shift+X`) y busca **"PlatformIO IDE"**. Instálala y reinicia VS Code cuando te lo pida.

## 2. Abrir el proyecto
1. En VS Code: `File > Open Folder...` y selecciona esta carpeta (`stepper_project`).
2. PlatformIO detectará automáticamente el archivo `platformio.ini`.

## 3. Ajustar la placa (importante)
El archivo `platformio.ini` usa `board = esp32-s3-devkitm-1` porque muchas "ESP32 Super Mini" traen chip **ESP32-S3**.

- Si tu placa es la variante **ESP32-C3** o el chip original ESP32, cambia la línea `board` por una de estas opciones:
  - `board = esp32-c3-devkitm-1` (si es C3)
  - `board = esp32dev` (genérica, funciona en casi cualquier ESP32 clásico)
- Puedes verificar el chip exacto mirando la serigrafía de tu placa o el listado en: https://docs.platformio.org/en/latest/boards/index.html#espressif-32

## 4. Conectar los pines (ULN2003 -> ESP32)
| ULN2003 | ESP32 |
|---------|-------|
| IN1     | GPIO 1 |
| IN2     | GPIO 2 |
| IN3     | GPIO 3 |
| IN4     | GPIO 4 |
| VCC     | 5V (idealmente fuente externa) |
| GND     | GND común con el ESP32 |

Si usas otros pines, edítalos al inicio de `src/main.cpp` (líneas `#define IN1 ...`).

## 5. Compilar y subir
En la barra inferior de VS Code (iconos de PlatformIO):
- ✔️ (Build) — compila
- ➡️ (Upload) — compila y sube el código al ESP32
- 🔌 (Serial Monitor) — abre la terminal serial a 115200 baudios

También puedes usar `Ctrl+Alt+U` para subir, o desde la terminal:
```bash
pio run --target upload
pio device monitor
```

## 6. Usar la terminal de comandos
Con el Monitor Serial abierto, escribe y presiona Enter:

| Comando      | Función                                          |
|--------------|---------------------------------------------------|
| `M 500`      | Mueve 500 pasos adelante                          |
| `M -200`     | Mueve 200 pasos atrás                             |
| `V 12`       | Cambia la velocidad a 12 RPM                      |
| `S`          | Detiene el motor y libera las bobinas             |
| `R`          | Gira continuamente hacia adelante                 |
| `L`          | Gira continuamente hacia atrás                    |
| `H`          | Muestra la ayuda                                  |

## Notas
- El 28BYJ-48 usa ~4096 medios pasos por vuelta completa (con el reductor interno).
- El comando `S` libera las bobinas para evitar que el driver/motor se calienten en reposo.
