#include <board.h>
#include <game_io.h>
#include <gpio.h>
#include <systick.h>
#include <stdint.h>

uint8_t get_light_pin(LIGHT light) {
	const static uint8_t light_pins[] = {
			GREEN_LIGHT_PIN,
			WHITE_LIGHT_PIN,
			BLUE_LIGHT_PIN,
			RED_LIGHT_PIN
	};

	return light_pins[light];
}

uint8_t get_button_pin(BUTTON button) {
	const static uint8_t button_pins[] = {
		GREEN_BUTTON_PIN,
		WHITE_BUTTON_PIN,
		BLUE_BUTTON_PIN,
		RED_BUTTON_PIN
	};

	return button_pins[button];
}

void turn_on(LIGHT light) {
	gpio_write(LIGHT_PORT, get_light_pin(light), 1);
}

void turn_off(LIGHT light) {
	gpio_write(LIGHT_PORT, get_light_pin(light), 0);
}

void set_light(LIGHT light, uint8_t value) {
	gpio_write(LIGHT_PORT, get_light_pin(light), value);
}

void all_lights_off(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		gpio_write(LIGHT_PORT, get_light_pin(i), 0);
	}
}

uint8_t is_pressed(BUTTON button) {
	return !gpio_read(BUTTON_PORT, get_button_pin(button));
}

