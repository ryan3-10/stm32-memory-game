#include <game.h>
#include <game_io.h>
#include <stdint.h>
#include <stdlib.h>

// define the struct here so external modules can't create a GAME instance
typedef struct {
	GAME_STATE state;
	uint32_t round;
	LIGHT sequence[15];
} GAME;

static GAME game;

void game_reset() {
	game.state = GAME_WAIT_START;
	game.round = 1;
	game.sequence[0] = rand() % BUTTON_COUNT;
}

GAME_STATE game_get_state() {
	return game.state;
}

void game_set_state(GAME_STATE state) {
	game.state = state;
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

