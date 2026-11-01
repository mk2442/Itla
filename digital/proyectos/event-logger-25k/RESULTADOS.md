# RESULTADOS - Event Logger 25K

## Tabla de pruebas

| # | Prueba | Modulo | Resultado | Observaciones |
|---|--------|--------|-----------|---------------|
| 1 | Reset correcto | Todos | Pendiente | Verificar estado IDLE, contadores en 0 |
| 2 | Tick periodico (PERIOD=4) | tick_enable | Pendiente | Pulsos cada 4 ciclos |
| 3 | Boton con rebote | debounce_onepulse | Pendiente | Rebotes 0-1-0-1 no generan pulso |
| 4 | Pulsacion larga (un solo pulso) | debounce_onepulse | Pendiente | Nivel estable alto -> un pulso |
| 5 | RAM escritura addr 3 = A | ram32x4 | Pendiente | Lectura posterior entrega A |
| 6 | RAM escritura addr 7 = 5 | ram32x4 | Pendiente | Lectura posterior entrega 5 |
| 7 | RAM escritura addr 0 = F | ram32x4 | Pendiente | Direccion limite inferior |
| 8 | RAM escritura addr 31 = 1 | ram32x4 | Pendiente | Direccion limite superior |
| 9 | FSM: IDLE -> ARMED | event_logger_fsm | Pendiente | arm_pulse dispara transicion |
| 10 | FSM: ARMED -> CAPTURE -> ARMED | event_logger_fsm | Pendiente | capture_pulse + no full |
| 11 | FSM: ARMED -> TX -> ARMED | event_logger_fsm | Pendiente | tx_pulse + uart_busy |
| 12 | FSM: clear desde cualquier estado | event_logger_fsm | Pendiente | Prioridad de clear_pulse |
| 13 | FSM: mem_full bloquea capture | event_logger_fsm | Pendiente | Prioridad de mem_full |
| 14 | UART: 0x41 (ASCII 'A') | uart_tx | Pendiente | start, 10000010 LSB, stop |
| 15 | UART: 0x35 (ASCII '5') | uart_tx | Pendiente | start, 10101100 LSB, stop |
| 16 | UART: start ignorado si busy | uart_tx | Pendiente | Segundo start no afecta |
| 17 | CDC: pulso cruza dominios | cdc_pulse_toggle | Pendiente | Un pulso destino por pulso fuente |
| 18 | CDC: pulsos multiples sin perdida | cdc_pulse_toggle | Pendiente | 5 pulsos fuente -> 5 pulsos destino |
| 19 | Integracion: armar y capturar | challenge_top | Pendiente | Secuencia completa |
| 20 | Integracion: memoria llena | challenge_top | Pendiente | 32 escrituras, full flag |
| 21 | Integracion: display | challenge_top | Pendiente | Ultimo evento y contador |

## Resultados de simulacion

### Script de ejecucion

```bash
# Compilar y ejecutar todas las pruebas
cd event_logger_25k
iverilog -o sim/tb_tick_enable.vvp -s tb_tick_enable -I rtl tb/tb_tick_enable.v rtl/tick_enable.v
vvp sim/tb_tick_enable.vvp
```

### Cobertura

- [ ] Todas las pruebas pasan
- [ ] Sin latches inferidos
- [ ] Sin clocks derivados
- [ ] Sin warnings de sintesis
- [ ] Timing cerrado

### Reporte de sintesis

(Pendiente de ejecucion con Gowin EDA)

| Recurso | Utilizado | Disponible | % |
|---------|-----------|------------|---|
| Slice LUTs | - | - | - |
| Slice Registers | - | - | - |
| Block RAM | - | - | - |
| I/O | - | - | - |

### Reporte de timing

(Pendiente de ejecucion con Gowin EDA)

| Ruta | Slack | Frecuencia max |
|------|-------|----------------|
| setup | - | - |
| hold | - | - |

## Evidencia de hardware

(Pendiente de programacion en Tang Primer 25K)
