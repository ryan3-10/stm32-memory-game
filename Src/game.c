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
	static uint32_t last_call_time = 0;

	if (get_ms_ticks() - last_call_time > 1) {
		game->sequence[game->round - 1] = rand() % 4;
	}

	last_call_time = get_ms_ticks();

	const uint32_t wait_time = 300;
	light_animation(game, game->sequence, game->round, game->round, wait_time, GAME_USER_ATTEMPT);
}

void user_attempt(GAME* game) {
	uint8_t index = 0;
	BUTTON pressed;
	uint32_t start_time = get_ms_ticks();

	while (game->state == GAME_USER_ATTEMPT) {
		pressed = get_input();

		if ((LIGHT)pressed == game->sequence[index]) {
			if (++index == game->round) {
				game->state = ++(game->round) == 16
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

void light_animation(
	GAME* game,
	LIGHT* lights,
	uint8_t lights_size,
	uint8_t flash_count,
	uint32_t flash_delay,
	GAME_STATE new_game_state
) {
	static uint32_t last_transition_time;
	static uint32_t last_call_time;
	static uint8_t index;
	static ANIMATION_STATE state = ANIMATION_START;

	// If it's been more than 1 ms since the last call to this function, start a fresh
	// animation
	if (get_ms_ticks() - last_call_time > 1) {
		state = ANIMATION_START;
	}

	last_call_time = get_ms_ticks();

	switch (state) {
		case ANIMATION_START:
			index = 0;
			last_transition_time = 0;
			state = ANIMATION_LIGHT_ON;
			break;
		case ANIMATION_LIGHT_ON:
			if (get_ms_ticks() - last_transition_time >= flash_delay) {
				turn_on(lights[index % lights_size]);
				last_transition_time = get_ms_ticks();
				state = ANIMATION_LIGHT_OFF;
			} break;
		case ANIMATION_LIGHT_OFF:
			if (get_ms_ticks() - last_transition_time >= flash_delay) {
				turn_off(lights[index % lights_size]);

				// Update the game state if the animation is finished. Otherwise,
				// update the animation state
				if (++index == flash_count) {
					game->state = new_game_state;
				} else {
					last_transition_time = get_ms_ticks();
					state = ANIMATION_LIGHT_ON;
				}
			} break;
	}
}

void game_over_animation(GAME* game) {
	LIGHT lights[] = {LIGHT_RED};
	const uint8_t lights_size = 1;
	const uint8_t flash_count = 15;
	const uint32_t wait_time = 50;

	light_animation(game, lights, lights_size, flash_count, wait_time, GAME_DISPLAY_SCORE);
}

void victory_animation(GAME* game) {
	LIGHT lights[] = {LIGHT_GREEN, LIGHT_WHITE, LIGHT_BLUE, LIGHT_RED};
	const uint8_t lights_size = 4;
	const uint8_t flash_count = 16;
	const uint32_t wait_time = 50;

	light_animation(game, lights, lights_size, flash_count, wait_time, GAME_DISPLAY_SCORE);
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

