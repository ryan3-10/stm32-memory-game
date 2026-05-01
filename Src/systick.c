#include <stdint.h>
#include <mcu.h>
#include <systick.h>

// Systick flags
#define CTRL_ENABLE    (1 << 0)
#define CTRL_CLKSOURCE (1 << 2)
#define CTRL_COUNTFLAG (1 << 16)

void delay(uint32_t ms) {
    // 16000 ticks = 1 ms at 16 MHz
    SYSTICK->LOAD = 16000 - 1;

    // Clear current value register
    SYSTICK->VAL = 0;

    // Enable SysTick, use processor clock
    SYSTICK->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE;

    for (uint32_t i = 0; i < ms; i++) {
        // Wait until COUNTFLAG is set
        while (!(SYSTICK->CTRL & CTRL_COUNTFLAG));
    }

    // Disable SysTick
    SYSTICK->CTRL = 0;
}
