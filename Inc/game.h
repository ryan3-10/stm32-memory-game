#ifndef GAME_H_
#define GAME_H_

#include <game_io.h>

#define MAX_SCORE 15

typedef enum {
	GAME_WAIT_START,
	GAME_SEQUENCE,
	GAME_USER_ATTEMPT,
	GAME_VICTORY,
	GAME_OVER,
	GAME_DISPLAY_SCORE
} GAME_STATE;

void game_reset(void);
GAME_STATE game_get_state(void);
void game_set_state(GAME_STATE state);
LIGHT* game_get_sequence(void);
uint32_t game_get_round(void);
void game_level_up(void);
uint8_t game_in_new_state(void);

#endif /* GAME_H_ */
