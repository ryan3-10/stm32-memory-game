#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <game_io.h>
#include <stdint.h>

void wait_start(void);
void display_sequence(void);
void user_attempt(void);
void game_over_animation(void);
void victory_animation(void);
void display_score(uint8_t score);

#endif /* GAME_LOGIC_H_ */
