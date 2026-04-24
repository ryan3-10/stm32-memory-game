#ifndef GAME_H_
#define GAME_H_

#include <components.h>

typedef enum {
	STATE_GAME_INIT,
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
void init_game();
void wait_to_start();
void display_sequence(GAME* game);
void user_attempt(GAME* game);

#endif /* GAME_H_ */
