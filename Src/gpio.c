#include <gpio.h>

#define GPIO_MODER_INPUT	(0u)
#define GPIO_MODER_OUTPUT  	(1u)
#define GPIO_MODER_AF      	(2u)
#define GPIO_MODER_ANALOG  	(3u)
#define GPIO_PUPDR_PU		(1u)

void gpio_init_output(volatile GPIO_PORT_t* port, uint8_t pin) {
	const uint8_t pos = pin * 2u;

	port->MODER &= ~(3u << pos);
	port->MODER |= GPIO_MODER_OUTPUT << pos;
}

void gpio_init_input(volatile GPIO_PORT_t* port, uint8_t pin) {
	const uint8_t pos = pin * 2u;

	port->MODER &= ~(3u << pos);
	port->MODER |= GPIO_MODER_INPUT << pos;
}

void gpio_set_pullup(volatile GPIO_PORT_t* port, uint8_t pin) {
	const uint8_t pos = pin * 2u;

	port->PUPDR &= ~(3u << pos);
	port->PUPDR |= GPIO_PUPDR_PU << pos;
}

void gpio_write(volatile GPIO_PORT_t* port, uint8_t pin, uint8_t value) {
	if (value) {
		port->ODR |= 1u << pin;
	} else {
		port->ODR &= ~(1u << pin);
	}
}

uint8_t gpio_read(volatile GPIO_PORT_t* port, uint8_t pin) {
	return (port->IDR >> pin) & 1u;
}
