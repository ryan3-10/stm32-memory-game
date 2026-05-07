#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include <game_io.h>
#include <stdint.h>

void wait_start(void);
void display_sequence(void);
void user_attempt(void);
void game_over_animation(void);
void victory_animation(void);
void display_score(void);

#endif /* USER_INTERFACE_H_ */
