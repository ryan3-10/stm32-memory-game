#include <game.h>
#include <game_io.h>
#include <systick.h>
#include <stdlib.h>

GAME get_new_game() {
	GAME game = {
		.state = STATE_WAIT_START,
		.round = 0,
	};
	return game;
}

void wait_to_start() {
	// Wait for the user to press the blue button
	turn_on(LIGHT_GREEN);
	while (get_input() != BUTTON_GREEN);
	turn_off(LIGHT_GREEN);
}

void display_sequence(GAME* game) {
	const uint32_t initial_delay = 400;
	const uint32_t mid_delay = 300;

	game->sequence[game->round++] = rand() % 4;

	delay(initial_delay);

	for (uint8_t i = 0; i < game->round; ++i) {
		LIGHT light = game->sequence[i];
		turn_on(light);

		delay(mid_delay);
		turn_off(light);
		delay(mid_delay);
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
	const uint8_t flash_delay = 50;

	for (int8_t i = 0; i < flash_count; ++i) {
		turn_on(LIGHT_RED);
		delay(flash_delay);
		turn_off(LIGHT_RED);
		delay(flash_delay);
	}
}

void display_score(uint8_t score) {
	LIGHT light_order[] = {LIGHT_RED, LIGHT_BLUE, LIGHT_WHITE, LIGHT_GREEN};

	for (uint8_t i = 0; i < 4; ++i) {
		if (score & 1 << i) {
			turn_on(light_order[i]);
		}
	}

	get_input();
	all_lights_off();
}

// Interrupt handler
void EXTI9_5_IRQHandler() {
	EXTI->PR = 1 << 5;
}

