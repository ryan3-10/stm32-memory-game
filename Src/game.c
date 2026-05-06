#include <display.h>
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
	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.start_delay = 300,
		.flash_delay = 300
	};

	// need to set these attributes separately because they will not be the same every time
	// this function is called
	if (display.state == DISPLAY_NEW) {
		display.lights = game->sequence;
		display.lights_size = game->round;
		display.flash_count = game->round;
		game->sequence[game->round - 1] = rand() % 4;
	}

	light_animation(&display);

	if (display.state == DISPLAY_DONE) {
		reset_display(&display);
		game->state = GAME_USER_ATTEMPT;
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
}

void game_over_animation(GAME* game) {
	static LIGHT lights[] = {LIGHT_RED};
	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.lights = lights,
		.lights_size = 1,
		.start_delay = 0,
		.flash_count = 16,
		.flash_delay = 50
	};

	light_animation(&display);

	if (display.state == DISPLAY_DONE) {
		game->state = GAME_DISPLAY_SCORE;
	}
}

void victory_animation(GAME* game) {
	static LIGHT lights[] = {LIGHT_GREEN, LIGHT_WHITE, LIGHT_BLUE, LIGHT_RED};
	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.lights = lights,
		.lights_size = 4,
		.start_delay = 0,
		.flash_count = 16,
		.flash_delay = 50
	};

	light_animation(&display);

		if (display.state == DISPLAY_DONE) {
			reset_display(&display);
			game->state = GAME_DISPLAY_SCORE;
		}
}

void display_score(uint8_t score) {
	LIGHT light_order[] = {LIGHT_RED, LIGHT_BLUE, LIGHT_WHITE, LIGHT_GREEN};

	for (uint8_t i = 0; i < 4; ++i) {
		if (score & 1 << i) {
			turn_on(light_order[i]);
		}
	}

	while (get_input() == BUTTON_NONE);
	all_lights_off();
}

