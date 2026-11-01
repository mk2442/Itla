# TIMING - Event Logger 25K

## Datos del sistema

### Frecuencia de reloj

La board Tang Primer 25K (GW5A-25) utiliza un oscilador externo de **27 MHz** conectado al pin de reloj principal.

- `Frecuencia i_clk`: **27.0 MHz**
- `Periodo de reloj`: **37.037 ns** (1 / 27e6)

### Baud rate UART

Se selecciona **115200 baud** como compromiso entre velocidad y robustez para depuracion por terminal serie.

### Calculo de CLKS_PER_BIT

```
CLKS_PER_BIT = frecuencia_clk / baud_rate
CLKS_PER_BIT = 27,000,000 / 115,200 = 234.375
```

Redondeo: **234** ciclos por bit.

Error porcentual:
```
Error = |234.375 - 234| / 234.375 * 100 = 0.16%
```

Este error esta dentro del margen tipico de tolerancia de UART (< 2%).

### Periodo de scan del display

El display multiplexado utiliza un tick enable con `SCAN_PERIOD = 10000`:

```
Frecuencia scan = 27,000,000 / 10000 = 2700 Hz
Periodo scan = 370.37 us
```

A 2700 Hz, cada digito se refresca a 1350 Hz, suficiente para evitar parpadeo visible (> 60 Hz por digito).

### Tiempo de debounce

Se usa `STABLE_CYCLES = 270000` con `COUNTER_WIDTH = 19`:

```
Tiempo debounce = STABLE_CYCLES * periodo_clk = 270000 * 37.037 ns = 10 ms
```

10 ms es el valor estandar para rebote de pulsadores mecanicos.

---

## Setup, Hold y Sincronizacion

### Setup y hold

- **Setup time (tsu)**: Tiempo minimo antes del flanco de reloj durante el cual el dato debe estar estable.
- **Hold time (th)**: Tiempo minimo despues del flanco de reloj durante el cual el dato debe permanecer estable.

Para la GW5A-25 (Gowin), los valores tipicos son:
- tsu ~ 0.5 ns
- th ~ 0.5 ns

### Violacion de setup/hold

Si una entrada cambia demasiado cerca del flanco de reloj, se viola tsu o th, y el flip-flop entra en **metaestabilidad**: la salida oscila o se estabiliza en un valor indeterminado despues de un tiempo impredecible.

### Por que las entradas asincronas requieren sincronizacion

Los botones y switches son entradas asincronas respecto al clock del sistema. Su transicion puede ocurrir en cualquier momento, incluso exactamente en el flanco de reloj. Sin sincronizacion:

1. El primer flip-flop que muestrea la entrada puede entrar en metaestabilidad.
2. Si la salida metaestable se propaga a otros flip-flops, el error se multiplica.
3. La FSM puede interpretar un valor no binario como un estado invalido.

La solucion es el **sincronizador de 2 flip-flops**: el primer flip-flop puede volverse metaestable, pero tiene un ciclo completo para estabilizarse antes de que el segundo flip-flop lo muestree. La probabilidad de que la metaestabilidad persista mas alla del segundo flip-flop es despreciable.

### Calculo de MTBF (Mean Time Between Failures)

Para la GW5A-25 a 27 MHz con sincronizador de 2 etapas, el MTBF tipico supera los **10^9 anos**, lo cual es aceptable para cualquier sistema de laboratorio.

---

## Declaracion de clock enables

**Este diseno no utiliza ningun clock derivado.**

Todos los procesos de frecuencia reducida se implementan exclusivamente mediante senales de **clock enable** generadas por `tick_enable`:

- `scan_tick`: enable para multiplexado del display (2700 Hz)
- `tick` interno en `uart_tx`: enable para conteo de baud rate
- Contador interno en `debounce_onepulse`: enable implicito (cada ciclo de reloj)

No existen asignaciones del tipo `assign slow_clk = counter[N]` ni `always @(posedge derived_clk)`. Todo el circuito opera en el dominio `i_clk` a 27 MHz.

---

## Resumen de parametros de hardware

| Parametro | Valor | Derivado de |
|-----------|-------|-------------|
| Frecuencia i_clk | 27.0 MHz | Oscilador de la board |
| Periodo i_clk | 37.037 ns | 1/27e6 |
| Baud rate | 115200 | Estandar serie |
| CLKS_PER_BIT | 234 | 27e6 / 115200 (redondeado) |
| Error baud rate | 0.16% | (234.375-234)/234.375 |
| SCAN_PERIOD | 10000 | 27e6 / 2700 Hz |
| Frecuencia scan | 2700 Hz | 27e6 / 10000 |
| STABLE_CYCLES | 270000 | 10 ms / 37.037 ns |
| Tiempo debounce | ~10 ms | 270000 * 37.037 ns |
| COUNTER_WIDTH | 19 | bits para 270000 |
