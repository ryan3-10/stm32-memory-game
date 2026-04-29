#include <peripherals.h>

void init_peripherals() {
	// Enable clock for ports C and E, and RNG
	RCC->AHB1ENR |= 1 << PORTC_CLOCK_POS;
	RCC->AHB1ENR |= 1 << PORTE_CLOCK_POS;
	RCC->AHB2ENR |= 1 << RNG_CLOCK_POS;

	// Set the pins controlling the LEDs to output
	gpio_init_output(LIGHT_PORT, GREEN_LIGHT_PIN);
	gpio_init_output(LIGHT_PORT, WHITE_LIGHT_PIN);
	gpio_init_output(LIGHT_PORT, BLUE_LIGHT_PIN);
	gpio_init_output(LIGHT_PORT, RED_LIGHT_PIN);

	// Set the pins controlling the buttons to input
	gpio_init_input(BUTTON_PORT, GREEN_BUTTON_PIN);
	gpio_init_input(BUTTON_PORT, WHITE_BUTTON_PIN);
	gpio_init_input(BUTTON_PORT, BLUE_BUTTON_PIN);
	gpio_init_input(BUTTON_PORT, RED_BUTTON_PIN);

	// Set pull up resistors in pins controlling the buttons
	gpio_set_pullup(BUTTON_PORT, GREEN_BUTTON_PIN);
	gpio_set_pullup(BUTTON_PORT, WHITE_BUTTON_PIN);
	gpio_set_pullup(BUTTON_PORT, BLUE_BUTTON_PIN);
	gpio_set_pullup(BUTTON_PORT, RED_BUTTON_PIN);

	// PLLN = 12
	RCC->PLLCFGR &= ~(0X1FF << PLLN_POS);
	RCC->PLLCFGR |= 12 << PLLN_POS;

	// PLLM = 2
	RCC->PLLCFGR &= ~(0X3F << PLLM_POS);
	RCC->PLLCFGR |= 2 << PLLM_POS;

	// PLLQ = 2
	RCC->PLLCFGR &= ~(0XF << PLLQ_POS);
	RCC->PLLCFGR |= 2 << PLLQ_POS;

	// PLLON
	RCC->CR |= 1 << PLLON_POS;

	// RNGEN
	RNG->CR |= 1 << RNGEN_POS;

	// Wait for RNG to have a value ready and then seed srand with it
	while (!(RNG->SR & 1));
	uint32_t seed = RNG->DR;
	srand(seed);
}

