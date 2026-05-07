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

static GAME game_instance;

void game_reset() {
	game_instance.state = GAME_WAIT_START;
	game_instance.round = 1;
	game_instance.sequence[0] = rand() % BUTTON_COUNT;
}

GAME_STATE game_get_state() {
	return game_instance.state;
}

void game_set_state(GAME_STATE state) {
	game_instance.state = state;
}

LIGHT* game_get_sequence() {
	return game_instance.sequence;
}

uint32_t game_get_round() {
	return game_instance.round;
}

void game_level_up() {
	if (++game_instance.round <= 15) {
		game_instance.sequence[game_instance.round - 1] = rand() % BUTTON_COUNT;
	}
}

