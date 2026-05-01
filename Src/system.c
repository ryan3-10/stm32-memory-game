#include <mcu.h>
#include <system.h>
#include <stdlib.h>

// Clock enable bits
#define PORTC_CLOCK_POS	(2u)
#define PORTE_CLOCK_POS	(4u)
#define RNG_CLOCK_POS	(6u)

// PLL bits
#define PLLN_POS 	(6u)
#define PLLM_POS 	(0u)
#define PLLQ_POS 	(24u)
#define PLLON_POS	(24u)

// RNG control register bits
#define RNGEN_POS	(2u)

void system_init() {
	// Enable clock for ports C and E, and RNG
	RCC->AHB1ENR |= 1 << PORTC_CLOCK_POS;
	RCC->AHB1ENR |= 1 << PORTE_CLOCK_POS;
	RCC->AHB2ENR |= 1 << RNG_CLOCK_POS;

	// Set PLLN to 12
	RCC->PLLCFGR &= ~(0X1FF << PLLN_POS);
	RCC->PLLCFGR |= 12 << PLLN_POS;

	// Set PLLM to 2
	RCC->PLLCFGR &= ~(0X3F << PLLM_POS);
	RCC->PLLCFGR |= 2 << PLLM_POS;

	// Set PLLQ to 2
	RCC->PLLCFGR &= ~(0XF << PLLQ_POS);
	RCC->PLLCFGR |= 2 << PLLQ_POS;

	// Set PLLON bit
	RCC->CR |= 1 << PLLON_POS;

	// Set RNGEN bit
	RNG->CR |= 1 << RNGEN_POS;

	// Wait for RNG to have a value ready and then seed srand with it
	while (!(RNG->SR & 1));
	uint32_t seed = RNG->DR;
	srand(seed);
}


