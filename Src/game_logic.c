#include <display.h>
#include <game.h>
#include <game_io.h>
#include <game_logic.h>
#include <systick.h>

// Wait for the user to press the green button
void wait_to_start() {
	static uint8_t done = 0;

	if (!done) {
		turn_on(LIGHT_GREEN);
	}

	while (get_input() != BUTTON_GREEN);
	turn_off(LIGHT_GREEN);
}

void display_sequence() {
	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.start_delay = 300,
		.flash_delay = 300
	};

	// need to set these attributes separately because they will not be the same every time
	// this function is called
	if (display.state == DISPLAY_NEW) {
		display.lights = game_get_sequence();
		display.lights_size = game_get_round();
		display.flash_count = game_get_round();
	}

	light_animation(&display);

	if (display.state == DISPLAY_DONE) {
		reset_display(&display);
		game_set_state(GAME_USER_ATTEMPT);
	}
}

void user_attempt() {
	uint8_t index = 0;
	BUTTON pressed;
	uint32_t start_time = get_ms_ticks();

	while (game_get_state() == GAME_USER_ATTEMPT) {
		pressed = get_input();

		if ((LIGHT)pressed == game_get_sequence()[index]) {
			if (++index == game_get_round()) {
				game_level_up();
				GAME_STATE new_state = game_get_round() == 16
					? GAME_VICTORY
					: GAME_SEQUENCE;
				game_set_state(new_state);
			}
		} else if (pressed != BUTTON_NONE) {
			game_set_state(GAME_OVER);
		} else if (get_ms_ticks() - start_time > 1000 * game_get_round()) {
			game_set_state(GAME_OVER);
		}
	}
}

void game_over_animation() {
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
		reset_display(&display);
		game_set_state(GAME_DISPLAY_SCORE);
	}
}

void victory_animation() {
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
			game_set_state(GAME_DISPLAY_SCORE);
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

