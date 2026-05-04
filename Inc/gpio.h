#ifndef GPIO_H_
#define GPIO_H_

#include <mcu.h>
#include <stdint.h>

void gpio_init_output(volatile GPIO_PORT_t* port, uint8_t pin);
void gpio_init_input(volatile GPIO_PORT_t* port, uint8_t pin);

void gpio_write(volatile GPIO_PORT_t* port, uint8_t pin, uint8_t value);
uint8_t gpio_read(volatile GPIO_PORT_t* port, uint8_t);
void gpio_set_pullup(volatile GPIO_PORT_t* port, uint8_t pin);


#endif /* GPIO_H_ */
