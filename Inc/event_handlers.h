#ifndef EVENT_HANDLERS_H_
#define EVENT_HANDLERS_H_

#include <event.h>

// Flags indicating whether a function is starting a new run or just circulating
extern uint8_t wait_start_reset;
extern uint8_t display_sequence_reset;
extern uint8_t user_attempt_reset;
extern uint8_t game_over_animation_reset;
extern uint8_t victory_animation_reset;
extern uint8_t display_score_reset;

void handle_event(EVENT event);
void wait_start_handler(EVENT event);
void sequence_handler(EVENT event);
void user_attempt_handler(EVENT event);
void victory_handler(EVENT event);
void game_over_hanlder(EVENT event);
void display_score_handler(EVENT event);

// Input handler helpers
void correct_input_helper(uint8_t* index);
void incorrect_input_helper(uint8_t* index);
void endgame_helper(EVENT event);

#endif /* EVENT_HANDLERS_H_ */
