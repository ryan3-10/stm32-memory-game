#ifndef BOARD_H_
#define BOARD_H_

// Light pins
#define	GREEN_LIGHT_PIN 	(0x6u)
#define	WHITE_LIGHT_PIN 	(0x2u)
#define BLUE_LIGHT_PIN 		(0xDu)
#define RED_LIGHT_PIN		(0xFu)

// Button pins
#define GREEN_BUTTON_PIN	(0x3u)
#define WHITE_BUTTON_PIN	(0x4u)
#define BLUE_BUTTON_PIN 	(0x5u)
#define RED_BUTTON_PIN		(0x6u)

#define BUTTON_PORT	GPIOC
#define LIGHT_PORT 	GPIOE

void board_init();


#endif /* BOARD_H_ */
