#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdint.h>

#define GPIOA_BASE 	(0x40020000UL)
#define GPIOD_BASE 	(0x40020C00UL)
#define GPIOE_BASE 	(0x40021000UL)
#define RCC_BASE 	(0x40023800UL)

typedef struct
{
	uint32_t MODER;		// 0x00
	uint32_t OTYPER;	// 0x04
	uint32_t OSPEEDR;	// 0x08
	uint32_t PUPDR;		// 0x0C
	uint32_t IDR;		// 0X10
	uint32_t ODR;		// 0x14
	uint32_t BSRR;		// 0x18
	uint32_t LCKR;		// 0x1C
	uint32_t AFRL;		// 0x20
	uint32_t AFRH;		// 0x20
} GPIO_PORT_t;

typedef struct
{
	uint32_t CR;		// 0x00
	uint32_t PLLCFGR;	// 0x04
	uint32_t CFGR;		// 0X08
	uint32_t CIR;		// 0X0C
	uint32_t AHB1RSTR;	// 0X10
	uint32_t AHB2RSTR;	// 0X14
	uint32_t AHB3RSTR;	// 0X18
	uint32_t RES;		// 0x1C
	uint32_t APB1RSTR;	// 0X20
	uint32_t APB2RSTR; 	// 0x24
	uint32_t RES2[2];	// 0x28, 0x2C
	uint32_t AHB1ENR;	// 0x30
} RCC_t;

#define GPIOA 	((GPIO_PORT_t*)GPIOA_BASE)
#define GPIOD 	((GPIO_PORT_t*)GPIOD_BASE)
#define GPIOE 	((GPIO_PORT_t*)GPIOE_BASE)
#define RCC		((RCC_t*)RCC_BASE)


#endif /* REGISTERS_H_ */
