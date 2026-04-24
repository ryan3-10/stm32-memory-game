#ifndef GAME_H_
#define GAME_H_

#include <gpio.h>

typedef enum {
	STATE_GAME_INIT,
	STATE_WAIT_START,
	STATE_SEQUENCE,
	STATE_WAIT_INPUT,
	STATE_GAME_OVER
} STATE;

void init_game();

#endif /* GAME_H_ */
