#include <display.h>
#include <event.h>
#include <event_handlers.h>
#include <game.h>
#include <game_io.h>

#define DEBOUNCE_THRESHOLD 30

void (*event_handlers[])(EVENT) = {
	wait_start_handler,
	sequence_handler,
	user_attempt_handler,
	victory_handler,
	game_over_hanlder,
	display_score_handler
};

uint8_t debounce_detected(EVENT current) {
	static EVENT previous;
	uint32_t time_diff = current.timestamp - previous.timestamp;

	uint8_t is_debounce =
		current.type == previous.type
		&& current.button == previous.button
		&& time_diff < DEBOUNCE_THRESHOLD;


	if (is_debounce) {
		is_debounce = 50;
	}
	previous = current;
	return is_debounce;
}

void handle_event(EVENT event) {
	if (!debounce_detected(event)) {
		event_handlers[game_get_state()](event);
	}
}

void wait_start_handler(EVENT event) {
	switch (event.type) {
		case EVENT_BUTTON_PRESSED:
			turn_on(event.button);
			if (event.button == BUTTON_GREEN) {
				turn_off(BUTTON_GREEN);
				game_set_state(GAME_SEQUENCE);
			}
			break;

		case EVENT_BUTTON_RELEASED:
			turn_off(event.button);
			break;

		// Ignore everything else
		default:
			break;
	}
}

void sequence_handler(EVENT event) {
	switch (event.type) {
		// Don't allow button presses during sequence display
		case EVENT_BUTTON_PRESSED:
			all_lights_off();
			game_set_state(GAME_OVER);
			break;

		case EVENT_DISPLAY_DONE:
			game_set_state(GAME_USER_ATTEMPT);
			break;

		// Ignore anything else
		default:
			break;
	}
}

void user_attempt_handler(EVENT event) {
	static uint8_t index;

	switch (event.type) {
		case EVENT_BUTTON_PRESSED:
			turn_on(event.button);
			break;

		case EVENT_BUTTON_RELEASED:
			turn_off(event.button);

			if ((LIGHT)event.button == game_get_sequence()[index]) {
				correct_input_helper(&index);
			} else {
				incorrect_input_helper(&index);
			}
			break;

		case EVENT_TIMEOUT:
			all_lights_off();
			index = 0;
			game_set_state(GAME_OVER);
			break;

		default:
			break;
	}
}

void correct_input_helper(uint8_t* index) {
	if (++(*index) == game_get_round()) {
		*index = 0;
		game_level_up();
		GAME_STATE new_state;

		if (game_get_round() > MAX_SCORE) {
			new_state = GAME_VICTORY;
		} else {
			new_state = GAME_SEQUENCE;
		}

		game_set_state(new_state);
	}
}

void incorrect_input_helper(uint8_t* index) {
	*index = 0;
	game_set_state(GAME_OVER);
}

void victory_handler(EVENT event) {
	endgame_helper(event);
}

void game_over_hanlder(EVENT event) {
	endgame_helper(event);
}

void endgame_helper(EVENT event) {
	switch (event.type) {
		// Cancels the animation
		case EVENT_BUTTON_PRESSED:
			all_lights_off();
			game_set_state(GAME_DISPLAY_SCORE);
			break;

		case EVENT_DISPLAY_DONE:
			game_set_state(GAME_DISPLAY_SCORE);
		break;

		// Ignore everything else
		default:
			break;
	}
}

void display_score_handler(EVENT event) {
	switch (event.type) {
		case EVENT_BUTTON_PRESSED:
			all_lights_off();
			game_reset();
			game_set_state(GAME_WAIT_START);
			break;

		// Ignore everything else
		default:
			break;
	}
}
