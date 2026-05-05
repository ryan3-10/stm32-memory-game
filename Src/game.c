#include <game.h>
#include <game_io.h>
#include <systick.h>
#include <stdlib.h>

GAME get_new_game() {
	GAME game = {
		.state = GAME_WAIT_START,
		.round = 1,
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

	game->sequence[game->round - 1] = rand() % 4;

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
	uint8_t index = 0;
	BUTTON pressed;
	uint32_t start_time = get_ms_ticks();

	while (game->state == GAME_USER_ATTEMPT) {
		pressed = get_input();

		if ((LIGHT)pressed == game->sequence[index]) {
			if (++index == game->round) {
				game->state = ++game->round == 16
					? GAME_VICTORY
					: GAME_SEQUENCE;
			}
		} else if (pressed != BUTTON_NONE) {
			game->state = GAME_OVER;
		} else if (get_ms_ticks() - start_time > 1000 * game->round) {
			game->state = GAME_OVER;
		}
	}

	for (uint8_t i = 0; i < game->round && game->state != GAME_OVER; ++i) {
		BUTTON expected = game->sequence[i];
		BUTTON pressed = get_input();

		if (expected != pressed) {
			game->state = GAME_OVER;
		}
	}

	if (game->state != GAME_OVER) {
		game->state = ++game->round == 16 ? GAME_VICTORY : GAME_SEQUENCE;
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

void victory_animation() {
	const uint8_t flash_delay = 80;

	for (size_t i = 0; i < 10; ++i) {
		turn_on(LIGHT_GREEN);
		delay(flash_delay);
		turn_off(LIGHT_GREEN);

		turn_on(LIGHT_WHITE);
		delay(flash_delay);
		turn_off(LIGHT_WHITE);

		turn_on(LIGHT_BLUE);
		delay(flash_delay);
		turn_off(LIGHT_BLUE);

		turn_on(LIGHT_RED);
		delay(flash_delay);
		turn_off(LIGHT_RED);
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

