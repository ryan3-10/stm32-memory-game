#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <gpio.h>

// Ports
#define LIGHT_PORT	(GPIOE)
#define BUTTON_PORT	(GPIOC)

// Systick flags
#define CTRL_ENABLE    (1 << 0)
#define CTRL_CLKSOURCE (1 << 2)
#define CTRL_COUNTFLAG (1 << 16)

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
void delay(uint32_t count);

#endif /* COMPONENTS_H_ */
