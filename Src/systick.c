#include <stdint.h>
#include <mcu.h>
#include <systick.h>

// Systick flags
#define CTRL_ENABLE    (1 << 0)
#define CTRL_CLKSOURCE (1 << 2)
#define CTRL_COUNTFLAG (1 << 16)
#define SYSTICK_LOAD_VALUE 16000  // 16 MHz clock → 1 ms

void delay(uint32_t ms) {
    // 16000 ticks = 1 ms at 16 MHz
    SYSTICK->LOAD = SYSTICK_LOAD_VALUE - 1;

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

void systick_init()
{
	SYSTICK->LOAD = SYSTICK_LOAD_VALUE - 1;  // reload value
	SYSTICK->VAL  = 0;                        // reset current value
	SYSTICK->CTRL =
        (1 << 2) |  // use CPU clock
        (1 << 1) |  // enable interrupt
        (1 << 0);   // enable SysTick
}

volatile uint32_t ms_ticks = 0;

void SysTick_Handler() {
    ++ms_ticks;
}

uint32_t get_ms_ticks() {
	return ms_ticks;
}


