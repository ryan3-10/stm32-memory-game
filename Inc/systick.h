#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

void systick_init();
uint32_t get_ms_ticks();

#endif /* SYSTICK_H_ */
