#ifndef GAME_H_
#define GAME_H_

#include <game_io.h>
#include <stdint.h>

typedef enum {
	GAME_WAIT_START,
	GAME_SEQUENCE,
	GAME_USER_ATTEMPT,
	GAME_VICTORY,
	GAME_OVER,
	GAME_DISPLAY_SCORE
} GAME_STATE;

typedef enum {
	ANIMATION_START,
	ANIMATION_LIGHT_ON,
	ANIMATION_LIGHT_OFF,
} ANIMATION_STATE;

typedef struct {
	GAME_STATE state;
	uint32_t round;
	LIGHT sequence[15];
} GAME;


GAME get_new_game();
void wait_to_start();
void display_sequence(GAME* game);
void user_attempt(GAME* game);

void light_animation(
	GAME* game,
	LIGHT* lights,
	uint8_t lights_size,
	uint8_t flash_count,
	uint32_t flash_delay,
	GAME_STATE new_game_state
);

void game_over_animation();
void victory_animation(GAME* game);
void display_score(uint8_t score);

#endif /* GAME_H_ */
