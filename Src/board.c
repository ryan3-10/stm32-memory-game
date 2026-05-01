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

