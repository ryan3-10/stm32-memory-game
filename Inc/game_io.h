#ifndef GAME_IO_H_
#define GAME_IO_H_

#include <gpio.h>

typedef enum {
	LIGHT_GREEN,
	LIGHT_WHITE,
	LIGHT_BLUE,
	LIGHT_RED
} LIGHT;

typedef enum {
	BUTTON_NONE = -1,
	BUTTON_GREEN,
	BUTTON_WHITE,
	BUTTON_BLUE,
	BUTTON_RED
} BUTTON;

void turn_on(LIGHT light);
void turn_off(LIGHT light);
void all_lights_off();
uint8_t is_pressed(BUTTON button);
BUTTON get_input();

#endif /* GAME_IO_H_ */
