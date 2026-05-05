#ifndef GAME_H_
#define GAME_H_

#include <game_io.h>
#include <stdint.h>

typedef enum {
	GAME_WAIT_START,
	GAME_SEQUENCE,
	GAME_USER_ATTEMPT,
	GAME_VICTORY,
	GAME_OVER
} GAME_STATE;

typedef struct {
	GAME_STATE state;
	uint32_t round;
	LIGHT sequence[15];
} GAME;

GAME get_new_game();
void wait_to_start();
void display_sequence(GAME* game);
void user_attempt(GAME* game);
void game_over_animation();
void victory_animation();
void display_score(uint8_t score);

#endif /* GAME_H_ */
