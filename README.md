# STM32 Memory Game

A high-performance implementation of Simon Says on the **STM32F407** microcontroller, demonstrating embedded systems design patterns including interrupt-driven input handling, finite state machines, and bare-metal peripheral configuration.

## Overview

This project implements a classic memory/pattern matching game on an ARM Cortex-M4 microcontroller with minimal overhead. The game presents increasingly complex sequences of colored lights, requiring the player to reproduce each sequence by pressing corresponding buttons. Success advances to the next round; any mistake ends the game.

**Key Distinction**: Rather than a naive polling-based approach, this implementation uses **external interrupts (EXTI)** for button inputs combined with a non-blocking state machine, allowing the processor to efficiently handle real-time constraints while maintaining responsive gameplay.

## Features

- **🎮 Full Game Mechanics**: Progressive difficulty with up to 15 sequence depth
- **⚡ Interrupt-Driven Architecture**: Efficient CPU utilization via EXTI handlers (no busy-waiting on button inputs)
- **🛡️ Debounce Handling**: Hardware-software debouncing on button press/release cycles
- **🎯 State Machine Design**: Clean game flow with explicit state transitions (WAIT_START → SEQUENCE → USER_ATTEMPT → GAME_OVER)
- **💡 Real-Time Output**: Visual feedback with 4-color LED display
- **📊 Score Display**: Binary encoding of final score across LED states

## Hardware Configuration

| Component | Details |
|-----------|---------|
| **MCU** | STM32F407G-DISC1 (Cortex-M4, 168 MHz, 1MB Flash) |
| **GPIO** | 4 Output pins (GPIOE) for LEDs, 4 Input pins (GPIOC) for buttons |
| **Interrupts** | EXTI9_5_IRQn handler for all button events (EXTI5, EXTI6, EXTI7, EXTI9) |
| **RNG** | Hardware random number generator for sequence generation |
| **SysTick** | Timer for game delays and debounce timing |

**Pin Mapping:**
- **Green Light**: PE6 | **Green Button**: PC5
- **White Light**: PE2 | **White Button**: PC9
- **Blue Light**: PED | **Blue Button**: PC7
- **Red Light**: PEF | **Red Button**: PC6

## Architecture

### State Machine

```
┌──────────────────┐
│  WAIT_START      │ ◄── Game ready, awaiting player signal
└────────┬─────────┘
         │ [Green button pressed]
         ▼
┌──────────────────┐
│  SEQUENCE        │ ◄── Display light sequence with delays
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│  USER_ATTEMPT    │ ◄── Process player button inputs via EXTI
└────────┬─────────┘
         │ [Player error OR all correct]
         ▼
┌──────────────────┐
│  GAME_OVER       │ ◄── Flash animation, encode score
└──────────────────┘
```

### Interrupt-Driven Input Handling

Instead of blocking on `get_input()`, the game uses a non-blocking approach:

1. **Button Press**: EXTI handler detects falling edge (active-low buttons)
2. **Debounce**: 20ms software delay ensures stable pin state
3. **State Update**: Global `button_pressed` variable is updated
4. **get_input()**: Checks if the value of the `pressed` variable has been updated by the IRQ
5. **Button Release**: Verified before advancing sequence matching

This design maintains responsiveness even under tight timing constraints.

### Key Components

| File | Responsibility |
|------|-----------------|
| `game.c` | Game logic, sequence generation, compare user input with expected sequence |
| `game_io.c` | LED control and non-blocking button input |
| `board.c` | GPIO initialization, EXTI configuration |
| `gpio.c` | Low-level GPIO register manipulation |
| `system.c` | RCC clocks, RNG initialization |
| `systick.c` | Timer for delays and debouncing |
| `mcu.h` | Raw memory locations of peripheral registers | 

## Technical Highlights

### 1. **Efficient Interrupt Handling**
- Minimal ISR overhead: store button state, return immediately
- SysTick-based debouncing prevents contact bounce errors
- Proper EXTI/SYSCFG register configuration for falling edge detection

### 2. **Bare-Metal Peripheral Configuration**
- Direct register manipulation (no HAL dependencies) for EXTI, GPIO, RCC, SYSCFG
- Manual clock gating and pin mode configuration
- Hardware RNG integration for unbiased sequence generation

### 3. **Clean Separation of Concerns**
- Game logic isolated from I/O handling
- Consistent naming conventions and parameter passing
- Modular design allows easy hardware adaptation

### 4. **Memory-Efficient Sequence Storage**
- Fixed-size array (15 elements) eliminates dynamic allocation
- Tight loops with minimal stack usage suitable for embedded constraints

## Building & Running

### Prerequisites
- STM32CubeIDE or compatible ARM GCC toolchain
- ST-Link debugger for flashing
- STM32F407 development board with LED/button hardware

### Build
```bash
make -C Debug/
```

### Flash to Device
```bash
# Using ST-Link
st-flash write Debug/stm32-memory-game.bin 0x08000000

# Or via STM32CubeIDE
# Right-click project → Run As → STM32 C/C++ Application
```

## How to Play

1. **Start**: Press the green button when game shows green LED
2. **Watch**: Observe the sequence of flashing lights
3. **Repeat**: Press buttons in the same sequence
4. **Progress**: Each successful round adds another light to the sequence
5. **Game Over**: One mistake ends the game
6. **Score Display**: Final score encoded in binary LED pattern (max score of 15)

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
