#include <stdint.h>
#include <mcu.h>
#include <systick.h>

// Systick flags
#define CTRL_ENABLE    (1 << 0)
#define CTRL_CLKSOURCE (1 << 2)
#define CTRL_COUNTFLAG (1 << 16)
#define SYSTICK_LOAD_VALUE 16000  // 16 MHz clock → 1 ms

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

uint32_t elapsed(uint32_t timestamp) {
	return ms_ticks - timestamp;
}


