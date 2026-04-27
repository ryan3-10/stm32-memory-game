#include "tests.h"
#include <components.h>
#include <game.h>

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


