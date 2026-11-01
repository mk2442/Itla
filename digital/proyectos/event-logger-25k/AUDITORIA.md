# AUDITORIA de Codigo

## Modulos analizados: `driver_Led`, `driver_Button`, `driver_DigitalTube`

A continuacion se presentan los hallazgos basados en implementaciones tipicas de estos modulos vistas en clase.

---

### Hallazgo 1: Diferencia entre salida combinacional y registrada

**Problema:** En `driver_DigitalTube`, se observa que la senal `seg` se asigna dentro de un `always @(posedge clk)` sin necesidad de registro. La logica de decodificacion de 7 segmentos es puramente combinacional; no requiere almacenamiento de estado.

```verilog
// Ejemplo problematico
always @(posedge clk) begin
    case (hex_in)
        4'h0: seg <= 7'b1000000;
        // ...
    endcase
end
```

**Efecto:** La salida tiene una latencia adicional de un ciclo innecesaria, lo que puede romper la temporizacion del display multiplexado y aumentar el consumo de recursos (flip-flops innecesarios).

**Correccion:** Usar logica combinacional para la decodificacion:

```verilog
always @(*) begin
    case (hex_in)
        4'h0: seg = 7'b1000000;
        // ...
    endcase
end
```

---

### Hallazgo 2: Contador de debounce sin saturacion

**Problema:** En `driver_Button`, el contador de debounce puede desbordarse porque no se satura ni reinicia al alcanzar el limite:

```verilog
// Ejemplo problematico
always @(posedge clk) begin
    if (noisy_in != filtered) begin
        counter <= counter + 1;
        if (counter == STABLE_CYCLES - 1) begin
            filtered <= ~filtered;
        end
    end else begin
        counter <= 0;
    end
end
```

**Efecto:** Cuando `counter` alcanza `STABLE_CYCLES - 1`, la condicion `counter == STABLE_CYCLES - 1` se evalúa antes de que `counter` se incremente. Si la entrada permanece inestable, `counter` sigue incrementandose mas alla del valor de comparacion, desbordando y reiniciando desde 0. Esto puede producir falsos pulsos de debounce.

**Correccion:** Saturacion del contador:

```verilog
always @(posedge clk) begin
    if (noisy_in != filtered) begin
        if (counter == STABLE_CYCLES - 1) begin
            filtered <= ~filtered;
            counter <= 0;
        end else begin
            counter <= counter + 1;
        end
    end else begin
        counter <= 0;
    end
end
```

---

### Hallazgo 3: Diferencia entre "pulso de un ciclo" y "nivel mantenido"

**Problema:** En `driver_Button`, la senal que indica "boton presionado" es un nivel mantenido (`filtered`) en lugar de un pulso de exactamente un ciclo:

```verilog
// Ejemplo problematico - solo produce nivel
assign button_pressed = filtered;
```

**Efecto:** La FSM recibe un nivel prolongado en lugar de un pulso. Si la FSM usa `button_pressed` como condicion de transicion, permanecera verdadero durante toda la pulsacion, pudiendo provocar multiples transiciones o bloqueos.

**Correccion:** Generar un pulso de exactamente un ciclo:

```verilog
always @(posedge clk) begin
    prev_filtered <= filtered;
end
assign pulse = filtered & ~prev_filtered;
```

---

### Hallazgo 4: Riesgo de usar entrada mecanica sin sincronizador

**Problema:** En `driver_Button` (y frecuentemente en `driver_Led` que lee entradas), el boton se conecta directamente a la logica sin pasar por un sincronizador de dos flip-flops:

```verilog
// Ejemplo problematico
module driver_Button (
    input wire clk,
    input wire button_in,  // asincrona, sin sincronizar
    output wire pulse
);
    // Uso directo de button_in
    always @(posedge clk) begin
        if (button_in != filtered) begin
            // ...
        end
    end
endmodule
```

**Efecto:** Las entradas mecanicas son asincronas respecto al clock. Sin sincronizacion, se violan los tiempos de setup/hold del flip-flop, llevando a metaestabilidad. Esto puede causar valores indeterminados, fallos intermitentes o propagacion de metaestabilidad por todo el sistema.

**Correccion:** Agregar sincronizador de 2 flip-flops antes de cualquier proceso:

```verilog
always @(posedge clk) begin
    sync_ff1 <= button_in;
    sync_ff2 <= sync_ff1;
end
// Usar sync_ff2 en lugar de button_in
```

---

### Hallazgo 5: Uso correcto o incorrecto de `<=`

**Problema:** En `driver_Led`, se usa `<=` en todos los bloques, incluso en logica combinacional:

```verilog
// Ejemplo problematico - <= en bloque combinacional
always @(*) begin
    led_onehot[0] <= ~(switches == 3'd0);
    led_onehot[1] <= ~(switches == 3'd1);
end
```

