#ifndef GAME_IO_H_
#define GAME_IO_H_

#include <stdint.h>

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
	BUTTON_RED,
	BUTTON_COUNT,
} BUTTON;

typedef enum {
    INPUT_IDLE,
    INPUT_DEBOUNCE_PRESS,
    INPUT_WAIT_RELEASE,
    INPUT_DEBOUNCE_RELEASE
} INPUT_STATE;

void turn_on(LIGHT light);
void turn_off(LIGHT light);
void set_light(LIGHT light, uint8_t value);
void all_lights_off(void);
uint8_t is_pressed(BUTTON button);
BUTTON get_input(void);

#endif /* GAME_IO_H_ */
