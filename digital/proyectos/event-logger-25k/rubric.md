# Rubrica - Event Logger 25K

| Desafio | Puntos | Descripcion | Minimo para aprobar |
|---------|--------|-------------|---------------------|
| 1 - Auditoria | 10 | 8 hallazgos en AUDITORIA.md | 6 hallazgos correctos |
| 2 - Logica combinacional | 8 | event_code_comb, hex_to_ascii, sevenseg_decoder | Sin latches |
| 3 - Clock enable y contadores | 10 | tick_enable, write_pointer | Tick periodico correcto |
| 4 - Sincronizacion y debounce | 10 | sync_2ff, debounce_onepulse | Un pulso por pulsacion |
| 5 - FSM | 12 | event_logger_fsm | Transiciones y prioridades |
| 6 - RAM 32x4 | 12 | ram32x4 | **Escritura/lectura correcta** |
| 7 - UART TX 8N1 | 14 | uart_tx | **Al menos una trama valida** |
| 8 - CDC toggle | 8 | cdc_pulse_toggle | Pulso unico en destino |
| 9 - Display e integracion | 8 | sevenseg_mux2, challenge_top | Instanciacion correcta |
| 10 - Testbench y timing | 8 | Testbenches y TIMING.md | 10 casos de prueba |
| **Total** | **100** | | **Minimo 70/100 (14/20)** |

## Criterios de penalizacion

| Infraccion | Penalizacion |
|------------|--------------|
| Sin testbench | Nota maxima 12/20 |
| Clocks derivados (counter[n]) | Nota maxima 14/20 |
| Entradas mecanicas directas a FSM | Nota maxima 14/20 |
| No simula antes de hardware | Practica no validada |
| Latches inferidos | -2 puntos por latch |
| Senales implicitas | -1 punto por senal |
