#ifndef EVENT_HANDLERS_H_
#define EVENT_HANDLERS_H_

#include <event.h>

void handle_event(EVENT event);
void wait_start_handler(EVENT event);
void sequence_handler(EVENT event);
void user_attempt_handler(EVENT event);
void victory_handler(EVENT event);
void game_over_handler(EVENT event);
void display_score_handler(EVENT event);

// Input handler helpers
void correct_input_helper(uint8_t* index);
void incorrect_input_helper(uint8_t* index);
void endgame_helper(EVENT event);

#endif /* EVENT_HANDLERS_H_ */
