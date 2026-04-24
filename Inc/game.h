#ifndef GAME_H_
#define GAME_H_



typedef enum {
	STATE_GAME_INIT,
	STATE_WAIT_START,
	STATE_SEQUENCE,
	STATE_WAIT_INPUT,
	STATE_GAME_OVER
} STATE;

void init_game();
void wait_to_start();

#endif /* GAME_H_ */
