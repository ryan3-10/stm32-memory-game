# STM32 Memory Game

A Simon Says implementation on the **STM32F407** microcontroller, demonstrating interrupt-driven input handling, non-blocking event-driven architecture, and bare-metal embedded systems design.

## Demo Video
[Watch the Demo](https://youtube.com/shorts/naQB-Cir1FA)

## Overview

This project implements a classic memory/pattern matching game on an ARM Cortex-M4 microcontroller. The game displays increasingly complex sequences of colored lights (up to 15 rounds); the player must reproduce each sequence by pressing the corresponding buttons.

**Key Innovation**: Non-blocking event-driven architecture with EXTI interrupt handlers, circular event queue, and state-specific handlers—no polling or blocking calls.

## Features

- **Interrupt-Driven**: EXTI handlers for button input with hardware debouncing
- **Non-Blocking Event Loop**: Dequeue events and dispatch to state handlers
- **State Machine**: Clean transitions (WAIT_START → SEQUENCE → USER_ATTEMPT → VICTORY/GAME_OVER)
- **4-Color LED Display**: Real-time visual feedback
- **Animations**: Victory sequence and defeat flash

## Hardware

| Component | Details |
|-----------|---------|
| **MCU** | STM32F407G-DISC1 (Cortex-M4, 168 MHz) |
| **GPIO** | 4 LEDs (GPIOE), 4 buttons (GPIOC) |
| **Interrupts** | EXTI9_5_IRQn for button events |
| **RNG** | Hardware random number generator |
| **SysTick** | Timer for delays and debouncing |

**Pins (Light/Button)**: Green=PE6/PC5, White=PE2/PC9, Blue=PE13/PC7, Red=PE15/PC6

## Architecture

### Non-Blocking Event-Driven Design

The program uses a circular event queue (16 events) to decouple interrupt handlers from game logic:

1. **EXTI Button IRQ**: Generates `EVENT_BUTTON` on button press
2. **SysTick Animation Tick**: Animation completion generates `EVENT_DISPLAY_DONE`
3. **Timeout Timer**: `EVENT_TIMEOUT` if user doesn't respond in time
4. **Main Loop**: Dequeues events and dispatches to appropriate handler

### Game State Machine

States flow: **WAIT_START** → **SEQUENCE** (display) → **USER_ATTEMPT** → **VICTORY** or **GAME_OVER** → **DISPLAY_SCORE** → **WAIT_START**

Each state has a dedicated event handler that processes only relevant events:
- `wait_start_handler()`: Waits for green button press
- `sequence_handler()`: Ignores input during display; advances on `EVENT_DISPLAY_DONE`
- `user_attempt_handler()`: Matches button presses to sequence; handles timeout
- `victory_handler()`: Victory animation completion
- `game_over_handler()`: Defeat animation completion
- `display_score_handler()`: Shows score, waits to restart

### User Interface Functions

Non-blocking UI functions update incrementally and generate events:
- `wait_start()`: Display green light, mirror button states
- `display_sequence()`: Flash game sequence → `EVENT_DISPLAY_DONE`
- `user_attempt()`: Show pressed buttons, track timeout → `EVENT_TIMEOUT`
- `game_over_animation()`: Flash red light 15 times
- `victory_animation()`: Cycle all 4 lights 10 times
- `display_score()`: Binary-encode final score on LEDs

Each maintains internal state without blocking the main loop.
## Key Components

| File | Responsibility |
|------|-----------------|
| `main.c` | Event loop: dequeue and dispatch to state handlers |
| `event_handlers.c` | State-specific event handlers |
| `user_interface.c` | Non-blocking UI state machines |
| `game.c` | Game logic and sequence management |
| `game_io.c` | LED control and button input |
| `board.c` | GPIO and EXTI initialization |
| `systick.c` | Timer for delays and timeouts |

## Technical Highlights

- **Interrupt-Driven**: EXTI handlers with 20ms debouncing
- **Non-Blocking**: All I/O operations generate events; main loop never blocks
- **State-Based**: Separate handler for each game state processes only relevant events
- **Bare-Metal**: Direct register manipulation (no HAL dependencies)

## Building & Running

### Prerequisites
- STM32CubeIDE or ARM GCC toolchain
- ST-Link debugger
- STM32F407 development board

### Build & Flash
```bash
make -C Debug/
st-flash write Debug/stm32-memory-game.bin 0x08000000
```

### Testing

Run the unit tests using the provided script (Unix terminal, WSL, or Git Bash on Windows):

```bash
./run_tests
```

This script builds and executes all tests using Google Test (GTest)

Tests cover:
- **Game logic**: State transitions, sequence generation, round progression
- **Event handlers**: Button input handling, timeout behavior, state-specific event processing
- **Event queue**: Circular buffer operations, push/pop mechanics

## How to Play

1. **Start**: Press the green button when game shows green LED
2. **Watch**: Observe the sequence of flashing lights
3. **Repeat**: Press buttons in the same sequence
4. **Progress**: Each successful round adds another light to the sequence
5. **Victory**: Complete all 15 rounds successfully to trigger the victory animation (cycling through all 4 lights)
6. **Game Over**: One mistake triggers the defeat animation (red LED flash) and displays your final score
7. **Score Display**: Final score encoded in binary LED pattern (1-15 for rounds completed)

## Skills Demonstrated

- **Embedded Systems**: Bare-metal ARM development, interrupt handling, real-time constraints
- **Digital Electronics**: GPIO configuration, EXTI routing, clock distribution
- **Software Design**: State machines, non-blocking I/O, debouncing patterns
- **Low-Level Programming**: Register manipulation, bit-field operations, memory efficiency
- **Hardware Debugging**: EXTI configuration validation, timing analysis

---

**Author**: Ryan  
**MCU**: STM32F407G-DISC1  
**Date**: 2026
