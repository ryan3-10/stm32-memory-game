#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <stdint.h>

// Peripheral base addresses
#define GPIOC_BASE		(0x40020800UL)
#define GPIOE_BASE 		(0x40021000UL)
#define RCC_BASE 		(0x40023800UL)
#define SYSTICK_BASE	(0xE000E010UL)
#define RNG_BASE		(0x50060800UL)

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

// PLL bits
#define PLLN_POS 	(6u)
#define PLLM_POS 	(0u)
#define PLLQ_POS 	(24u)
#define PLLON_POS	(24u)

// Clock enable bits
#define PORTC_CLOCK_POS	(2u)
#define PORTE_CLOCK_POS	(4u)
#define RNG_CLOCK_POS	(6u)

// RNG control register bits
#define RNGEN_POS	(2u)

// Systick flags
#define CTRL_ENABLE    (1 << 0)
#define CTRL_CLKSOURCE (1 << 2)
#define CTRL_COUNTFLAG (1 << 16)

typedef struct {
	volatile uint32_t MODER;	// 0x00
	volatile uint32_t OTYPER;	// 0x04
	volatile uint32_t OSPEEDR;	// 0x08
	volatile uint32_t PUPDR;	// 0x0C
	volatile uint32_t IDR;		// 0X10
	volatile uint32_t ODR;		// 0x14
	volatile uint32_t BSRR;		// 0x18
	volatile uint32_t LCKR;		// 0x1C
	volatile uint32_t AFRL;		// 0x20
	volatile uint32_t AFRH;		// 0x24
} GPIO_PORT_t;

typedef struct {
	volatile uint32_t CR;		// 0x00
	volatile uint32_t PLLCFGR;	// 0x04
	volatile uint32_t CFGR;		// 0X08
	volatile uint32_t CIR;		// 0X0C
	volatile uint32_t AHB1RSTR;	// 0X10
	volatile uint32_t AHB2RSTR;	// 0X14
	volatile uint32_t AHB3RSTR;	// 0X18
	volatile uint32_t RES;		// 0x1C
	volatile uint32_t APB1RSTR;	// 0X20
	volatile uint32_t APB2RSTR; // 0x24
	volatile uint32_t RES2[2];	// 0x28, 0x2C
	volatile uint32_t AHB1ENR;	// 0x30
	volatile uint32_t AHB2ENR; 	// 0x34
	volatile uint32_t AHB3ENR; 	// 0x38
	volatile uint32_t RES3; 	// 0x3C
	volatile uint32_t APB1ENR;	// 0x40
	volatile uint32_t APB2ENR;	// 0x44;
} RCC_t;

typedef struct {
	volatile uint32_t CTRL;		// 0x00
	volatile uint32_t LOAD;		// 0x04
	volatile uint32_t VAL;		// 0x08
} SYSTICK_t;

typedef struct {
	volatile uint32_t CR;	// 0x00
	volatile uint32_t SR;	// 0x04
	volatile uint32_t DR;	// 0x08
} RNG_t;

#define BUTTON_PORT 	((volatile GPIO_PORT_t*)GPIOC_BASE)
#define LIGHT_PORT 	((volatile GPIO_PORT_t*)GPIOE_BASE)
#define RCC		((volatile RCC_t*)RCC_BASE)
#define SYSTICK	((volatile SYSTICK_t*)SYSTICK_BASE)
#define RNG		((volatile RNG_t*)RNG_BASE)

void init_peripherals();

#endif /* PERIPHERALS_H_ */
