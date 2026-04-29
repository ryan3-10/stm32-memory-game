#include <components.h>
#include <game.h>
#include <gpio.h>
#include <stdlib.h>

int8_t sequence[50];

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
	game->sequence[game->round++] = rand() % 4;

	delay(400);

	for (uint8_t i = 0; i < game->round; ++i) {
		LIGHT light = game->sequence[i];
		turn_on(light);

		delay(300);
		turn_off(light);
		delay(300);
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
		delay(50);
		turn_off(LIGHT_RED);
		delay(50);
	}
}

void display_score(uint8_t score) {
	if (score & (1 << 0)) {
		turn_on(LIGHT_RED);
	}
	if (score & 1 << 1) {
		turn_on(LIGHT_BLUE);
	}
	if (score & 1 << 2) {
		turn_on(LIGHT_WHITE);
	}
	if (score & 1 << 3) {
		turn_on(LIGHT_GREEN);
	}

	get_input();
	all_lights_off();
}

