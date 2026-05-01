#ifndef GPIO_H_
#define GPIO_H_

#include <mcu.h>

void gpio_init_output(GPIO_PORT_t* port, uint8_t pin);
void gpio_init_input(GPIO_PORT_t* port, uint8_t pin);

void gpio_write(GPIO_PORT_t* port, uint8_t pin, uint8_t value);
uint8_t gpio_read(GPIO_PORT_t* port, uint8_t);
void gpio_set_pullup(GPIO_PORT_t* port, uint8_t pin);


#endif /* GPIO_H_ */
