#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

void systick_init();
uint32_t get_ms_ticks();
uint32_t elapsed(uint32_t timestamp);

#endif /* SYSTICK_H_ */
