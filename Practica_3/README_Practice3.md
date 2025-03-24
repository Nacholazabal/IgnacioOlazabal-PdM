# Programming Practice 3 – Non-blocking Delay API

## Overview

This practice is based on Programming Practice 2 and focuses on **modularizing** the implementation of **non-blocking delays** in embedded C programming. The goal is to encapsulate the delay functionalities into a reusable and maintainable API, suitable for STM32 projects (NUCLEO-F4xx board).

## Objectives

- Refactor the delay code from Practice 2 into a **modular API**.
- Implement a **non-blocking LED blinking sequence** with adjustable timing.
- Add a utility function to check if a delay is currently running.

## Project Structure

A new project was created as a **copy of Practice 2**, with the following additions:

```
/Drivers
└── /API
    ├── /Inc
    │   └── API_delay.h
    └── /Src
        └── API_delay.c
```

## Files

### API_delay.h

Contains:

- `typedef` declarations:
  - `tick_t`: an alias for `uint32_t`
  - `bool_t`: an alias for `bool`
  - `delay_t`: struct to manage delays (`startTime`, `duration`, `running`)
- Function prototypes:
  ```c
  void delayInit(delay_t * delay, tick_t duration);
  bool_t delayRead(delay_t * delay);
  void delayWrite(delay_t * delay, tick_t duration);
  bool_t delayIsRunning(delay_t * delay);
  ```

### API_delay.c

Contains the implementation of the delay functions using `HAL_GetTick()` for millisecond timekeeping. All logic is non-blocking.

## Main Program (main.c)

- Blinks the user LED on the NUCLEO board using a sequence defined by:
  ```c
  const uint32_t TIEMPOS[] = {500, 100, 100, 1000};
  ```
- Uses a single `delay_t` variable and updates its duration dynamically using `delayWrite()`.
- Ensures `delayWrite()` is only called when the delay is not running (`!delayIsRunning()`).

## Key Concepts

- **Modular Design**: All delay logic is moved out of `main.c` and into a dedicated API, making the code easier to maintain and reuse.
- **Non-blocking Execution**: Uses time comparisons instead of `HAL_Delay()` to keep the application responsive.
- **Delay State Inspection**: `delayIsRunning()` provides transparency into delay status for safer timing updates.

## To Consider

- Are the timing constants centralized or scattered as “magic numbers”?
- Are input parameters validated adequately?
- Could this API scale if more functionality was added?
- Is the current design intuitive and reusable?

## Requirements

- STM32 HAL Library (for `HAL_GetTick`)
- `stdint.h` and `stdbool.h`

## Build Instructions

1. Clone the Practice 3 project (copied from Practice 2).
2. Make sure the `/API/Inc` and `/API/Src` folders are added to the include path in your IDE (e.g., STM32CubeIDE).
3. Compile and flash to the NUCLEO-F4xx board.
