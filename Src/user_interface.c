#include <display.h>
#include <event.h>
#include <game.h>
#include <game_io.h>
#include <systick.h>
#include <user_interface.h>

#define TIMEOUT_FACTOR 1000

// Wait for the user to press the green button
void wait_start() {
	if (game_in_new_state()) {
		all_lights_off();
		turn_on(LIGHT_GREEN);
	}

	// In this loop, we ignore green button presses because it's already on and
	// should not be turned off during this function
	for (uint8_t i = BUTTON_GREEN + 1; i < BUTTON_COUNT; ++i) {
			set_light(i, is_pressed(i));
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
		all_lights_off();
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
		all_lights_off();
		start_time = get_ms_ticks();
	}

	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		set_light(i, is_pressed(i));
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
		all_lights_off();
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
			all_lights_off();
			reset_display(&display);
		}

		update_animation(&display);

		if (display.state == DISPLAY_DONE) {
			EVENT event = { EVENT_DISPLAY_DONE, BUTTON_NONE, get_ms_ticks() };
			eq_push(event);
		}
}

void display_score(void) {
	const static LIGHT light_order[] = {LIGHT_RED, LIGHT_BLUE, LIGHT_WHITE, LIGHT_GREEN};

	if (game_in_new_state()) {
		all_lights_off();
		const uint8_t score = game_get_round() - 1;

		for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
			if (score & 1 << i) {
				turn_on(light_order[i]);
			}
		}
	}
}

