#include <registers.h>

#define GPIO_MODER_INPUT   (0u)
#define GPIO_MODER_OUTPUT  (1u)
#define GPIO_MODER_AF      (2u)
#define GPIO_MODER_ANALOG  (3u)

void gpio_init_output(GPIO_PORT_t* port, uint8_t pin) {
	const uint32_t pos = pin * 2u;

	port->MODER &= ~(0x3u << pos);
	port->MODER |= GPIO_MODER_OUTPUT << pos;
}

void gpio_init_input(GPIO_PORT_t* port, uint8_t pin) {
	const uint32_t pos = pin * 2u;

	port->MODER &= ~(0x3u << pos);
	port->MODER |= GPIO_MODER_INPUT << pos;
}

void gpio_write(GPIO_PORT_t* port, uint8_t pin, uint8_t value) {
	if (value) {
		port->ODR |= 1u << pin;
	} else {
		port->ODR &= ~(1u << pin);
	}
}

uint8_t gpio_read(GPIO_PORT_t* port, uint8_t pin) {
	return port->IDR & 1u << pin;
}
