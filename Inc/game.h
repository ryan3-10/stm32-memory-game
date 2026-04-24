#ifndef GAME_H_
#define GAME_H_

#include <gpio.h>

typedef enum {
	STATE_GAME_INIT,
	STATE_WAIT_START,
	STATE_SEQUENCE,
	STATE_WAIT_INPUT,
	STATE_GAME_OVER
} STATE;

void init_game() {
	// Enable clock for ports C and E
	RCC->AHB1ENR |= 1 << 2;
	RCC->AHB1ENR |= 1 << 4;

	// Set the pins controlling the LEDs to output
	gpio_init_output(GPIOE, 6); // red
	gpio_init_output(GPIOE, 2); // white
	gpio_init_output(GPIOE, 13); // blue
	gpio_init_output(GPIOE, 15); //yellow

	// Set the pins controlling the buttons to input
	gpio_init_input(GPIOC, 3); // red
	gpio_init_input(GPIOC, 4); // white
	gpio_init_input(GPIOC, 5); // blue
	gpio_init_input(GPIOC, 6); // yellow

	// Set pull up resistors in pins controlling the buttons
	gpio_set_pullup(GPIOC, 3);
	gpio_set_pullup(GPIOC, 4);
	gpio_set_pullup(GPIOC, 5);
	gpio_set_pullup(GPIOC, 6);
}

#endif /* GAME_H_ */
