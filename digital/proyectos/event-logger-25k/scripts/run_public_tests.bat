@echo off
setlocal enabledelayedexpansion

set RTL_DIR=..\rtl
set TB_DIR=..\tb
set SIM_DIR=..\sim
set IVL=iverilog
set VVP=vvp

if not exist "%SIM_DIR%" mkdir "%SIM_DIR%"

echo ========================================
echo  Event Logger 25K - Public Test Suite
echo ========================================

set RTL_FILES=%RTL_DIR%\tick_enable.v %RTL_DIR%\write_pointer.v %RTL_DIR%\sync_2ff.v %RTL_DIR%\debounce_onepulse.v %RTL_DIR%\event_code_comb.v %RTL_DIR%\hex_to_ascii.v %RTL_DIR%\sevenseg_decoder.v %RTL_DIR%\event_logger_fsm.v %RTL_DIR%\ram32x4.v %RTL_DIR%\uart_tx.v %RTL_DIR%\cdc_pulse_toggle.v %RTL_DIR%\sevenseg_mux2.v %RTL_DIR%\challenge_top.v

echo.
echo --- Test 1: tick_enable ---
%IVL% -o %SIM_DIR%\tb_tick_enable.vvp -s tb_tick_enable -I %RTL_DIR% %TB_DIR%\tb_tick_enable.v %RTL_DIR%\tick_enable.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_tick_enable.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 2: debounce_onepulse ---
%IVL% -o %SIM_DIR%\tb_debounce_onepulse.vvp -s tb_debounce_onepulse -I %RTL_DIR% %TB_DIR%\tb_debounce_onepulse.v %RTL_DIR%\debounce_onepulse.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_debounce_onepulse.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 3: RAM 32x4 ---
%IVL% -o %SIM_DIR%\tb_ram32x4.vvp -s tb_ram32x4 -I %RTL_DIR% %TB_DIR%\tb_ram32x4.v %RTL_DIR%\ram32x4.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_ram32x4.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 4: Event Logger FSM ---
%IVL% -o %SIM_DIR%\tb_event_logger_fsm.vvp -s tb_event_logger_fsm -I %RTL_DIR% %TB_DIR%\tb_event_logger_fsm.v %RTL_DIR%\event_logger_fsm.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_event_logger_fsm.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 5: UART TX ---
%IVL% -o %SIM_DIR%\tb_uart_tx.vvp -s tb_uart_tx -I %RTL_DIR% %TB_DIR%\tb_uart_tx.v %RTL_DIR%\uart_tx.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_uart_tx.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 6: CDC Pulse Toggle ---
%IVL% -o %SIM_DIR%\tb_cdc_pulse_toggle.vvp -s tb_cdc_pulse_toggle -I %RTL_DIR% %TB_DIR%\tb_cdc_pulse_toggle.v %RTL_DIR%\cdc_pulse_toggle.v
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_cdc_pulse_toggle.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo --- Test 7: Challenge Top (Integration) ---
%IVL% -o %SIM_DIR%\tb_challenge_top.vvp -s tb_challenge_top -I %RTL_DIR% %TB_DIR%\tb_challenge_top.v %RTL_FILES%
if !errorlevel! equ 0 (
    %VVP% %SIM_DIR%\tb_challenge_top.vvp
) else (
    echo  FAIL: Compilation error
)

echo.
echo ========================================
echo  All tests completed.
echo ========================================
pause
