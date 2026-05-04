#include <board.h>
#include <gpio.h>

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
}

void interrupt_init() {
	const uint8_t extis_per_register = 4;
	const uint8_t green_cr = GREEN_BUTTON_PIN / extis_per_register;
	const uint8_t white_cr = WHITE_BUTTON_PIN / extis_per_register;
	const uint8_t blue_cr = BLUE_BUTTON_PIN / extis_per_register;
	const uint8_t red_cr = RED_BUTTON_PIN / extis_per_register;

	// Connect EXTI5 to green button pin
	SYSCFG->EXTICR[green_cr] &= ~(0xF << 4);
	SYSCFG->EXTICR[green_cr] |= 0x2 << 4;

	// Connect EXTI6 to PC6
	SYSCFG->EXTICR[red_cr] &= ~(0xF << 8);
	SYSCFG->EXTICR[red_cr] |= 0x2 << 8;

	// Connect EXTI7 to PC7
	SYSCFG->EXTICR[blue_cr] &= ~(0xF << 12);
	SYSCFG->EXTICR[blue_cr] |= 0x2 << 12;

	// Connect EXTI9 to PC9
	SYSCFG->EXTICR[white_cr] &= ~(0xF << 4);
	SYSCFG->EXTICR[white_cr] |= 0x2 << 4;

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
	NVIC->ISER[0] |= 1 << 23;
}
