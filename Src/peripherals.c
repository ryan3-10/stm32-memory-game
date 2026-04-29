#include <peripherals.h>

void init_peripherals() {
	// Enable clock for ports C and E, and RNG
	RCC->AHB1ENR |= 1 << 2;
	RCC->AHB1ENR |= 1 << 4;
	RCC->AHB2ENR |= 1 << 6;

	// Set the pins controlling the LEDs to output
	gpio_init_output(GPIOE, 6); // green
	gpio_init_output(GPIOE, 2); // white
	gpio_init_output(GPIOE, 13); // blue
	gpio_init_output(GPIOE, 15); // red

	// Set the pins controlling the buttons to input
	gpio_init_input(GPIOC, 3); // green
	gpio_init_input(GPIOC, 4); // white
	gpio_init_input(GPIOC, 5); // blue
	gpio_init_input(GPIOC, 6); // red

	// Set pull up resistors in pins controlling the buttons
	gpio_set_pullup(GPIOC, 3);
	gpio_set_pullup(GPIOC, 4);
	gpio_set_pullup(GPIOC, 5);
	gpio_set_pullup(GPIOC, 6);

	// PLLON
	RCC->CR |= 1 << 24;

	// PLLN = 12
	RCC->PLLCFGR &= ~(0XFFF << 6);
	RCC->PLLCFGR |= 12 << 6;

	// PLLM = 2
	RCC->PLLCFGR &= ~(0XFFF << 0);
	RCC->PLLCFGR |= 2 << 0;

	// PLLQ = 2
	RCC->PLLCFGR &= ~(0XFFF << 24);
	RCC->PLLCFGR |= 2 << 24;

	// RNGEN
	RNG->CR |= 1 << 2;

	// Wait for RNG to have a value ready and then seed srand with it
	while (!(RNG->SR & 1));
	uint32_t seed = RNG->DR;
	srand(seed);
}

