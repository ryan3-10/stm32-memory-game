#include <board.h>
#include <game_io.h>
#include <gpio.h>
#include <systick.h>
#include <stdint.h>

volatile BUTTON pressed = BUTTON_NONE;

uint8_t light_pins[] = {
	GREEN_LIGHT_PIN,
	WHITE_LIGHT_PIN,
	BLUE_LIGHT_PIN,
	RED_LIGHT_PIN
};

uint8_t button_pins[] = {
	GREEN_BUTTON_PIN,
	WHITE_BUTTON_PIN,
	BLUE_BUTTON_PIN,
	RED_BUTTON_PIN
};

const uint8_t array_size = 4;

void turn_on(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 1);
}

void turn_off(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 0);
}

void all_lights_off() {
	for (uint8_t i = 0; i < array_size; ++i) {
		gpio_write(LIGHT_PORT, light_pins[i], 0);
	}
}

uint8_t is_pressed(BUTTON button) {
	return !gpio_read(BUTTON_PORT, button_pins[button]);
}

BUTTON get_input() {
	pressed = BUTTON_NONE;
	const uint8_t debounce_delay = 30;

	// wait for interrupt
	while (pressed == BUTTON_NONE);
	BUTTON temp_pressed = pressed;
	delay(debounce_delay); // debounce check

	turn_on((LIGHT)temp_pressed);
	while (is_pressed(temp_pressed));
	delay(debounce_delay);

	turn_off((LIGHT)temp_pressed);

	return temp_pressed;
}

// This interrupt handler loops through button_pins to see which pending bit request is set
// It then sets pressed according to the pending request
void EXTI9_5_IRQHandler() {
	for (uint8_t i = 0; i < array_size; ++i) {
		if (EXTI->PR & 1 << button_pins[i]) {
			pressed = (BUTTON)i;
			EXTI->PR = 1 << button_pins[i];
			break;
		}
	}
}

