#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include <gpio.h>

// Ports
#define LIGHT_PORT	(GPIOE)
#define BUTTON_PORT	(GPIOC)

// Light pins
#define	RED_LIGHT_PIN 		(0x6u)
#define	WHITE_LIGHT_PIN 	(0x2u)
#define BLUE_LIGHT_PIN 		(0xDu)
#define YELLOW_LIGHT_PIN	(0xFu)

// Button pins
#define RED_BUTTON_PIN		(0x3u)
#define WHITE_BUTTON_PIN	(0x4u)
#define BLUE_BUTTON_PIN 	(0x5u)
#define YELLOW_BUTTON_PIN	(0x6u)

typedef enum {
	LIGHT_RED,
	LIGHT_WHITE,
	LIGHT_BLUE,
	LIGHT_YELLOW
} LIGHT;

typedef enum {
	BUTTON_RED,
	BUTTON_WHITE,
	BUTTON_BLUE,
	BUTTON_YELLOW
} BUTTON;

void turn_on(LIGHT light);
void turn_off(LIGHT light);
uint8_t is_pressed(BUTTON button);
BUTTON get_input();
void delay(uint32_t count);

#endif /* COMPONENTS_H_ */
