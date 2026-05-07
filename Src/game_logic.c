#include <display.h>
#include <game.h>
#include <game_io.h>
#include <game_logic.h>
#include <systick.h>

static LIGHT game_over_lights[] = {LIGHT_RED};

DISPLAY game_over_display = {
	.state = DISPLAY_NEW,
	.index = 0,
	.lights = game_over_lights,
	.lights_size = 1,
	.start_delay = 0,
	.flash_count = 16,
	.flash_delay = 50
};

static LIGHT victory_lights[] = {LIGHT_GREEN, LIGHT_WHITE, LIGHT_BLUE, LIGHT_RED};
DISPLAY victory_display = {
	.state = DISPLAY_NEW,
	.index = 0,
	.lights = victory_lights,
	.lights_size = 4,
	.start_delay = 0,
	.flash_count = 16,
	.flash_delay = 50
};

// light_size and flash_count set in function
DISPLAY sequence_display = {
	.state = DISPLAY_NEW,
	.index = 0,
	.start_delay = 300,
	.flash_delay = 300
};

uint8_t wait_to_start_done = 0;
uint8_t display_score_done = 0;

// Wait for the user to press the green button
void wait_to_start() {
	if (!wait_to_start_done) {
		game_reset();
		turn_on(LIGHT_GREEN);
		wait_to_start_done = 1;
	}

	while (get_input() != BUTTON_GREEN);
	turn_off(LIGHT_GREEN);
	wait_to_start_done = 0;
	game_set_state(GAME_SEQUENCE);
}

void display_sequence() {
	// need to set these attributes separately because they will not be the same every time
	// this function is called
	if (sequence_display.state == DISPLAY_NEW) {
		sequence_display.lights = game_get_sequence();
		sequence_display.lights_size = game_get_round();
		sequence_display.flash_count = game_get_round();
	}

	light_animation(&sequence_display);

	if (sequence_display.state == DISPLAY_DONE) {
		reset_display(&sequence_display);
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
	light_animation(&game_over_display);

	if (game_over_display.state == DISPLAY_DONE) {
		reset_display(&game_over_display);
		game_set_state(GAME_DISPLAY_SCORE);
	}
}

void victory_animation() {
	light_animation(&victory_display);

		if (victory_display.state == DISPLAY_DONE) {
			reset_display(&victory_display);
			game_set_state(GAME_DISPLAY_SCORE);
		}
}

void display_score(uint8_t score) {
	static LIGHT light_order[] = {LIGHT_RED, LIGHT_BLUE, LIGHT_WHITE, LIGHT_GREEN};

	if (!display_score_done) {
		for (uint8_t i = 0; i < 4; ++i) {
			if (score & 1 << i) {
				turn_on(light_order[i]);
			}
		}

		display_score_done = 1;
	}

	while (get_input() == BUTTON_NONE);
	all_lights_off();
	display_score_done = 0;
	game_set_state(GAME_WAIT_START);
}