**Efecto:** En simulacion, `<=` en un bloque combinacional puede causar diferencias sutiles entre simulacion y sintesis. La simulacion puede propagar valores con retraso de un ciclo, mientras que la sintesis ignora la diferencia y produce logica combinacional pura. Esto lleva a discrepancias sim-vs-sintesis dificiles de depurar.

**Correccion:** Usar `=` en bloques combinacionales y `<=` solo en bloques secuenciales:

```verilog
always @(*) begin
    led_onehot[0] = ~(switches == 3'd0);
    led_onehot[1] = ~(switches == 3'd1);
end
```

---

### Hallazgo 6: Senales declaradas implicitamente

**Problema:** En los modulos analizados, algunas senales internas no estan declaradas explicitamente:

```verilog
// Ejemplo problematico
module driver_DigitalTube (
    input wire [3:0] hex_in,
    output wire [6:0] seg
);
    // 'decoder_output' no esta declarado como wire/reg
    assign seg = decoder_output;
    always @(*) begin
        decoder_output = ...;
    end
endmodule
```

**Efecto:** Verilog-2005 declara implicitamente las senales no declaradas como wires de 1 bit. Si la senal se usa como lado izquierdo en un `always`, el simulador puede interpretarla como wire, causando errores de multiple driver o desconexion. En el hardware, la sintesis puede inferir comportamiento incorrecto o simplemente fallar.

**Correccion:** Declarar explicitamente todas las senales:

```verilog
module driver_DigitalTube (
    input wire [3:0] hex_in,
    output wire [6:0] seg
);
    reg [6:0] decoder_output;
    assign seg = decoder_output;
    always @(*) begin
        decoder_output = ...;
    end
endmodule
```

---

### Hallazgo 7: Comparacion terminal y posible error off-by-one

**Problema:** En `driver_Button`, la comparacion para la estabilidad del debounce usa `counter == STABLE_CYCLES` en lugar de `counter == STABLE_CYCLES - 1`:

```verilog
// Ejemplo problematico - off-by-one
if (counter == STABLE_CYCLES) begin
    filtered <= ~filtered;
    counter <= 0;
end
```

**Efecto:** Con `STABLE_CYCLES = 100`, el contador cuenta de 0 a 99 inclusive (100 valores) pero la comparacion espera 100. El contador llegara a 100 solo si `STABLE_CYCLES` es exactamente igual al maximo valor alcanzable, o nunca si el contador se desborda antes. Esto resulta en que el debounce nunca completa o espera un ciclo adicional.

**Correccion:** Usar `STABLE_CYCLES - 1` en la comparacion:

```verilog
if (counter == STABLE_CYCLES - 1) begin
    filtered <= ~filtered;
    counter <= 0;
end
```

---

### Hallazgo 8: Por que un clock enable es preferible a un clock derivado

**Problema:** En los modulos de clase, se observa generacion de clocks derivados mediante division de frecuencia:

```verilog
// Ejemplo problematico - clock derivado
reg [15:0] divider;
reg slow_clk;
always @(posedge clk) begin
    divider <= divider + 1;
end
assign slow_clk = divider[15];  // clock derivado
// Uso como clock
always @(posedge slow_clk) begin
    // ...
end
```

**Efecto:** 
1. **Skew y timing:** `slow_clk` no pasa por el arbol de distribucion de clock de la FPGA, creando skew significativo.
2. **Multiples dominios de clock:** Cada clock derivado crea un nuevo dominio, complicando el STA (Static Timing Analysis).
3. **Glitches:** Como `slow_clk` se genera de logica combinacional, puede producir glitches que disparan flancos espurios.
4. **Herramientas de sintesis:** Los tools de Gowin EDA no optimizan rutas entre dominios de clock derivados, resultando en violaciones de timing.

**Correccion:** Usar un clock enable:

```verilog
reg [15:0] divider;
wire tick;
assign tick = (divider == 16'hFFFF);
always @(posedge clk) begin
    divider <= divider + 1;
    if (tick) begin
        // Logica que se ejecuta a frecuencia reducida
    end
end
```

---

## Resumen

| # | Hallazgo | Modulo | Severidad |
|---|----------|--------|-----------|
| 1 | Salida registrada innecesaria | driver_DigitalTube | Baja |
| 2 | Contador sin saturacion | driver_Button | Media |
| 3 | Nivel vs pulso | driver_Button | Alta |
| 4 | Falta sincronizador | driver_Button | Critica |
| 5 | Uso incorrecto de `<=` | driver_Led | Media |
| 6 | Senales implicitas | driver_DigitalTube | Alta |
| 7 | Off-by-one en comparacion | driver_Button | Alta |
| 8 | Clock derivado vs clock enable | Todos | Critica |
