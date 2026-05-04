#include <board.h>
#include <gpio.h>

#define IRQ5_9_POS 23

void board_init() {
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

	exti_init();
}

void exti_init() {
	const uint8_t extis_per_register 	= 4;
	const uint8_t bits_per_exti			= 4;

	const uint8_t green_cr	= GREEN_BUTTON_PIN / extis_per_register;
	const uint8_t red_cr 	= RED_BUTTON_PIN / extis_per_register;
	const uint8_t blue_cr 	= BLUE_BUTTON_PIN / extis_per_register;
	const uint8_t white_cr 	= WHITE_BUTTON_PIN / extis_per_register;

	const uint8_t green_shift	= (GREEN_BUTTON_PIN % extis_per_register) * bits_per_exti;
	const uint8_t red_shift 	= (RED_BUTTON_PIN % extis_per_register) * bits_per_exti;
	const uint8_t blue_shift	= (BLUE_BUTTON_PIN % extis_per_register) * bits_per_exti;
	const uint8_t white_shift	= (WHITE_BUTTON_PIN % extis_per_register) * bits_per_exti;

	// Connect EXTI5 to green button pin
	SYSCFG->EXTICR[green_cr] &= ~(0xF << green_shift);
	SYSCFG->EXTICR[green_cr] |= 0x2 << green_shift;

	// Connect EXTI6 to red button pin
	SYSCFG->EXTICR[red_cr] &= ~(0xF << red_shift);
	SYSCFG->EXTICR[red_cr] |= 0x2 << red_shift;

	// Connect EXTI7 to blue button pin
	SYSCFG->EXTICR[blue_cr] &= ~(0xF << blue_shift);
	SYSCFG->EXTICR[blue_cr] |= 0x2 << blue_shift;

	// Connect EXTI9 to white button pin
	SYSCFG->EXTICR[white_cr] &= ~(0xF << white_shift);
	SYSCFG->EXTICR[white_cr] |= 0x2 << white_shift;

	// Unmask IRQ for each EXTI associated with a button's pin
	EXTI->IMR |= 1 << GREEN_BUTTON_PIN;
	EXTI->IMR |= 1 << WHITE_BUTTON_PIN;
	EXTI->IMR |= 1 << BLUE_BUTTON_PIN;
	EXTI->IMR |= 1 << RED_BUTTON_PIN;

	// Set falling trigger selection for for each EXTI associated with a button's pin
	EXTI->FTSR |= 1 << GREEN_BUTTON_PIN;
	EXTI->FTSR |= 1 << WHITE_BUTTON_PIN;
	EXTI->FTSR |= 1 << BLUE_BUTTON_PIN;
	EXTI->FTSR |= 1 << RED_BUTTON_PIN;

	// Enable the IRQ for EXTI5 - EXTI9
	NVIC->ISER[0] |= 1 << IRQ5_9_POS;
}
