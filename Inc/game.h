#ifndef GAME_H_
#define GAME_H_

#include <game_io.h>
#include <stdint.h>

typedef enum {
	STATE_WAIT_START,
	STATE_SEQUENCE,
	STATE_USER_ATTEMPT,
	STATE_GAME_OVER
} STATE;

typedef struct {
	STATE state;
	uint32_t round;
	LIGHT sequence[50];
} GAME;

GAME get_new_game();
void wait_to_start();
void display_sequence(GAME* game);
void user_attempt(GAME* game);
void game_over_animation();
void display_score(uint8_t score);

#endif /* GAME_H_ */
