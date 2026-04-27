#include <components.h>
#include <game.h>
#include <gpio.h>
#include <stdlib.h>

int8_t sequence[50];

GAME get_new_game() {
	GAME game = {
		.state = STATE_GAME_INIT,
		.round = 0,
	};
	return game;
}

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

void wait_to_start() {
	// Wait for the user to press the blue button
	turn_on(LIGHT_BLUE);
	while (get_input() != BUTTON_BLUE);
	turn_off(LIGHT_BLUE);
}

void display_sequence(GAME* game) {
	game->sequence[game->round++] = rand() % 4;
	delay(600000);

	for (uint8_t i = 0; i < game->round; ++i) {
		LIGHT light = game->sequence[i];
		turn_on(light);

		delay(600000);
		turn_off(light);
		delay(300000);
	}
}

void user_attempt(GAME* game) {
	for (uint8_t i = 0; i < game->round && game->state != STATE_GAME_OVER; ++i) {
		BUTTON expected = game->sequence[i];
		BUTTON pressed = get_input();

		turn_on((LIGHT)pressed);
		while (is_pressed(pressed));
		turn_off((LIGHT)pressed);

		if (expected != pressed) {
			game->state = STATE_GAME_OVER;
		}
	}

	if (game->state != STATE_GAME_OVER) {
		game->state = STATE_SEQUENCE;
	}
}

void game_over_animation() {
	const uint8_t flash_count = 15;
	for (int8_t i = 0; i < flash_count; ++i) {
		turn_on(LIGHT_RED);
		delay(100000);
		turn_off(LIGHT_RED);
		delay(100000);
	}
}

void display_score(uint8_t score) {
	if (score & (1 << 0)) {
		turn_on(LIGHT_YELLOW);
	}
	if (score & 1 << 1) {
		turn_on(LIGHT_BLUE);
	}
	if (score & 1 << 2) {
		turn_on(LIGHT_WHITE);
	}
	if (score & 1 << 3) {
		turn_on(LIGHT_RED);
	}

	get_input();
	all_lights_off();
}

