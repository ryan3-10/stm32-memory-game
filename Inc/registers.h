#ifndef REGISTERS_H_
#define REGISTERS_H_

#include <stdint.h>

#define GPIOC_BASE	(0x40020800UL)
#define GPIOE_BASE 	(0x40021000UL)
#define RCC_BASE 	(0x40023800UL)

typedef struct
{
	volatile uint32_t MODER;	// 0x00
	volatile uint32_t OTYPER;	// 0x04
	volatile uint32_t OSPEEDR;	// 0x08
	volatile uint32_t PUPDR;	// 0x0C
	volatile uint32_t IDR;		// 0X10
	volatile uint32_t ODR;		// 0x14
	volatile uint32_t BSRR;		// 0x18
	volatile uint32_t LCKR;		// 0x1C
	volatile uint32_t AFRL;		// 0x20
	volatile uint32_t AFRH;		// 0x20
} GPIO_PORT_t;

typedef struct
{
	volatile uint32_t CR;		// 0x00
	volatile uint32_t PLLCFGR;	// 0x04
	volatile uint32_t CFGR;		// 0X08
	volatile uint32_t  CIR;		// 0X0C
	volatile uint32_t AHB1RSTR;	// 0X10
	volatile uint32_t AHB2RSTR;	// 0X14
	volatile uint32_t AHB3RSTR;	// 0X18
	volatile uint32_t RES;		// 0x1C
	volatile uint32_t APB1RSTR;	// 0X20
	volatile uint32_t APB2RSTR; // 0x24
	volatile uint32_t RES2[2];	// 0x28, 0x2C
	volatile uint32_t AHB1ENR;	// 0x30
} RCC_t;

#define GPIOC 	((GPIO_PORT_t*)GPIOC_BASE)
#define GPIOE 	((GPIO_PORT_t*)GPIOE_BASE)
#define RCC		((RCC_t*)RCC_BASE)


#endif /* REGISTERS_H_ */
