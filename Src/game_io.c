#include <board.h>
#include <game_io.h>
#include <gpio.h>
#include <systick.h>
#include <stdint.h>
#include <event.h>

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

void turn_on(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 1);
}

void turn_off(LIGHT light) {
	gpio_write(LIGHT_PORT, light_pins[light], 0);
}

void set_light(LIGHT light, uint8_t value) {
	gpio_write(LIGHT_PORT, light_pins[light], value);
}

void all_lights_off(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		gpio_write(LIGHT_PORT, light_pins[i], 0);
	}
}

uint8_t is_pressed(BUTTON button) {
	return !gpio_read(BUTTON_PORT, button_pins[button]);
}

// This interrupt handler loops through button_pins to see which pending bit request is set
// It then sets pressed according to the pending request
void EXTI9_5_IRQHandler(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; ++i) {
		if (EXTI->PR & 1 << button_pins[i]) {
			EVENT event = {
				EVENT_BUTTON,
				(BUTTON)i,
				get_ms_ticks()
			};
			eq_push(event);
			EXTI->PR = 1 << button_pins[i];	// Clear pending bit
		}
	}
}

