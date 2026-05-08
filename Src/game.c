#include <game.h>
#include <game_io.h>
#include <stdint.h>
#include <stdlib.h>

// define the struct here so external modules can't create a GAME instance
typedef struct {
	GAME_STATE state;
	uint32_t round;
	LIGHT sequence[MAX_SCORE];
	uint8_t in_new_state;
} GAME;

static GAME game;

void game_reset() {
	game.state = GAME_WAIT_START;
	game.round = 1;
	game.sequence[0] = rand() % BUTTON_COUNT;
	game.in_new_state = 1;
}

GAME_STATE game_get_state() {
	return game.state;
}

void game_set_state(GAME_STATE state) {
	game.state = state;
	game.in_new_state = 1;
}

LIGHT* game_get_sequence() {
	return game.sequence;
}

uint32_t game_get_round() {
	return game.round;
}

void game_level_up() {
	if (++game.round <= 15) {
		game.sequence[game.round - 1] = rand() % BUTTON_COUNT;
	}
}

uint8_t game_in_new_state(void) {
	uint8_t output = game.in_new_state;
	// Once this is checked, state is no longer considered "new"
	game.in_new_state = 0;
	return output;
}


