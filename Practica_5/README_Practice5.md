# Programming Practice 5 – UART Communication with Interrupts

## Overview

This practice builds upon previous projects and introduces **UART communication using interrupts** on an STM32-based embedded system. The goal is to modularize UART functionality, handle user input via serial terminal commands, and provide real-time interaction without blocking the main program execution.

The code is developed for the NUCLEO-F446RE board using **STM32CubeIDE** and the **HAL library**.

## Objectives

- Implement a UART communication module (`API_uart`) with send/receive functionality.
- Enable non-blocking **receive via interrupts** using `HAL_UART_Receive_IT()`.
- React to specific input characters from the user (e.g., `'c'`) sent through a serial terminal.
- When `'c'` is received:
  - Clear the terminal screen using ANSI escape codes.
  - Print the current UART configuration parameters in a readable format.
- Maintain compatibility with the **debounce-based button input** from Practice 4.

## Project Structure

The project builds on Practice 4, with a new module:

```
/Drivers
└── /API
    ├── /Inc
    │   ├── API_delay.h
    │   ├── API_debounce.h
    │   └── API_uart.h      ← New!
    └── /Src
        ├── API_delay.c
        ├── API_debounce.c
        └── API_uart.c      ← New!
```

## UART API

### API_uart.h

Provides:

- Initialization and utility:
  ```c
  bool_t uartInit(void);
  void uartSendString(uint8_t * pstring);
  void uartSendStringSize(uint8_t * pstring, uint16_t size);
  void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
  ```

- Interrupt-based command checking:
  ```c
  void uartCheckCommand_IT(void);
  ```

- Special actions:
  ```c
  void uartClearTerminal(void);
  void uartPrintConfig(void);
  ```

### API_uart.c

- Uses `HAL_UART_Receive_IT()` to handle single-byte reception via interrupt.
- Implements `HAL_UART_RxCpltCallback()` to flag reception and re-arm the interrupt.
- Reacts to the character `'c'` to clear the terminal and show configuration.
- Sends all data via `HAL_UART_Transmit()` using internal helper functions.

### UART Configuration Printed

Upon receiving `'c'`, the microcontroller clears the terminal (using `\033[2J\033[H`) and prints:

```
UART Config:
BaudRate: 115200
Word Length: 8 bits
Stop Bits: 1
Parity: None
```

> This is dynamically derived from the `huart2.Init` structure.

## Main Program (main.c)

- Initializes GPIO, UART, and the debounce state machine.
- Runs a **non-blocking LED blink** with changeable period using button press.
- Continuously checks for UART commands in the main loop via `uartCheckCommand_IT()`.
- Button debouncing and LED blinking logic is preserved from previous practices.

## Key Concepts

- **UART interrupts** enable non-blocking reception of data with minimal CPU usage.
- **ANSI escape codes** are used to interact with terminals that support screen control.
- **Modular design** separates UART functionality into an independent API.
- **State-driven logic** ensures proper handling of received characters only once.

## Terminal Compatibility

To interpret ANSI sequences like screen clearing:
- Use **RealTerm** (with “Ansi” mode enabled under the Display tab)
- Or **TeraTerm**, **PuTTY**, or **STM32CubeIDE Terminal** with ANSI enabled

If the terminal doesn’t support ANSI, `uartClearTerminal()` can be modified to print multiple `\r\n` lines as a workaround.

## Requirements

- STM32 HAL Library
- `USART2` configured and connected to the USB virtual COM port (ST-Link VCP)
- Terminal emulator with ANSI support (or fallback mode)

## Build Instructions

1. Import the project into STM32CubeIDE.
2. Ensure `/API/Inc` and `/API/Src` are included in the build paths.
3. Flash the code to the NUCLEO-F4xx board.
4. Open a serial terminal (RealTerm, TeraTerm, etc.) at `115200 8N1`.
5. Type `'c'` to trigger the UART config printout and terminal clear.