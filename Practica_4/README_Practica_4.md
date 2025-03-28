# Programming Practice 4 – Debounce State Machine

## Overview

This practice builds upon Practice 3 and focuses on implementing a **debounce state machine (FSM)** using **non-blocking delays**. The goal is to robustly detect button presses on the NUCLEO-F4 board while maintaining a **modular and portable code structure**, decoupling hardware-specific logic from the FSM.

## Objectives

- Implement a **finite state machine (FSM)** for **debouncing** a mechanical button.
- Detect **valid button press-release events**.
- Modularize the FSM logic and hardware abstraction into separate source files.
- Integrate the FSM with the existing non-blocking delay API (`API_delay`).
- Use detected button events to **toggle LED blinking frequency**.

## Project Structure

The project was created as a copy of Practice 3 and extends it with a button debouncer:

```
/Drivers
└── /API
    ├── /Inc
    │   ├── API_delay.h
    │   ├── API_debounce.h
    │   └── API_button.h
    └── /Src
        ├── API_delay.c
        ├── API_debounce.c
        └── API_button.c
```

## Files

### API_debounce.h / API_debounce.c

- Implements a **4-state FSM** (`BUTTON_UP`, `BUTTON_FALLING`, `BUTTON_DOWN`, `BUTTON_RAISING`) for button debouncing.
- Uses `delayRead()` to ensure 40ms of stable input before transitioning states.
- Calls an internal function `on_button_released()` on valid release, which sets a flag.
- Provides a public function `read_key()` to consume the button event flag from `main.c`.

### API_button.h / API_button.c

- Encapsulates the **hardware-specific button logic**, including:
  - GPIO pin and port selection.
  - Whether the button is **active-low or active-high**.
- Provides a single `readButton()` function that returns `true` when the button is pressed, normalized for logic level.

### API_delay.h / API_delay.c

- Reused from Practice 3 without modification.
- Provides non-blocking delay functionality using `HAL_GetTick()`.

## Main Program (`main.c`)

- Initializes the FSM and delay modules.
- Periodically calls `debounceFSM_update()` in the main loop.
- Uses `read_key()` to detect a valid button press-release event and toggles LED blink timing between 500ms and 100ms.
- LED blinking is controlled via the `API_delay` module with non-blocking logic.

## Key Concepts

- **Debounce FSM**: Handles bouncing using state transitions and delay timers instead of polling raw GPIO.
- **Event-based Logic**: The FSM flags events only on valid press-release sequences, avoiding noise and false triggers.
- **Hardware Abstraction**: Button pin logic and polarity are hidden behind `readButton()` for clean separation.
- **Modular Design**: FSM, GPIO logic, and delay functionality are fully modular and reusable across projects.

## Questions for Reflection

- Is the debounce logic portable to other boards or buttons?
- Could this FSM be extended to detect **long presses** or **double clicks**?
- Is the use of constants and macros (e.g., `BUTTON_PRESSED`, debounce time) centralized for easy tuning?

## Requirements

- STM32 HAL Library (for `HAL_GetTick`, GPIO)
- `stdint.h`, `stdbool.h`

## Build Instructions

1. Clone or copy the Practice 3 project.
2. Add the new debounce FSM and button GPIO files into `/API/Inc` and `/API/Src`.
3. Make sure include paths are updated in your STM32CubeIDE project settings.
4. Compile and flash the code to the NUCLEO-F4 board.
5. Press the blue button to toggle the LED blinking speed between 100ms and 500ms.
