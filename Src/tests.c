#include "tests.h"
#include <game.h>
#include <game_io.h>

void test_debouncing() {
	while (1) {
		BUTTON test_button = get_input();
		uint16_t count = 0;

		while (get_input() == test_button) {
			++count;
		}

		display_score(count);
	}
}

void test_display_score() {
	for (int8_t i = 0; i < 16; ++i) {
		display_score(i);
	}
}

