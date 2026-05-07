#include <display.h>
#include <event.h>
#include <game.h>
#include <game_io.h>
#include <game_logic.h>
#include <systick.h>

#define TIMEOUT_FACTOR 1000

// Wait for the user to press the green button
void wait_start() {
	if (game_in_new_state()) {
		turn_on(LIGHT_GREEN);
	}
}

void display_sequence() {
	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.start_delay = 300,
		.flash_delay = 300
	};

	// Need to set these attributes separately because they will not be the same every time
	// this function is called
	if (game_in_new_state()) {
		reset_display(&display);
		display.lights = game_get_sequence();
		display.lights_size = game_get_round();
		display.flash_count = game_get_round();
	}

	update_animation(&display);

	if (display.state == DISPLAY_DONE) {
		EVENT event = { EVENT_DISPLAY_DONE, BUTTON_NONE, get_ms_ticks() };
		eq_push(event);
	}
}

void user_attempt() {
	static uint32_t start_time;

	if (game_in_new_state()) {
		start_time = get_ms_ticks();
	}

	if (elapsed(start_time) >= game_get_round() * TIMEOUT_FACTOR) {
		EVENT event = { EVENT_TIMEOUT, BUTTON_NONE, get_ms_ticks() };
		eq_push(event);
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

	if (game_in_new_state()) {
		reset_display(&display);
	}

	update_animation(&display);

	if (display.state == DISPLAY_DONE) {
		EVENT event = { EVENT_DISPLAY_DONE, BUTTON_NONE, get_ms_ticks() };
		eq_push(event);
	}
}

void victory_animation() {
	static LIGHT lights[] = {LIGHT_GREEN, LIGHT_WHITE, LIGHT_BLUE, LIGHT_RED};

	static DISPLAY display = {
		.state = DISPLAY_NEW,
		.index = 0,
		.lights = lights,
		.lights_size = BUTTON_COUNT,
		.start_delay = 0,
		.flash_count = 16,
		.flash_delay = 50
	};

		if (game_in_new_state()) {
			reset_display(&display);
		}

		update_animation(&display);

		if (display.state == DISPLAY_DONE) {
			EVENT event = { EVENT_DISPLAY_DONE, BUTTON_NONE, get_ms_ticks() };
			eq_push(event);
		}
}

void display_score(uint8_t score) {
	const static LIGHT light_order[] = {LIGHT_RED, LIGHT_BLUE, LIGHT_WHITE, LIGHT_GREEN};

	if (game_in_new_state()) {
		for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
			if (score & 1 << i) {
				turn_on(light_order[i]);
			}
		}
	}
}

